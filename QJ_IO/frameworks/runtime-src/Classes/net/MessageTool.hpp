//
//  MessageTool.hpp
//  QJ_IO
//
//  Created by Andy Hong on 2017/1/6.
//
//

#ifndef MessageTool_hpp
#define MessageTool_hpp

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/unordered_map.hpp>
#include <boost/assign.hpp>

namespace google {
    namespace protobuf {
        class MessageLite;
    }
}

namespace qj {
    
    bool CreateCMessage(uint16_t opcode, std::shared_ptr< ::google::protobuf::MessageLite >& msg);
    bool CreateSMessage(uint16_t opcode, std::shared_ptr< ::google::protobuf::MessageLite >& msg);
    
#ifdef __NET_PACKET_DEBUG__
    std::string GetOpcodeC(uint16_t opcode);
    std::string GetOpcodeS(uint16_t opcode);
    boost::unordered_map<uint16_t, std::string> InitDebugOpcodes();
    boost::unordered_map<uint16_t, std::string> InitDebugOpcodec();
    void LogPacket(uint32_t len, uint16_t mopcode, const uint8_t* data, uint8_t direction, uint64_t accountid);
#endif
    
}



#endif /* MessageTool_hpp */
