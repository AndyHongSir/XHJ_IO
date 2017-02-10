//
//  CppToLua.hpp
//  QJ_IO
//
//  Created by Andy Hong on 2017/1/20.
//
//

#ifndef CppToLua_hpp
#define CppToLua_hpp
//#include "BaseSocket.h"
#include <iostream>
class QjDataInfo
{
public:
    QjDataInfo();
    ~QjDataInfo();
    
    static QjDataInfo* getInstance();
    
private:
    static QjDataInfo* m_pInstance;
    
    class CGarbo
    {
    public:
        ~CGarbo()
        {
            if (QjDataInfo::m_pInstance != nullptr)
            {
                delete QjDataInfo::m_pInstance;
                QjDataInfo::m_pInstance = nullptr;
            }
        }
    };
    
    static CGarbo m_garbo;
    
public:
    
    int GetPlayerAccId();
    
    int GetRivalAccId(int index);
    
    //获取对手的数量
    
    int GetRivalNum();
    
    void ToGameScene();
    
    //获取所有玩家分数
    int GetPlayerScore(int accid);
    //获取所有玩家名字
    std::string GetPlayerName(int accid);
    
private:

    
};


class QjSocket
{
public:
    QjSocket();
    ~QjSocket();
    
    static QjSocket* getInstance();
    
private:
    static QjSocket* m_pInstance;
    
    class CGarbo
    {
    public:
        ~CGarbo()
        {
            if (QjSocket::m_pInstance != nullptr)
            {
                delete QjSocket::m_pInstance;
                QjSocket::m_pInstance = nullptr;
            }
        }
    };
    
    static CGarbo m_garbo;
    
public:
    void connectDefault();
    void SendNetBattleBegin(int map_id, int net_type); //网络战斗请求或取消, net_type(1普通匹配,2局域网匹配,3取消匹配)
    void SendNetBattleOper(int type,int acc_id,float x = 0,float y = 0, float score = 0);

};

#endif /* CppToLua_hpp */
