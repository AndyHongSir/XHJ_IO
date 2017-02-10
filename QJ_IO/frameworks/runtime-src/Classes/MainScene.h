//
//  MainScene.hpp
//  QJ_IO
//
//  Created by Andy Hong on 2016/12/30.
//
//

#ifndef MainScene_h
#define MainScene_h

#include "cocos2d.h"
#include "CustomContactListener.hpp"
#include "GLES-Render.h"
#include "Player.hpp"
#include "AIPlayer.hpp"
//#include "BaseSocket.h"
#include "XML.pb.h"

USING_NS_CC;
//NS_CC_BEGIN;


class MyQueryCallback : public b2QueryCallback {
public:
    std::vector<b2Body*> foundBodies;
    
    bool ReportFixture(b2Fixture* fixture) {
        foundBodies.push_back( fixture->GetBody() );
        return true;//keep going to find all fixtures in the query area
    }
};

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    virtual void onEnter() override;
    
    
    virtual void update(float dt) override;
    
    const Vec2& getPlayerPos(){
        
        return _player->getPosition();
    }
    int getBulletNumVisible();
    
    void addBoxBody(Sprite *sprite,Node *body,bool isShapeFromPlist,const std::string& name = "",
                    float scale = 1.0);
    
    bool removeBulletFromBox2D(Node *body);
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
    
    // implement the "static create()" method manually
    
    //播放死亡倒计时
    void showRiviveCountDown(const Vec2 & point ,int number,bool isMyself);
    
    float getScaleRate(){
        return _scaleRate;
    }
    Vec2& getOriginPoint(){
        return _orginPoint;
    }
    
    void setGameOver(){
        _isGameover = true;
    }
    
    void setIsInZone(bool isInZone);
       
    MainScene();
    ~MainScene();
    CREATE_FUNC(MainScene);
protected:
    void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
    cocos2d::CustomCommand _customCmd;
    
private:
    Player *_player;
    std::map<int , Player *> _other_players;
    std::map<int ,::jynetwork::proto::NetBattleOper*> _other_players_data;
    AIPlayer *_ai_player;
    MyContactListener *_contactListener;
    b2World *_world;
    GLESDebugDraw *_debugDraw;
    bool _isGameover;
    bool _isAllReady;
    bool _isShowScore;
    float _gameOverTime ;
 

    float _duration;
    int _score;
    
    float _scaleRate;
    Vec2 _orginPoint;
    
    bool _isInZone;
};
//NS_CC_END;

#endif /* MainScene_hpp */
