//
//  AIPlayer.cpp
//  QJ_IO
//
//  Created by Andy Hong on 2017/1/3.
//
//

#include "AIPlayer.hpp"
#include "BulletManager.hpp"


AIPlayer::AIPlayer()
:_time(0)
,_duration(0)
,_ai_dir(Vec2(0,0))
,_ai_speed(0)
,_seed(0){
    
}


AIPlayer * AIPlayer::create(const std::string& filename){
    AIPlayer *player = new (std::nothrow) AIPlayer();
    if (player && player->init(filename,"AI",false))
    {
        player->_frame = 0;
        player->_frame_total = 0;
        return player;
    }
    CC_SAFE_DELETE(player);
    
    return nullptr;
}



int AIPlayer::minDistance(){
    
    
    auto winSize = Director::getInstance()->getWinSize();
    auto bullets = BulletManager::getInstance()->getBullet();
    int minDis = 1000;
    for (auto iter2 = bullets.begin(); iter2!= bullets.end(); iter2++) {
        auto bullet = *iter2;
        auto pos = bullet->getPosition();
        
        if (pos.x<-0 || pos.x> winSize.width || pos.y<-0 ||pos.y > winSize.height+0 ) {
            continue;
        }
        float dis = pos.distance(getPosition());
        if (dis<minDis) {
            minDis = dis;
        }
    }
    return minDis;

}

int AIPlayer::getBulletNum(const Vec2& targetPos,int radius){
    auto winSize = _game_layer->getContentSize();
    auto bullets = BulletManager::getInstance()->getBullet();
    int bullet_num = 0;
    for (auto iter2 = bullets.begin(); iter2!= bullets.end(); iter2++) {
        auto bullet = *iter2;
        auto pos = bullet->getPosition();
        
        if (pos.x<-0 || pos.x> winSize.width || pos.y<-0 ||pos.y > winSize.height+0 ) {
            continue;
        }
        float dis = pos.distance(targetPos);
        if (dis<radius) {
            bullet_num ++;
        }
    }
    return bullet_num;

}


bool AIPlayer::IsCollision2(const Vec2 & pos,const Vec2& dir , float time){
    
    bool isCollision = false;
    auto bullets = BulletManager::getInstance()->getBullet();
    for (auto iter2 = bullets.begin(); iter2!= bullets.end(); iter2++) {
        auto bullet = *iter2;
        auto dir_ = bullet->getDirection();
        auto bullet_pos = bullet->getPosition();        
        dir_ = dir_ * bullet->getSpeed();
        float A = dir.x-dir_.x;
        float B = dir.y-dir_.y;
        float M = pos.x-bullet_pos.x;
        float N = pos.y-bullet_pos.y;
        float a = A*A+B*B;
        float b = 2*A*M+2*B*N;
        float c = M*M+N*N;
        
        float m = -(b/(2*a));
        
        float min = 0;
        
        float bullet_width =  bullet->getSprite()->getContentSize().width;
        float bullet_height =  bullet->getSprite()->getContentSize().height;
        
        float bullet_radius =   sqrt(bullet_width*bullet_width+bullet_height*bullet_height);
      
        
        float max_distance = 79.101*0.1*_game_layer->getScaleRate()+ bullet_radius;

        
        if( m > time){
            min = a*time*time+b*time+c;
        }
        else if (m>0 && m < time){
            min = (4*a*c-b*b)/(4*a);
            
        }
        else if (m<0){
            min = c;
        }
        min = sqrt(min);
        if (min < max_distance+3) {
            isCollision = true;
            break;
        }
    }
    return isCollision;
}


