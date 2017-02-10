//
//  AIPlayer.hpp
//  QJ_IO
//
//  Created by Andy Hong on 2017/1/3.
//
//

#ifndef AIPlayer_hpp
#define AIPlayer_hpp

#include "Player.hpp"
USING_NS_CC;

struct MaxRadiusPoint{
    Vec2 point1;
    Vec2 point2;
};



class AIPlayer : public Player
{
public:
    AIPlayer();
    static AIPlayer * create(const std::string& filename);
    virtual void update(float dt) ;
protected:
    //计算距离AI最近的子弹的距离
    int minDistance();
    //检查与子弹不会碰撞
    bool IsCollision(const Vec2 & pos);
    //计算某个像素半径内的子弹数量
    int getBulletNum(const Vec2& targetPos,int radius);
    //寻找半径最大的两个点
    
    MaxRadiusPoint FindPoints();
    
    
    bool IsCollision2(const Vec2 & pos,const Vec2& dir , float time);
    
    
private:
    int _frame;
    int _frame_total;
    Vec2 _target_pos;
    
    float _time;
    float _duration;
    
    float _ai_speed;
    Vec2 _ai_dir;
    
    //_相切距离
    
    float _max_distance;
    
    int _seed;
    
};
#endif /* AIPlayer_hpp */
