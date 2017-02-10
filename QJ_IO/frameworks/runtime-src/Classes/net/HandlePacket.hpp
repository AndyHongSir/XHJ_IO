//
//  HandlePacket.hpp
//  QJ_IO
//
//  Created by Andy Hong on 2017/1/6.
//
//

#ifndef HandlePacket_hpp
#define HandlePacket_hpp

#include "BaseSocket.h"

bool HandleMessage(BaseSocket* socket, uint16_t opcode, std::shared_ptr<::google::protobuf::MessageLite> msg);


#endif
