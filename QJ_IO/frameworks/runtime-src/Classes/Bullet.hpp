//
//  Bullet.hpp
//  QJ_IO
//
//  Created by Andy Hong on 2016/12/30.
//
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "cocos2d.h"

USING_NS_CC;



class Bullet : public cocos2d::Node
{
public:
    
    enum class BulletType {
        normal,
        quick,
        slow
    };
    
    static Bullet* create (cocos2d::Vec2 direction,BulletType type,float rate,int wave);
    
    bool isOverBoundary();
    void update(float dt);
   
    Sprite *getSprite(){
        return _sp;
    }
    
    const cocos2d::Vec2 & getDirection(){
        return _direction;
    }
    float getSpeed(){
        return _speed;
    }
    
private:
    cocos2d::Vec2 _direction ;
    float _speed;
    float _time;
    float _delay;
    //当前帧率
    int _frame;
    //帧数
    int _random_frame;
    int _random_rotation;
    Sprite *_sp;
    
    BulletType _type;
 
    
};

#endif /* Bullet_hpp */
