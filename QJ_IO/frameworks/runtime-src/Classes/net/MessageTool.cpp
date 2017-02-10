//
//  MessageTool.cpp
//  QJ_IO
//
//  Created by Andy Hong on 2017/1/6.
//
//

#include "MessageTool.hpp"
#include <boost/smart_ptr.hpp>
#include <boost/unordered_map.hpp>


#include "MessageHeader.pb.h"
#include "CSMessage.pb.h"
#include "SCMessage.pb.h"
#include "StoC.pb.h"

using namespace jynetwork;

namespace qj {

bool CreateCMessage(uint16_t opcode, std::shared_ptr< ::google::protobuf::MessageLite >& msg)
{
    try
    {
        switch (opcode)
        {
            case jynetwork::proto::eCSMessagePing:
            {
                msg = std::make_shared< proto::CSMessagePing>();
                return true;
            }
                break;
            case jynetwork::proto::eCSMessageLoginAuth:
            {
                msg = std::make_shared< proto::CSMessageLoginAuth>();
                return true;
            }
                break;
            case jynetwork::proto::eCSMessageGateAuth:
            {
                msg = std::make_shared< proto::CSMessageGateAuth>();
                return true;
            }
                break;
            case jynetwork::proto::eCSMessageCreateCharInfo:
            {
                msg = std::make_shared< proto::CSMessageCreateCharInfo>();
                return true;
            }
                break;
            case jynetwork::proto::eCSMessageCreateCharJob:
            {
                msg = std::make_shared< proto::CSMessageCreateCharJob>();
                return true;
            }
                break;
            case jynetwork::proto::eCSMessageBattleResult:
            {
                msg = std::make_shared< proto::CSMessageBattleResult>();
                return true;
            }
                break;
            case jynetwork::proto::eCSMessageClientOperation:
            {
                msg = std::make_shared< proto::CSMessageClientOperation>();
                return true;
            }
                break;
            case jynetwork::proto::eCSMessageBattleBegin:
            {
                msg = std::make_shared< proto::CSMessageBattleBegin>();
                return true;
            }
                break;
            case jynetwork::proto::eCSMessageGMCommond:
            {
                msg = std::make_shared< proto::CSMessageGMCommond>();
                return true;
            }
                break;
            case jynetwork::proto::eCSMessageRankList:
            {
                msg = std::make_shared< proto::CSMessageRankList>();
                return true;
            }
                break;
            case jynetwork::proto::eCSMessagePlayerQuery:
            {
                msg = std::make_shared< proto::CSMessagePlayerQuery>();
                return true;
            }
                break;
            case jynetwork::proto::eCSMessageChat:
            {
                msg = std::make_shared< proto::CSMessageChat>();
                return true;
            }
                break;
            case jynetwork::proto::eCSMessageNetBattleBegin:
            {
                msg = std::make_shared< proto::CSMessageNetBattleBegin>();
                return true;
            }
                break;
            case jynetwork::proto::eCSMessageNetBattleOper:
            {
                msg = std::make_shared< proto::CSMessageNetBattleOper>();
                return true;
            }
                break;
            case jynetwork::proto::eCSMessageArenaBattleBegin:
            {
                msg = std::make_shared< proto::CSMessageArenaBattleBegin>();
                return true;
            }
                break;
            case jynetwork::proto::eCSMessageCorpsOper:
            {
                msg = std::make_shared< proto::CSMessageCorpsOper>();
                return true;
            }
                break;
            default:
#ifdef __NET_PACKET_DEBUG__
            {
                boost::unordered_map<uint16_t, std::string>::iterator iteropcode;
                std::string strOpcode;
                iteropcode = g_map_opcode_c.find(opcode);
                if (iteropcode == g_map_opcode_c.end())
                {
                    strOpcode = "CMSG_UNKNOW";
                } else {
                    strOpcode = iteropcode->second;
                }
#ifdef _IN_CLIENT_BUILD_
                cocos2d::log("CreateCMessage not found %s", strOpcode.c_str());
#endif
            }
#endif
                break;
        }
        return false;
    }
    catch(std::bad_alloc)
    {
#ifndef _IN_CLIENT_BUILD_
        //        ErrorOnMemoryFull();
#endif
        return false;
    }
    return false;
}

bool CreateSMessage(uint16_t opcode, std::shared_ptr< ::google::protobuf::MessageLite >& msg)
{
    try
    {
        switch (opcode)
        {
            case proto::eSCMessageLoginAuth:
            {
                msg = std::make_shared< proto::SCMessageLoginAuth>();
                return true;
            }
                break;
            case proto::eSCMessageGateAuth:
            {
                msg = std::make_shared< proto::SCMessageGateAuth>();
                return true;
            }
                break;
            case proto::eSCUserDetailInfo:
            {
                msg = std::make_shared< proto::SCUserDetailInfo>();
                return true;
            }
                break;
            case proto::eSCMessageOperationResult:
            {
                msg = std::make_shared< proto::SCMessageOperationResult>();
                return true;
            }
                break;
            case proto::eCSMessageClientOperation:
            {
                msg = std::make_shared< proto::CSMessageClientOperation>();
                return true;
            }
                break;
            case proto::eSCMessageBattleReward:
            {
                msg = std::make_shared< proto::SCMessageBattleReward>();
                return true;
            }
                break;
            case proto::eSCMessageBattleRewardEnd:
            {
                msg = std::make_shared< proto::SCMessageBattleRewardEnd>();
                return true;
            }
                break;
            case proto::eSCOpponentDetailInfo:
            {
                msg = std::make_shared< proto::SCOpponentDetailInfo>();
                return true;
            }
                break;
            case proto::eSCMessagePong:
            {
                msg = std::make_shared< proto::SCMessagePong>();
                return true;
            }
                break;
            case proto::eSCMessageBattlePrepare:
            {
                msg = std::make_shared< proto::SCMessageBattlePrepare>();
                return true;
            }
                break;
            case proto::eSCMessageShopItem:
            {
                msg = std::make_shared< proto::SCMessageShopItem>();
                return true;
            }
                break;
            case proto::eSCMessageMail:
            {
                msg = std::make_shared< proto::SCMessageMail>();
                return true;
            }
                break;
            case proto::eSCMessageBattleSweepReward:
            {
                msg = std::make_shared< proto::SCMessageBattleSweepReward>();
                return true;
            }
            case proto::eSCMessageRankList:
            {
                msg = std::make_shared< proto::SCMessageRankList>();
                return true;
            }
                break;
            case proto::eSCMessageFriendList:
            {
                msg = std::make_shared< proto::SCMessageFriendList>();
                return true;
            }
                break;
            case proto::eSCQueryDetailInfo:
            {
                msg = std::make_shared< proto::SCQueryDetailInfo>();
                return true;
            }
                break;
            case proto::eSCMessageCorpsOper:
            {
                msg = std::make_shared< proto::SCMessageCorpsOper>();
                return true;
            }
                break;
            case proto::eCSMessageChat:
            {
                msg = std::make_shared< proto::CSMessageChat>();
                return true;
            }
                break;
            case proto::eSCMessageNetBattlePrepare:
            {
                msg = std::make_shared< proto::SCMessageNetBattlePrepare>();
                return true;
            }
                break;
            case proto::eSCMessageNetBattleOper:
            {
                msg = std::make_shared< proto::SCMessageNetBattleOper>();
                return true;
            }
                break;
            case proto::eSCMessageCorpsList:
            {
                msg = std::make_shared< proto::SCMessageCorpsList>();
                return true;
            }
                break;
            case proto::eSCMessageCorpsInfo:
            {
                msg = std::make_shared< proto::SCMessageCorpsInfo>();
                return true;
            }
                break;
                
                break;
            default:
            {
#ifdef __NET_PACKET_DEBUG__
                boost::unordered_map<uint16_t, std::string>::iterator iteropcode;
                std::string strOpcode;
                iteropcode = g_map_opcode_s.find(opcode);
                if (iteropcode == g_map_opcode_s.end())
                {
                    strOpcode = "SMSG_UNKNOW";
                    strOpcode += std::string(" ") + ConvertToString(opcode);
                } else {
                    strOpcode = iteropcode->second;
                }
#ifdef _IN_CLIENT_BUILD_
                cocos2d::log("CreateSMessage not found %s", strOpcode.c_str());
#endif
#endif
            }
                break;
        }
        return false;
    }
    catch(std::bad_alloc)
    {
#ifndef _IN_CLIENT_BUILD_
        //        ErrorOnMemoryFull();
#endif
        return false;
    }
    return false;
}
}
