//
//  BaseMessage.hpp
//  QJ_IO
//
//  Created by Andy Hong on 2017/1/5.
//
//

#ifndef BaseMessage_hpp
#define BaseMessage_hpp
#include <vector>
#include <google/protobuf/message_lite.h>

const int kTcpRecvBufferSize = 65536;
const int kTcpMsgMaxSize = kTcpRecvBufferSize-10;
const int kTcpCircularBufferSize = kTcpRecvBufferSize;

const uint16_t kSocketMinSequenceId = 2;
const uint16_t kSocketMaxSequenceId = 16000;

const int kReadBufFlagSequenceId = 1;
const int kReadBufFlagMsgSize = 2;
const int kReadBufFlagOpcode = 3;
const int kReadBufFlagMsgRemain = 4;
const int kReadBufFlagIsAck = 5;
const int kReadBufFlagIsAcks = 6;
const int kReadBufFlagIsAckCount = 7;

class BaseSession
{
public:
    virtual void stop() = 0;
    virtual bool HandleMessage(uint16_t opcode, std::shared_ptr<::google::protobuf::MessageLite>& msg) = 0;
    virtual bool ParseMessage(uint16_t opcode, const void* p0, int size0, const void* p1, int size1) = 0;
    
    virtual void OnConnect() = 0;
    virtual void OnDisconnect() = 0;
};

class BaseMessage
{
      typedef std::vector<unsigned char>::size_type size_type;
public:
    
    BaseMessage()
    : _wpos(0)
    , _rpos(0)
    , _data()
    , _read_buf_flag(kReadBufFlagSequenceId)
    , _msg_remaining(0)
    , _opcode(0)
    , _sequence_id(kSocketMinSequenceId)
    , _msg_size(0)
    , _ack_count(0)
    , _session(nullptr)
    {
        _data.resize(4096);
    }
    
    void Resize(size_type bytes)
    {
        _data.resize(bytes);
    }
    
    size_type GetSize() const { return _wpos - _rpos; }
    
    unsigned char* GetBasePointer() { return _data.data(); }
    
    unsigned char* GetReadPointer() { return GetBasePointer() + _rpos; }
    
    unsigned char* GetWritePointer() { return GetBasePointer() + _wpos; }
    
    size_type GetRemainingSpace() const { return _data.size() - _wpos; }
    
     size_type GetMsgSize() const { return _data.size(); }


    bool handleMsg(std::size_t size);
    
    bool handleWriteMsg(std::size_t size);
    
    char* CreateWriteBuf(std::size_t size);
    
   
    void SetSession(BaseSession* session);
    
    void Normalize();
    /// 返回错误的话，需要关闭网络
    bool SendNetMessage(uint16_t opcode, ::google::protobuf::MessageLite *pmessage, bool is_use_crypto = true);

  
    
private:
  
    void reset();
    
    bool CanGetCompressUInt(int& uint_size);
    void SetReadBufFlag(int flag) { _read_buf_flag = flag; }
    bool IsReadBufFlag(int flag) { return (_read_buf_flag & flag); }
    bool Read(void* destination, std::size_t size);
    int _read_buf_flag;
    uint32_t _msg_remaining;
    uint16_t _opcode;
    
    uint32_t _sequence_id;
    uint32_t _msg_size; //msg size or ack sequence id
    uint32_t _ack_count;
    
    size_type _wpos;
    size_type _rpos;
    
    std::vector<unsigned char> _data;
    
    std::size_t body_length_;
    
    BaseSession* _session;
};

#endif /* BaseMessage_hpp */
