//
//  DataDoc.cpp
//  QJ_IO
//
//  Created by Andy Hong on 2017/1/20.
//
//

#include "DataDoc.h"
#include "cocos2d.h"
DataDoc* DataDoc::m_pInstance = nullptr;
DataDoc::CGarbo DataDoc::m_garbo;


DataDoc::DataDoc():
_MessageNetBattleOperItem(new(std::nothrow) jynetwork::proto::SCMessageNetBattleOper),
_MessageNetBattlePrepareItem(new(std::nothrow) jynetwork::proto::SCMessageNetBattlePrepare)
{
    
}
DataDoc::~DataDoc(){
    
}

void DataDoc::setPlayerInfo(std::shared_ptr<::jynetwork::proto::SCUserDetailInfo> player_info){
    _player_info = player_info;
    
}

void DataDoc::setPlayerScore(int acc_id,int score){
    if (score != 0 && acc_id != 0) {
       // cocos2d::log("acc_id = %d,socre = %d",acc_id,score);
        _player_score[acc_id] = score;
      //  _player_score.emplace(acc_id,score);
    }
    
}

int  DataDoc::getPlayerScore(int acc_id){
    auto iter = _player_score.find(acc_id);
    if (iter != _player_score.end()) {
        //cocos2d::log("acc_id = %d,socre = %d",acc_id,iter->second);
        return iter->second;
    }
    return 0;
    
}

void DataDoc::add_battle_player_data(std::shared_ptr<jynetwork::proto::SCMessageNetBattleOper> pmsg){
    if(pmsg){
        _pmsg = pmsg;
        
        for (int i=0; i<pmsg->opers_size(); i++) {
            auto oper = pmsg->mutable_opers(i);
            if(oper){
                
               
                
                if(oper->oper() != ::jynetwork::proto::eNetBattleOper::eBattle_player_score &&
                   oper->oper() != ::jynetwork::proto::eNetBattleOper::eBattle_next_wave){
                   
                    auto iter = _other_players_data.find(oper->player_id());
                    if (iter != _other_players_data.end()) {
                        
                        if(iter->second->oper() ==  ::jynetwork::proto::eNetBattleOper::eBattle_player_relife){
                             cocos2d::log("oper= %d,%d复活状态，",iter->second->oper(),iter->second->player_id());
                        }
                        else{
                           _other_players_data.erase(iter);
                            ::jynetwork::proto::NetBattleOper* item = _MessageNetBattleOperItem->add_opers() ;
                            item->CopyFrom(*oper);
                            _other_players_data.emplace(item->player_id(),item);
                        }
                        
                      
                       
                    }
                    else{
                        ::jynetwork::proto::NetBattleOper* item = _MessageNetBattleOperItem->add_opers() ;
                        item->CopyFrom(*oper);
                         _other_players_data.emplace(item->player_id(),item);
                    }
                    
                }
                
              
            }
            
        }
    }
}

void DataDoc::delete_battle_player_data(int acc_id){
    if (acc_id == -1) {
        _other_players_data.clear();
    }
    {
        auto iter = _other_players_data.find(acc_id);
        if (iter != _other_players_data.end()) {
            _other_players_data.erase(iter);
        }

    }
  
}

void DataDoc::clearRivalInfo(){
    _rival_info.clear();
}

void DataDoc::add_rivalInfo(jynetwork::proto::SCQueryDetailInfo * player_info_){
    
   
    ::jynetwork::proto::SCQueryDetailInfo*  player_info = _MessageNetBattlePrepareItem->add_friend_detail() ;
    player_info->CopyFrom(*player_info_);
    
    bool isRepeated = false;
    for (auto iter = _rival_info.begin(); iter!= _rival_info.end();iter++) {
        if ((*iter)->acc_id() ==player_info->acc_id()){
            isRepeated = true;
            break;
        }
    }
    if (isRepeated == false) {
        if(_player_info->acc_id() != player_info->acc_id()){
            //cocos2d::log("添加了对手%d",player_info->acc_id());
            _rival_info.push_back(player_info);
        }
    }
    
}
