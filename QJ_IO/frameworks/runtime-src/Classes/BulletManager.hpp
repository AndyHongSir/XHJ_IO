//
//  BulletManager.hpp
//  QJ_IO
//
//  Created by Andy Hong on 2016/12/30.
//
//

#ifndef BulletManager_hpp
#define BulletManager_hpp
#include "Bullet.hpp"
#include "MainScene.h"
class BulletManager : public cocos2d::Ref
{
public:
    BulletManager();
    ~BulletManager();
    void launch();
    
    void updateTargetPos(const Vec2 & targetPos);
    
    void update(float dt);
    
    void generateBullets();
    
    static BulletManager* getInstance();
    
    void setGameLayer( MainScene *game_layer){
        _game_layer = game_layer;
    }
    
    std::set<Bullet *> getBullet(){
        return _bullets;
    }
    
    void setSeed(int seed);
    
    int  getSeed();
    
    void clear();
    
    
    
private:
    std::set<Bullet *> _bullets;
    bool _isShooting;
    int32_t _wave;//当前波数
    Vec2 _targetPos;
    float _radis;
    float _time;
    
    MainScene *_game_layer;
    static BulletManager* m_pInstance;
    bool _stop ;
    int _seed;
    int _old_seed;
    float _duration;
    
    float _threshold ;
    
   
};

#endif /* BulletManager_hpp */
