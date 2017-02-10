//
//  BaseMessage.cpp
//  QJ_IO
//
//  Created by Andy Hong on 2017/1/5.
//
//

#include "BaseMessage.h"

#include <zlib.h>

#include <google/protobuf/stubs/common.h> // implicit_cast, down_cast

int GetCompressUIntValueSize(uint32_t value);
int WriteCompressUIntValue(uint32_t value, char* buf);
int ReadCompressUIntValue(uint32_t& value, char* buf, int buffsize);

int GetCompressUIntValueSize(uint32_t value)
{
    if (value >= (0x1<<7)) {
        if (value >= (0x1<<14)) {
            if (value >= (0x1<<21)) {
                if (value >= (0x1<<28)) {
                    return 5;
                }
                return 4;
            }
            return 3;
        }
        return 2;
    }
    return 1;
}

int WriteCompressUIntValue(uint32_t value, char* buf)
{
    char* pdata = buf;
    if (value >= (0x1 << 7)) {
        *pdata++ = (value & 0x7f) | 0x80;
        if (value >= (0x1 << 14)) {
            *pdata++ = ((value >> 14) & 0x7f) | 0x80;
            if (value >= (0x1<<21)) {
                *pdata++ = ((value >> 21) & 0x7f) | 0x80;
                if (value >= (0x1<<28)) {
                    *pdata++ = (value >> 28) & 0x7f;
                    return 5;
                } else {
                    *pdata++ = (value >> 21) & 0x7f;
                }
                return 4;
            } else {
                *pdata++ = (value >> 14) & 0x7f;
            }
            return 3;
        } else {
            *pdata++ = (value >> 7) & 0x7f;
        }
        return 2;
    } else {
        //0111 1111
        *pdata++ = (value & 0x7f);
    }
    return 1;
}

int ReadCompressUIntValue(uint32_t& value, char* buf, int buffsize)
{
    char* pdata = buf;
    value = 0;
    if (buffsize < 1) {
        return 0;
    }
    if ((*pdata) & 0x80) {
        if (buffsize < 2) {
            return 0;
        }
        value += (unsigned int)((*pdata) & 0x7f);
        ++pdata;
        if ((*pdata) & 0x80) {
            if (buffsize < 3) {
                return 0;
            }
            value += ((unsigned int)((*pdata) & 0x7f)) << 7;
            ++pdata;
            if ((*pdata) & 0x80) {
                if (buffsize < 4) {
                    return 0;
                }
                value += ((unsigned int)((*pdata) & 0x7f)) << 14;
                ++pdata;
                if ((*pdata) & 0x80) {
                    if (buffsize < 5) {
                        return 0;
                    }
                    value += ((unsigned int)((*pdata) & 0x7f)) << 21;
                    ++pdata;
                    if ((*pdata) & 0x80) {
                        return 0;   //error data
                    } else {
                        value += ((unsigned int)(*pdata)) << 28;
                        return 5;
                    }
                } else {
                    value += ((unsigned int)(*pdata)) << 21;
                    return 4;
                }
            } else {
                value += ((unsigned int)(*pdata)) << 14;
                return 3;
            }
        } else {
            value += ((unsigned int)(*pdata)) << 7;
            return 2;
        }
    } else {
        value += (unsigned int)(*pdata);
        return 1;
    }
}


bool BaseMessage::CanGetCompressUInt(int& uint_size)
{
    std::size_t cnt = 5;
    std::size_t aRead = 0;
    int cpsize = 0;
    auto asize = GetSize();
    
    if(asize < 1)
    {
        return false;
    }
    
    uint_size = 0;
    if(asize > 0)
    {
        aRead = (cnt > asize) ? asize : cnt;
        if (aRead > 0) {
            cpsize = (int) aRead;
            if (cpsize > 5) {
                cpsize = 5;
            }
            unsigned char* pdata = GetReadPointer();
            for (int i=0; i<cpsize; ++i) {
                if (((*pdata) & 0x80) == 0) {
                    ++uint_size;
                    return true;
                }
                ++pdata;
                ++uint_size;
            }
            if (uint_size >= 5) {
                uint_size = 0;  //data error
                return true;
            }
        }
        cnt -= aRead;
    }
    
    return false;
}

