//
//  BulletManager.cpp
//  QJ_IO
//
//  Created by Andy Hong on 2016/12/30.
//
//

#include "BulletManager.hpp"

BulletManager::BulletManager()
: _isShooting(false)
,_targetPos(Vec2(0,0))
,_radis(400)
,_time(0)
,_stop(false)
,_seed(1)
,_duration(0)
,_threshold(3.0)
,_wave(0)
,_old_seed(0)
{
    
}

BulletManager::~BulletManager()
{
    
}

BulletManager* BulletManager::getInstance()
{
    if ( m_pInstance == nullptr ) {
        
        //        boost::asio::io_service _io_service;
        m_pInstance = new(std::nothrow) BulletManager();
        
        
        //        std::thread work_thread(std::bind(&boost::asio::io_service::run, &(m_pInstance->GetIoService())));
    }
    return m_pInstance;
}


BulletManager* BulletManager::m_pInstance = nullptr;

void BulletManager::setSeed(int seed){
    _old_seed = seed;
    _seed = seed;
}

int  BulletManager::getSeed(){
    return _old_seed;
}

void BulletManager::generateBullets(){
    
    _wave ++;
    srand(_seed);
    
    _seed++;
    
    //确定是中速还是慢速子弹
    int type = rand()%3;
    
    //cocos2d::log("子弹类型 type = %d",type);
    
    int bullets_num = 0;
    
    switch ((Bullet::BulletType)type) {
        case Bullet::BulletType::normal :
        {
            bullets_num = 100;//80;
            _threshold = 4;
        }
            break;
        case Bullet::BulletType::slow:
        {
            bullets_num = 140;//120;
             _threshold = 6;
        }
            break;
        case Bullet::BulletType::quick :
        {
            bullets_num = 70;//50;
            _threshold = 6;
        }
            break;

        default:
            break;
    }
    
    //获取一个位置
    //480 320
    
    auto winSize = Size(568, 320); //Director::getInstance()->getWinSize();
    float scalerate = _game_layer->getScaleRate();
    Vec2 orignPoint = _game_layer->getOriginPoint();
    //winSize = winSize*scalerate;
    int min_x = winSize.width*1/4.0;
    int max_x = winSize.width*3/4.0;
    int min_y = winSize.height*1/4.0;
    int max_y = winSize.height*3/4.0;
    int x = (rand()%(max_x-min_x)+min_x);
    int y = (rand()%(max_y-min_y)+min_y);
    
    
    
    _targetPos = Vec2(x, y);
    
    //算出最小的半径
    //winSize = winSize*scalerate;
    float min_radis = 0;
    std::vector<Vec2> points ;
    points.push_back(Vec2(0,0));
    points.push_back(Vec2(0,winSize.height));
    points.push_back(Vec2(winSize.width,0));
    points.push_back(Vec2(winSize.width,winSize.height));
    
    for (auto iter = points.begin(); iter!= points.end(); iter++) {
        float len = _targetPos.distance(*iter);
        if (len > min_radis) {
            min_radis = len;
        }
    }
    
    
    _radis = min_radis*scalerate;
    
     _targetPos = _targetPos*scalerate;
    
    for (int i =0;i<bullets_num;i++){
        //要取得[a,b]的随机整数，使用(rand() % (b-a+1))+ a;
        
        //随机半径
        _radis = _radis +(rand()%20)*scalerate;
        
        // 随机角度
        float rais = (rand()%360)*M_PI/180;
        
        
        //子弹的出生点位置
        auto pos =  _targetPos + Vec2(_radis*cos(rais),_radis*sin(rais));
        
         auto winSize = Director::getInstance()->getWinSize();
        
        //log("wave = %d , index = %d ,出生点=%f,%f",_wave , i ,pos.x*568.0/winSize.width,pos.y*568.0/winSize.width);
       
        //子弹的目标点位置
        auto _random_targetPos = Vec2(_targetPos.x+(rand()%100-50)*scalerate,_targetPos.y+(rand()%100-50)*scalerate);
        
        //子弹的方向
        auto dir = _random_targetPos-pos;
        
        dir.normalize();
        
        if ((int)Bullet::BulletType::quick == type) {
            if (dir.y >0 ) {
                continue;
            }
        }
        
        //log("dir=%f,%f",dir.x,dir.y);
        
        auto bullet = Bullet::create(dir,(Bullet::BulletType)type,scalerate,_wave);
        //确定位置
        //随机半径
        
        bullet->setPosition(pos);
        
        _game_layer->addBoxBody(bullet->getSprite(),bullet,false);
        
        _game_layer->addChild(bullet,10);
        
        _bullets.insert(bullet);
    }

}

void BulletManager::launch(){
    //朝着目标发射子弹
    //生成子弹
    _stop = false;
     generateBullets();
}

void BulletManager::updateTargetPos(const Vec2 & targetPos){
    _targetPos = targetPos;
}

void BulletManager::clear(){
    _stop = true;
    for(auto iter = _bullets.begin();iter!= _bullets.end();){
        if(! _game_layer->removeBulletFromBox2D(*iter)){
            //log("移除物理世界的子弹失败");
        }
        (*iter)->removeFromParent();
        iter = _bullets.erase(iter);
        
    }

}

void BulletManager::update(float dt){
    if (_stop ) {
        return;
    }

    
    if (_time>=_threshold) {
        _time = 0;
        generateBullets();
    }
    _duration += dt;
    _time += dt;
    for(auto iter = _bullets.begin();iter!= _bullets.end();){
        (*iter)->update(dt);
        if ((*iter)->isOverBoundary()) {
            
            if(! _game_layer->removeBulletFromBox2D(*iter)){
                //log("移除物理世界的子弹失败");
            }
            (*iter)->removeFromParent();
            iter = _bullets.erase(iter);
        }
        else{
            iter++;
        }

    }

}
