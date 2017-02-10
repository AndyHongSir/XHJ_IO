//
//  CppToLua.cpp
//  QJ_IO
//
//  Created by Andy Hong on 2017/1/20.
//
//

#include "CppToLua.h"
#include "BaseSocket.h"
#include "MessageTool.hpp"
#include "DataDoc.h"
#include "MainScene.h"

QjDataInfo* QjDataInfo::m_pInstance = nullptr;
QjDataInfo::CGarbo QjDataInfo::m_garbo;

QjDataInfo::QjDataInfo(){
    
}

QjDataInfo::~QjDataInfo(){
    
}

QjDataInfo* QjDataInfo::getInstance(){
     if ( m_pInstance == nullptr )
     {
         m_pInstance = new(std::nothrow) QjDataInfo();
     }
     return m_pInstance;

}

//获取玩家分数
int QjDataInfo::GetPlayerScore(int accid){
    return DataDoc::getInstance()->getPlayerScore(accid);
}
//获取玩家名字，自己或者对手的
std::string QjDataInfo::GetPlayerName(int accid){
    if (accid == GetPlayerAccId()) {
        auto playerInfo =  DataDoc::getInstance()->getPlayerInfo();
        if(playerInfo){
//            if (!playerInfo->has_sname()) {
//                playerInfo->set_sname(StringUtils::format("player%d",accid));
//            }
//            
            return StringUtils::format("player%d",accid);
        }
    }
    else{
        auto& data = DataDoc::getInstance()->getRivalInfo();
        for(auto iter = data.begin();iter != data.end();iter++){
            
            if((*iter)->acc_id() == accid){
                return StringUtils::format("player%d",accid);
            }
           
        }
    }
    return "";
}


void QjDataInfo::ToGameScene(){
    auto  scene = MainScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

int QjDataInfo::GetRivalNum(){
    auto rivalInfo = DataDoc::getInstance()->getRivalInfo();
    
    return rivalInfo.size();
  
}

int QjDataInfo::GetPlayerAccId(){
    auto playerInfo =  DataDoc::getInstance()->getPlayerInfo();
    if(playerInfo){
         return playerInfo->acc_id();
    }
    return 0;
   
}

int QjDataInfo::GetRivalAccId(int index){
    auto rivalInfo = DataDoc::getInstance()->getRivalInfo();
    if (index>0 && index <= rivalInfo.size()) {
        return rivalInfo.at(index-1)->acc_id();
    }
    return 0;
}

///////////////////////////////////////////////////////////////
QjSocket* QjSocket::m_pInstance = nullptr;
QjSocket::CGarbo QjSocket::m_garbo;

QjSocket::QjSocket()

{
}

QjSocket::~QjSocket()
{
}

QjSocket* QjSocket::getInstance()
{
    if ( m_pInstance == nullptr )
    {
        m_pInstance = new(std::nothrow) QjSocket();
    }
    return m_pInstance;
}

void QjSocket::connectDefault(){
     BaseSocket::getInstance()->ConnectDefault();
}

void QjSocket::SendNetBattleOper(int type,int acc_id,float x,float y, float score){
    std::shared_ptr<::google::protobuf::MessageLite > msg;
    if (qj::CreateCMessage(jynetwork::proto::eCSMessageNetBattleOper, msg)) {
        std::shared_ptr<jynetwork::proto::CSMessageNetBattleOper> pmsg = std::dynamic_pointer_cast<jynetwork::proto::CSMessageNetBattleOper>(msg);
        
        ::jynetwork::proto::NetBattleOper* oper = pmsg->add_opers();
        oper->set_oper(::jynetwork::proto::eNetBattleOper(type));
        oper->set_player_id(acc_id);
        oper->set_x(x);
        oper->set_y(y);
        oper->set_now_score(score);
        
  
        
#ifdef __NET_INDICATOR_DEBUG__
        cocos2d::log("ShowIndicatorLayer SendNetBattleBegin");
#endif
        //cocos2d::ActivityIndicatorLayer::ShowIndicatorLayer(kIndicatorDuration);
        BaseSocket::getInstance()->DirectSend(jynetwork::proto::eCSMessageNetBattleOper, msg);
    }

}



void QjSocket::SendNetBattleBegin(int map_id,int net_type){
    
    DataDoc::getInstance()->clearRivalInfo();
    DataDoc::getInstance()->delete_battle_player_data(-1);
    
    std::shared_ptr<::google::protobuf::MessageLite > msg;
    if (qj::CreateCMessage(jynetwork::proto::eCSMessageNetBattleBegin, msg)) {
        std::shared_ptr<jynetwork::proto::CSMessageNetBattleBegin> pmsg = std::dynamic_pointer_cast<jynetwork::proto::CSMessageNetBattleBegin>(msg);
        pmsg->set_map_id(map_id);
        pmsg->set_net_type(net_type);
        
#ifdef __NET_INDICATOR_DEBUG__
        cocos2d::log("ShowIndicatorLayer SendNetBattleBegin");
#endif
        //cocos2d::ActivityIndicatorLayer::ShowIndicatorLayer(kIndicatorDuration);
        BaseSocket::getInstance()->DirectSend(jynetwork::proto::eCSMessageNetBattleBegin, msg);
    }
}



