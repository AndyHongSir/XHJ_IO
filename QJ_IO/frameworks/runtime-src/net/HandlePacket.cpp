//
//  HandlePacket.cpp
//  QJ_IO
//
//  Created by Andy Hong on 2017/1/6.
//
//

#include "HandlePacket.hpp"
#include "cocos2d.h"
#include "DataDoc.h"
#include "MainScene.h"
USING_NS_CC;
//using namespace CocosDenshion;

//#define __USE_PROTOBUF_FULL__

bool HandleMessage(BaseSocket* socket, uint16_t opcode, std::shared_ptr< ::google::protobuf::MessageLite> msg)
{   //消息处理的例子,需要按需求改变
#ifdef __NET_PACKET_DEBUG__
    uint32_t nlength = 0;
    if (msg.get()) {
        nlength = msg->ByteSize();
    }
    cocos2d::log(" HandleMessage opcode: %s, length: %d", jysvr::GetOpcodeS(opcode).c_str(), nlength);
#endif
    //    ActivityIndicatorLayer::HideIndicatorLayer();
    
    switch (opcode) {
        case jynetwork::proto::eCSMessageClientOperation:
        {
        }
            break;
        case jynetwork::proto::eSCMessageOperationResult:
        {

        }
            break;
        case jynetwork::proto::eSCMessageLoginAuth:
        {
            auto pmsg = std::dynamic_pointer_cast<jynetwork::proto::SCMessageLoginAuth>(msg);
            if (!pmsg.get()) {
                break;
            }
//#ifdef __NET_PACKET_DEBUG__
//#ifdef __USE_PROTOBUF_FULL__
//            cocos2d::log("HandleMessage eSCMessageLoginAuth");
//            cocos2d::log("%s", pmsg->DebugString().c_str());
//#else
            cocos2d::log("HandleMessage eSCMessageLoginAuth result %d", pmsg->result());
            if (pmsg->has_acc_id()) {
                cocos2d::log("acc_id %d", pmsg->acc_id());
            }
            if (pmsg->has_session_key()) {
                cocos2d::log("session_key %d", pmsg->session_key());
            }
            if (pmsg->has_port()) {
                cocos2d::log("port %d", pmsg->port());
            }
            if (pmsg->has_gate_ip()) {
                cocos2d::log("gate_ip %s", pmsg->gate_ip().c_str());
            }
            if (pmsg->has_user_name()) {
                cocos2d::log("user_name %s", pmsg->user_name().c_str());
            }
//#endif  //__USE_PROTOBUF_FULL__
//#endif
            switch (pmsg->result()) {
                case jynetwork::proto::k_success:
                {
                }
                    break;
                case jynetwork::proto::k_faild:
                case jynetwork::proto::k_version_error:
                case jynetwork::proto::k_session_key_error:
                case jynetwork::proto::k_packet_error:
                {
                    
                }
                    break;
            }
            socket->HandleLoginAuth(pmsg);
        }
            break;
        case jynetwork::proto::eSCMessageGateAuth:
        {
            auto pmsg = std::dynamic_pointer_cast<jynetwork::proto::SCMessageGateAuth>(msg);
            if (!pmsg.get()) {
                break;
            }
#ifdef __NET_PACKET_DEBUG__
#ifdef __USE_PROTOBUF_FULL__
            cocos2d::log("HandleMessage eSCMessageGateAuth");
            cocos2d::log("%s", pmsg->DebugString().c_str());
#else
            cocos2d::log("HandleMessage eSCMessageGateAuth result: %d", pmsg->result());
            if (pmsg->has_acc_id()) {
                cocos2d::log("acc_id %d", pmsg->acc_id());
            }
#endif  //__USE_PROTOBUF_FULL__
#endif
            switch (pmsg->result()) {
                case jynetwork::proto::k_success:
                {
                }
                    break;
                case jynetwork::proto::k_faild:
                case jynetwork::proto::k_version_error:
                case jynetwork::proto::k_session_key_error:
                case jynetwork::proto::k_packet_error:
                {
                }
                    break;
            }
        }
            break;
        case jynetwork::proto::eSCUserDetailInfo:
        {
            auto pmsg = std::dynamic_pointer_cast<jynetwork::proto::SCUserDetailInfo>(msg);
            
      
            if (!pmsg.get()) {
                break;
            }
            
            DataDoc::getInstance()->setPlayerInfo(pmsg);

            cocos2d::log("HandleMessage eSCUserDetailInfo");

            if (pmsg->has_acc_id()) {
                cocos2d::log("acc_id %d", pmsg->acc_id());
            }
            if (pmsg->has_isnewchar()) {
                cocos2d::log("isnewchar %d", pmsg->isnewchar());
            }
            if (pmsg->has_isfulldata()) {
                cocos2d::log("isfulldata %d", pmsg->isfulldata());
            }
            if (pmsg->has_sname()) {
                std::string strs;
                char ct[4];
                int nlen = (int)pmsg->sname().length();
                for (int i=0; i<nlen; ++i) {
                    sprintf(ct, "%02x ", (unsigned char)(pmsg->sname()[i]));
                    strs += ct;
                }
                cocos2d::log("sname %s, hex %s", pmsg->sname().c_str(), strs.c_str());
            }
            if (pmsg->has_guildid()) {
                cocos2d::log("guildid %d", pmsg->guildid());
            }
            if (pmsg->has_viplevel()) {
                cocos2d::log("viplevel %d", pmsg->viplevel());
            }
            if (pmsg->has_vipexp()) {
                cocos2d::log("vipexp %d", pmsg->vipexp());
            }
            if (pmsg->has_money()) {
                cocos2d::log("money %d", pmsg->money());
            }
            if (pmsg->has_diamonds()) {
                cocos2d::log("diamonds %d", pmsg->diamonds());
            }
            if (pmsg->has_charslot()) {
                cocos2d::log("charslot %d", pmsg->charslot());
            }
            if (pmsg->has_guide()) {
                cocos2d::log("guide %d", pmsg->guide());
            }

        }
            break;
        case jynetwork::proto::eSCMessageNetBattlePrepare:
        {
            auto pmsg = std::dynamic_pointer_cast<jynetwork::proto::SCMessageNetBattlePrepare>(msg);
            if (!pmsg.get()) {
                break;
            }
            if (pmsg->result() == ::jynetwork::proto::eOpertionResult::eOper_net_battle_add_player) {
                if (pmsg->friend_detail_size() >0) {
                    
                    for (int i=0; i< pmsg->friend_detail_size(); i++) {
                        ::jynetwork::proto::SCQueryDetailInfo* friend_detail = pmsg->mutable_friend_detail(i);
                        std::shared_ptr<::jynetwork::proto::SCQueryDetailInfo> friend_detail_ptr(friend_detail);
                        DataDoc::getInstance()->add_rivalInfo(friend_detail_ptr);
                    }
                    cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
                        auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
                        cocos2d::EventCustom event("addRival");
                        dispatcher->dispatchEvent(&event);
                        
                    });

                    
                    
                }
            }
            else if (pmsg->result() == ::jynetwork::proto::eOpertionResult::eOper_net_battle_begin){
                //进入战斗界面
                cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
                    //            cocos2d::ActivityIndicatorLayer::ShowIndicatorLayer(kIndicatorDurationShort);
                    auto  scene = MainScene::createScene();
                    Director::getInstance()->replaceScene(scene);
                });

               
            }
            

        }
            break;
            
        case jynetwork::proto::eSCMessageBattleRewardEnd:
        {
            //战斗结束
            
        }
            break;
        case jynetwork::proto::eSCMessageNetBattleOper:
        {
            //战斗中的数据同步
            auto pmsg = std::dynamic_pointer_cast<jynetwork::proto::SCMessageNetBattleOper>(msg);
            if (!pmsg.get()) {
                break;
            }
            
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
                auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
                cocos2d::EventCustom event("dataSys");
                
                event.setUserData((void *)pmsg.get());
                dispatcher->dispatchEvent(&event);
                
            });

           
            
        }
            break;



    }

    

}

