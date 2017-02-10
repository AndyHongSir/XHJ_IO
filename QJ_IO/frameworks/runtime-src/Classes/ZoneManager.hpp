//
//  ZoneManager.hpp
//  QJ_IO
//
//  Created by Andy Hong on 2017/2/8.
//
//

#ifndef ZoneManager_hpp
#define ZoneManager_hpp

#include "MainScene.h"
class ZoneManager : public cocos2d::Ref
{
public:
    ZoneManager();
    ~ZoneManager();
    
    void update(float dt);
    
    void setGameLayer( MainScene *game_layer){
        _game_layer = game_layer;
    }
    
    void generateZone();
    
    void removeZone();
    
    static ZoneManager* getInstance();
    
    bool init();
    
    
    
private:
    MainScene *_game_layer;
    static ZoneManager* m_pInstance;
    //游戏生命周期
    float _time;
    float _time2;
    //双倍区域出现的时间
    float _appear_time;
    
    Sprite *_zone;
    
    int _seed;
};

#endif /* ZoneManager_hpp */
