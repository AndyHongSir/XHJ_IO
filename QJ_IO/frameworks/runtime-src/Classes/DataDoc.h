//
//  DataDoc.h
//  QJ_IO
//
//  Created by Andy Hong on 2017/1/20.
//
//

#ifndef DataDoc_hpp
#define DataDoc_hpp

//#pragma once
//#include "BaseSocket.h"
//#include "Player.hpp"

//#include "AppDelegate.h"


//#include "TestClass.h"

#include <boost/asio.hpp>

#include "CSMessage.pb.h"
////
#include "SCMessage.pb.h"

#include <set>
//class ::jynetwork::proto::SCUserDetailInfo;
//class std::shared_ptr<::jynetwork::proto::SCQueryDetailInfo;
class DataDoc
{
public:
    
    DataDoc();
    virtual ~DataDoc();
    
    static DataDoc* getInstance()
    {
        if ( m_pInstance == nullptr )
            m_pInstance = new(std::nothrow) DataDoc();
        return m_pInstance;
    }
private:
    static DataDoc* m_pInstance;
    
    class CGarbo
    {
    public:
        ~CGarbo()
        {
            if (DataDoc::m_pInstance != nullptr)
            {
                delete DataDoc::m_pInstance;
                DataDoc::m_pInstance = nullptr;
            }
        }
    };
    
    static CGarbo m_garbo;
    
public:
    std::shared_ptr<::jynetwork::proto::SCUserDetailInfo> _player_info;
    std::vector<jynetwork::proto::SCQueryDetailInfo*> _rival_info;
    
    void setPlayerInfo(std::shared_ptr<::jynetwork::proto::SCUserDetailInfo> player_info);
    void add_rivalInfo(::jynetwork::proto::SCQueryDetailInfo *player_info);
    
    std::shared_ptr<::jynetwork::proto::SCUserDetailInfo> getPlayerInfo(){
        return _player_info;
    }
    std::vector<jynetwork::proto::SCQueryDetailInfo *>& getRivalInfo(){
        return _rival_info;
    }
    std::map<int ,::jynetwork::proto::NetBattleOper*>& getBattlePlayersData(){
        return _other_players_data;
    }
    
    std::shared_ptr<jynetwork::proto::SCMessageNetBattleOper>& getBattlePlayersData2(){
        return _pmsg;
    }
    void delete_battle_player_data(int acc_id);
    
     void add_battle_player_data(std::shared_ptr<jynetwork::proto::SCMessageNetBattleOper> pmsg);
    
    void setPlayerScore(int acc_id,int score);
    
    int  getPlayerScore(int acc_id);
    
    void clearPlayerScore(){
        _player_score.clear();
    }
    
    void addReadyPlayers(int acc_id){
        _ready_players.emplace(acc_id);
    }
    
    std::set<int> getReadyPlayers(){
        return _ready_players;
    }
    
    void clearRivalInfo();
    
    
private:
    
    std::unique_ptr<jynetwork::proto::SCMessageNetBattleOper> _MessageNetBattleOperItem;
    std::unique_ptr<jynetwork::proto::SCMessageNetBattlePrepare> _MessageNetBattlePrepareItem;
    std::map<int ,::jynetwork::proto::NetBattleOper*> _other_players_data;
    
    std::map<int , int >  _player_score;
    
    std::set<int> _ready_players;
    
    std::shared_ptr<jynetwork::proto::SCMessageNetBattleOper> _pmsg;
    
    
    
};

#endif /* DataDoc_hpp */