char* BaseMessage::CreateWriteBuf(std::size_t size)
{
    char* pbuf = NULL;
    auto bufsize = GetRemainingSpace();
    if (size > bufsize) {
        Resize(GetMsgSize()+size-bufsize);
    } else {
    }
    pbuf = (char*)GetWritePointer();
    _wpos+= size;
    return pbuf;
}

bool BaseMessage::SendNetMessage(uint16_t opcode, ::google::protobuf::MessageLite *pmessage, bool is_use_crypto)	//write
{
    if (!_session)	//结束，写缓冲区不再接受输入
    {
//        JyLogError("SendNetMessage opcode %d session error!", opcode);
        return true;
    }
    
    int size = 0;
    if (pmessage != NULL)
    {
        size = pmessage->ByteSize();
    }
    
    //	if (opcode == S2C::SMSG_SHUTDOWN)	//SMSG_SHUTDOWN是客户端收到就断开连接的消息
    //	{
    //        SetSession(nullptr); //缓冲区错误
    //	}
    
    bool bZip = false;
    int opcodesize = 0;
    int bodyvaluesize = 0;
    int unzipvaluesize = 0;
    unsigned int realopcode = opcode;
    opcodesize = GetCompressUIntValueSize(realopcode);
    bodyvaluesize = GetCompressUIntValueSize(size);
    if (bZip) {
        //        unzipvaluesize = GetCompressUIntValueSize(0);
    }
    std::size_t writesize = opcodesize+bodyvaluesize+unzipvaluesize+size;
    if (size > 0) {
        writesize += 2; //crc
    }
    int sequenceid_size = GetCompressUIntValueSize(_sequence_id);
    writesize += sequenceid_size;
    
    char* pbuf = CreateWriteBuf(writesize);
    if (!pbuf)
    {
//        JyLogError("SendNetMessage opcode %d buffer error!", opcode);
        SetSession(nullptr); //缓冲区错误
        return false;
    }
    
    char *pdata = pbuf;
    WriteCompressUIntValue(_sequence_id++, pdata);
    if (_sequence_id > kSocketMaxSequenceId) {
        _sequence_id = kSocketMinSequenceId;
    }
    pdata += sequenceid_size;
    
    WriteCompressUIntValue(size, pdata);
    pdata += bodyvaluesize;
    
    WriteCompressUIntValue(realopcode, pdata);
    pdata += opcodesize;
    
    if (size > 0)
    {
        if (!pmessage->SerializeToArray(reinterpret_cast<void*>(pdata), size))
        {
//            JyLogError("SendNetMessage opcode %d serialize error!", opcode);
            return false;
        }
//        if (_is_crypto && is_use_crypto) {
//            _crypto_engine.Process((unsigned char*)pdata, (unsigned char*)pdata, (unsigned int)size);
//        }
        uint16_t crc;
        uint32_t crcvalue = (uint32_t)::adler32(1, reinterpret_cast<const Bytef*>(pdata), static_cast<int>(size));
        crc = crcvalue&0xffff;
        crc = htons(crc);
        char* pcrc = (char*)(&crc);
        memcpy(pdata+size, pcrc, 2);
    }
    
#ifdef __NET_PACKET_DEBUG__
    jysvr::LogPacket((uint32_t)writesize, opcode, (uint8_t*)pbuf, 1, 0);
#endif
    return true;
}

bool BaseMessage::Read(void* destination, std::size_t size)
{
    std::size_t cnt = size;
    std::size_t aRead = 0;
    auto asize = GetSize();
    if (asize < size) {
        return false;
    }
    if (asize > 0) {
        aRead = (cnt > asize) ? asize : cnt;
        if (destination)
        {
            memcpy(destination, GetReadPointer(), aRead);
        }
        cnt -= aRead;
        _rpos += aRead;

        if (_rpos)
        {
            if (_rpos != _wpos)
                memmove(GetBasePointer(), GetReadPointer(), GetSize());
            _wpos -= _rpos;
            _rpos = 0;
        }
    } else {
        return false;
    }
    return true;
}