bool AIPlayer::IsCollision(const Vec2 & pos){
    auto myPos = getPosition();
    auto contentSize = getSprite()->getContentSize();
    std::vector<Vec2> vec_pos;
    auto pos1 = myPos-Vec2(contentSize.width/2,contentSize.height/2);
    auto pos2 = myPos-Vec2(contentSize.width/2,-contentSize.height/2);
    auto pos3 = myPos+Vec2(contentSize.width/2,contentSize.height/2);
    auto pos4 = myPos+Vec2(-contentSize.width/2,contentSize.height/2);
    vec_pos.push_back(pos1);
    vec_pos.push_back(pos2);
    vec_pos.push_back(pos3);
    vec_pos.push_back(pos4);
    for (int i=0; i<4; i++) {
        auto pos_ = vec_pos.at(i);
        auto dir = pos_-getPosition();
        dir.normalize();
        dir = dir*10;
        auto bullets = BulletManager::getInstance()->getBullet();
        for (auto iter2 = bullets.begin(); iter2!= bullets.end(); iter2++) {
            auto bullet = *iter2;
            auto dir_ = bullet->getDirection();
            auto bullet_pos = bullet->getPosition();
            
            dir_ = dir_ * bullet->getSpeed();
            if ((dir.y+dir.x*(dir_.x-dir_.y))!=0) {
                float t2 = ((pos_.x-bullet_pos.x)*dir.y-(pos_.y-bullet_pos.y)*dir.x)/(dir.y+dir.x*(dir_.x-dir_.y));
                if (dir.x != 0) {
                    float t1 = (dir_.x*t2+bullet_pos.x-pos_.x)/dir.x;
                    
                    if (t1>0 && t2>0) {
                        //                    log("t1=%f,t2=%f",t1,t2);
                        auto pos_end = dir*t1+pos_;
                        //                    log("x=%f,y=%f",pos_end.x,pos_end.y);
                        if (!isOverBoundary(pos_end)) {
                            if(fabs(t1-t2)<40){
                                return  true;
                            }
                            
                        }
                        
                    }
                }
            }
        }
        
    }
    return false;
    

    //解方程
    //k1 x+b1 = k2 *y + b2
    //k3 x +b3 = k4 * y + b4
    
    //y = (dir.x,dir.y)*t1 + (myPos.x,myPos.y)
    //y = (dir_.x,dir_.y)*t2 + (bullet_pos.x,bullet_pos.y)
    //dir.x * t1 + myPos.x = dir_.x*t2 + bullet_pos.x
    //dir.y * t1 + myPos.y = dir_.y*t2 + bullet_pos.y
    

    
}
//寻找最近的点，与远离它的方向跑
void AIPlayer::update(float dt)
{
    
    Player::update(dt);
    
    if (_lifeState == Player::PlayerLifeState::deaded) {
        _time = 0;
        _duration = 0;
        _ai_speed = 0;
        _ai_dir = Vec2(0, 0);
        return;
    }
    else if (_lifeState == Player::PlayerLifeState::reviving){
        return;
    }
 
    
    _time += dt;
    
    setPosition(getPosition()+_ai_speed*_ai_dir*_game_layer->getScaleRate());
    
    if (_time > _duration) {
        
       
        
        int min_radius = 0;
        int random_value = 0;
        
        //半径50像素范围内的点
        int bullet_num_40  =  getBulletNum(getPosition(),30);
        
        int bullet_num_80  =  getBulletNum(getPosition(),60);
        
        log("bullet_num_40 = %d",bullet_num_40);
        log("bullet_num_80 = %d",bullet_num_80);
        
        int random_point_num = 0;
        
         if (bullet_num_40 >4 or bullet_num_80 >15)
         {
             min_radius = 10;
             random_value = 25;
             random_point_num = 100;

         }
        
        else if (bullet_num_40 >2 or bullet_num_80 >10) {
            min_radius = 20;
            random_value = 30;
            random_point_num = 80;
        }
        else if (bullet_num_40 <= 0 && bullet_num_80 <= 1){
            min_radius = 40;
            random_value = 60;
            random_point_num = 20;
        }
        else{
            min_radius = 30;
            random_value = 45;
            random_point_num = 50;
        }
        
        int radius = rand()%random_value+min_radius;
        
        
        random_point_num += 20;
        
        
        bool bFound = false;
        
        for(int i=0;i<random_point_num;i++){
            
            
            // 随机角度
            float rais = (rand()%360)*M_PI/180;
            
            //AI目标点位置
            auto pos =  getPosition() + Vec2(radius*cos(rais),radius*sin(rais));
            
            if (isOverBoundary(pos)) {
                continue;
            }
            
            //检查此位置是否会与子弹碰撞
            
            auto dir = Vec2(radius*cos(rais),radius*sin(rais));
            
            _ai_speed = ((rand()%250)+250)/100*_game_layer->getScaleRate(); // 2.5;
            
            float cost_time = dir.length()/_ai_speed;
            
            dir.normalize();
            
            if (!IsCollision2(getPosition(), dir*_ai_speed, cost_time)) {
                _ai_dir = dir;
                _duration = cost_time/60.0;
                bFound = true;
                break;
            }
            
        }
        if (bFound) {
             _time = 0;
            
        }
        
        
    }
 
    
}
