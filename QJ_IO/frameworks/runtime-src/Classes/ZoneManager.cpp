//
//  ZoneManager.cpp
//  QJ_IO
//
//  Created by Andy Hong on 2017/2/8.
//
//

#include "ZoneManager.hpp"
#include "BulletManager.hpp"
ZoneManager* ZoneManager::m_pInstance = nullptr;

ZoneManager::ZoneManager()

:_time(0)
,_time2(0)
,_appear_time(0)
,_zone(nullptr)
{
    
}


ZoneManager::~ZoneManager()
{
    
}

ZoneManager* ZoneManager::getInstance()
{
    if ( m_pInstance == nullptr ) {
        m_pInstance = new(std::nothrow) ZoneManager();
        
    }
    return m_pInstance;
}

bool ZoneManager::init(){
    _time = 0;
    _time2 = 0;
    _appear_time = 0;
    _zone = nullptr;
    _seed = BulletManager::getInstance()->getSeed();
    return true;
}

void ZoneManager::generateZone(){
    
     srand(_seed);
    _seed++;
    _zone = Sprite::create("circle_zone.png");
    
    _zone->setAnchorPoint(Vec2(0.5, 0.5));
    
    float pos_x,pos_y;
    
    //568,320
    
    int min = 50;
    int max = 140;
    
    
    int random_r = rand()%(max-min)+min; //random(min, max);
    
    //log("随机半径%d",random_r);
    
    int random_x = rand()%( 568-random_r*2)+random_r;//random(random_r, 568-random_r);
    
    int random_y = rand()%( 320-random_r*2)+random_r;
    
    pos_x = random_x*_game_layer->getScaleRate();
    
    pos_y = random_y*_game_layer->getScaleRate();
    
    
    _zone->setPosition(Vec2(pos_x, pos_y));
    
    float scale_rate = random_r/250.0;
    
    _game_layer->addBoxBody(_zone, _zone, true,"circle_zone",scale_rate);
    
    _zone->setScale(scale_rate);
    
    _game_layer->addChild(_zone);
}

void ZoneManager::removeZone(){
    if (_zone) {
        _game_layer->removeBulletFromBox2D(_zone);
        _zone->removeFromParent();
        _zone = nullptr;
    }
}



void ZoneManager::update(float dt){
    _time += dt;
    
    _time2 += dt;
    
    if(_zone){
        _appear_time += dt;
    }
    if ( _time>= 10 && _time2 <= 60) {
        
        //log("第%f秒出现",_time2);
        _time = 0;
        _appear_time = 0;       
        generateZone();
        //出现双倍区域
    }
    if (_appear_time > 5.0) {
        //log("第%f秒消失",_time2);
        removeZone();
        _appear_time = 0.0;
    }

    
}