void BaseMessage::SetSession(BaseSession* session){
    if (_session) {
        _session->stop();
    }
    _session = session;
    
}

void BaseMessage::reset()
{
    _wpos = 0;
    _rpos = 0;
    
    _read_buf_flag = kReadBufFlagSequenceId;
    _msg_remaining = 0;
    _opcode = 0;
    
    _sequence_id = kSocketMinSequenceId;
    _msg_size = 0;
    _ack_count = 0;
}

void BaseMessage::Normalize()
{
    if (_rpos)
    {
        if (_rpos != _wpos)
            memmove(GetBasePointer(), GetReadPointer(), GetSize());
        _wpos -= _rpos;
        _rpos = 0;
    }
}

bool BaseMessage::handleWriteMsg(std::size_t size){
    std::size_t bytesToSend = GetSize();
    if (size == 0) {
    } else if (size < bytesToSend) {
        _rpos+=size;
        Normalize();
    } else {
        reset();
    }
    return true;

}

bool BaseMessage::handleMsg(std::size_t size){
    _wpos += size;
    char uint_buf[5];
    
    while(true)
    {
        switch (_read_buf_flag) {
            case kReadBufFlagSequenceId:
            {
                int uint_size;
                if (!CanGetCompressUInt(uint_size)) {
                    return true;
                }
                if (uint_size == 0) {
//                    SetSession(nullptr); //缓冲区错误
                    return false;
                }
                Read(uint_buf, uint_size);
                ReadCompressUIntValue(_sequence_id, uint_buf, uint_size);
                switch (_sequence_id) {
                    case 0:
                    {
                        SetReadBufFlag(kReadBufFlagIsAck);
                    }
                        break;
                    case 1:
                    {
                        SetReadBufFlag(kReadBufFlagIsAcks);
                    }
                        break;
                    default:
                    {
                        SetReadBufFlag(kReadBufFlagMsgSize);
                    }
                        break;
                }

            }
                break;
            case kReadBufFlagMsgSize:
            {
                int uint_size;
                if (!CanGetCompressUInt(uint_size)) {
                    return true;
                }
                if (uint_size == 0) {
                    //SetSession(nullptr); //缓冲区错误
                    return false;
                }
                Read(uint_buf, uint_size);
                ReadCompressUIntValue(_msg_size, uint_buf, uint_size);
                if (_msg_size > kTcpMsgMaxSize) {
//                    SetSession(nullptr); //缓冲区错误
                    return false;
                    
                }
                if (_msg_size > 0) {
                    _msg_remaining = _msg_size+2;
                } else {
                    _msg_remaining = 0;
                }
                SetReadBufFlag(kReadBufFlagOpcode);
            }
                break;
            case kReadBufFlagOpcode:
            {
                int uint_size;
                if (!CanGetCompressUInt(uint_size)) {
                    return true;
                }
                if (uint_size == 0) {
//                    SetSession(nullptr); //缓冲区错误
                    return false;
                }
                Read(uint_buf, uint_size);
                uint32_t opcode;
                ReadCompressUIntValue(opcode, uint_buf, uint_size);
                _opcode = opcode;
                if (_msg_size == 0) {   //message size is zero
#ifdef __NET_PACKET_DEBUG__
                    jysvr::LogPacket(0, _opcode, recivetbuf, 0, 0);
#endif
                    std::shared_ptr<::google::protobuf::MessageLite> msg;
                    if (!_session->HandleMessage(_opcode, msg)) {
                        SetSession(nullptr); //
                        return false;
                    }
                    SetReadBufFlag(kReadBufFlagSequenceId);
                    continue;
                } else {
                    SetReadBufFlag(kReadBufFlagMsgRemain);
                }
            }
                break;
            case kReadBufFlagMsgRemain:
            {
                if (_msg_remaining > kTcpMsgMaxSize) {	//封包超过规定的大小
//                    SetSession(nullptr); //缓冲区错误
                    return false;
                }
                if(_msg_remaining > 0)
                {
                    // do we have a full packet?
                    if(GetSize() < _msg_remaining) {
                        return true;
                    }
                    
                    std::shared_ptr< ::google::protobuf::MessageLite > message;
                    const char* pcdata = reinterpret_cast<const char*>(GetReadPointer());
                    uint16_t crc;
                    char* pcrc = (char*)(&crc);
                    memcpy(pcrc, pcdata+_msg_size, 2);
                    crc = ntohs(crc);
                    uint32_t crcvalue = (uint32_t)::adler32(1, reinterpret_cast<const Bytef*>(pcdata), static_cast<int>(_msg_size));
                    if ((crcvalue&0xffff) != (uint32_t)crc) {
//                        SetSession(nullptr); //缓冲区错误
                        return false;
                    }
            
#ifdef __NET_PACKET_DEBUG__
                    jysvr::LogPacket(_msg_size, _opcode, (const unsigned char*)pcdata, 0, 0);
#endif
                    const void* p0 = pcdata;
                    if (!_session->ParseMessage(_opcode, p0, _msg_size, nullptr, 0)) {
                        SetSession(nullptr); //缓冲区错误
                        return false;
                    }
                    bool bsucessed = Read(NULL, _msg_remaining);
                    if (!bsucessed)
                    {
                        SetSession(nullptr); //缓冲区错误
                        return false;
                    }
                    SetReadBufFlag(kReadBufFlagSequenceId);
                } else {
                    SetSession(nullptr); //缓冲区错误
                    return false;
                }
            }
                break;
            case kReadBufFlagIsAck:
            {
                int uint_size;
                if (!CanGetCompressUInt(uint_size)) {
                    return true;
                }
                if (uint_size == 0) {
                    SetSession(nullptr); //缓冲区错误
                    return false;
                }
                Read(uint_buf, uint_size);
                
                uint32_t ack_sequence_id;
                ReadCompressUIntValue(ack_sequence_id, uint_buf, uint_size);
                if ((ack_sequence_id < kSocketMinSequenceId)||(ack_sequence_id > kSocketMaxSequenceId)) {
                    SetSession(nullptr); //缓冲区错误
                    return false;
                }
                SetReadBufFlag(kReadBufFlagSequenceId);
            }
                break;
            case kReadBufFlagIsAcks:
            {
                int uint_size;
                if (!CanGetCompressUInt(uint_size)) {
                    return true;
                }
                if (uint_size == 0) {
                    SetSession(nullptr); //缓冲区错误
                    return false;
                }
                Read(uint_buf, uint_size);
                ReadCompressUIntValue(_ack_count, uint_buf, uint_size);
                SetReadBufFlag(kReadBufFlagIsAckCount);
            }
                break;
            case kReadBufFlagIsAckCount:
            {
                if (_ack_count == 0) {
                    SetSession(nullptr); //缓冲区错误
                    return false;
                }
                int uint_size;
                if (!CanGetCompressUInt(uint_size)) {
                    return true;
                }
                if (uint_size == 0) {
                    SetSession(nullptr); //缓冲区错误
                    return false;
                }
                Read(uint_buf, uint_size);
                
                uint32_t ack_sequence_id;
                ReadCompressUIntValue(ack_sequence_id, uint_buf, uint_size);
                if ((ack_sequence_id < kSocketMinSequenceId)||(ack_sequence_id > kSocketMaxSequenceId)) {
                    SetSession(nullptr); //缓冲区错误
                    return false;
                }
                --_ack_count;
                if (_ack_count == 0) {
                    SetReadBufFlag(kReadBufFlagSequenceId);
                }
            }
                break;
            default:
            {
                return false;
            }
                break;




        }
    }
    


}
