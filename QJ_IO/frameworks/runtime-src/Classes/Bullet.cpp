//
//  Bullet.cpp
//  QJ_IO
//
//  Created by Andy Hong on 2016/12/30.
//
//

#include "Bullet.hpp"
using namespace std;

Bullet * Bullet::create(cocos2d::Vec2 direction,BulletType type,float rate,int wave){
    Bullet *bullet = new (std::nothrow) Bullet();
    if (bullet )
    {
        string fileName = "";
        float speed = 0;
        switch (type) {
            case BulletType::normal:{
                fileName = "normal_bullet.png";
                speed = 4;
            }
                
                break;
            case BulletType::slow :
            {
                fileName = "slow_bullet.png";
                speed = 2.5;
            }
                break;
            case BulletType::quick :
            {
                fileName = "quick_bullet.png";
                speed = 7;

            }
                                break;
            default:
                break;
        }
        auto sp = Sprite::create(fileName);
        if(sp){
            bullet->addChild(sp);
            bullet->_sp = sp;
        }
        bullet->_direction = direction;
        bullet->_speed = speed/2.5*rate;
        bullet->_type = type;
        
        /*
        auto _lbl_name = Label::createWithSystemFont(StringUtils::format("%d",wave),"Helvetica", 7);
        _lbl_name->setPosition(0,-10);
        bullet->addChild(_lbl_name);
         */

        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return nullptr;
}

bool Bullet::isOverBoundary(){
    auto winSize = Director::getInstance()->getWinSize();
    if (getPosition().x<-40 || getPosition().x> winSize.width+40 || getPosition().y<-40 ||getPosition().y > winSize.height+40 ) {
        if (getPosition().y*_direction.y>0 || getPosition().x*_direction.x>0 ) {
            return true;
        }
        
    }
    return false;
}

void Bullet::update(float dt){
    
    
    this->setPosition(this->getPosition()+_speed*_direction);
    
}
