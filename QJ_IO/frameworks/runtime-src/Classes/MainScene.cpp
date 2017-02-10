//
//  MainScene.cpp
//  QJ_IO
//
//  Created by Andy Hong on 2016/12/30.
//
//

#include "MainScene.h"
#define PTM_RATIO 32
#include "BulletManager.hpp"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "DataDoc.h"
#include "CppToLua.h"
#include "GB2ShapeCache-x.h"
#include "ui/CocosGUI.h"
#include "ZoneManager.hpp"
USING_NS_CC;
using namespace cocos2d::ui;
Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    const float kVirtualScreenWidth = 568.0f ;
    const float kVirtualScreenHeight = 320.0f;
    
    auto winSize = Director::getInstance()->getWinSize();
    
    float rate = kVirtualScreenWidth/kVirtualScreenHeight;
    
    float rate1 = winSize.width/winSize.height;
    
    float height,width ;
    float pos_x,pos_y;
    
    if (rate1>=rate) {
        
        
        //太长了
        /*
         
         高度固定
         
         x/h = rate
         
         */
        
        width = winSize.height*rate;
        height = winSize.height;
        
        pos_x = (winSize.width-width)/2.0;
        pos_y = 0;
    }
    else{
        width = winSize.width;
        height = winSize.width/rate;
        pos_x = 0;
        pos_y = (winSize.height-height)/2.0;
    }
   
   
    
    auto bg_layer =  cocos2d::LayerColor::create(Color4B(50, 50, 50, 200),width,height);
    
    bg_layer->setAnchorPoint(Vec2(0, 0));
    
      // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    
    
    layer->setContentSize(Size(width, height));
    
    layer->setPosition(pos_x,pos_y);
    
    layer->setAnchorPoint(Vec2(0, 0));
    
    
    layer->_scaleRate = width/kVirtualScreenWidth;
    
    layer->_orginPoint = Vec2(pos_x,pos_y);
    
    layer->setColor(Color3B::WHITE);
    
    //layer->setColor(Color3B::GRAY);

    layer->addChild(bg_layer,-1);
    // add layer as a child to scene
    
    
    
    auto bg_sp = Sprite::create("di.png");
    if (bg_sp) {
        bg_sp->setAnchorPoint(Vec2(0.0,0.0));
        bg_sp->setScale(1.0/2.0*layer->_scaleRate);
        layer->addChild(bg_sp,0);
    }
    
    if (pos_x > 0) {
        auto bg_layer_1 = cocos2d::LayerColor::create(Color4B(0, 0, 0, 255),pos_x,height);
        bg_layer_1->setPosition(Vec2(0, 0));
         bg_layer_1->setAnchorPoint(Vec2(0, 0));
        scene->addChild(bg_layer_1,99);
        auto bg_layer_2 = cocos2d::LayerColor::create(Color4B(0, 0, 0, 255),pos_x,height);
        bg_layer_2->setAnchorPoint(Vec2(0, 0));
        bg_layer_2->setPosition(Vec2(width+pos_x, 0));
        scene->addChild(bg_layer_2,99);
    }
    else if (pos_y > 0){
        auto bg_layer_1 = cocos2d::LayerColor::create(Color4B(0, 0, 0, 255),width,pos_y);
        bg_layer_1->setPosition(Vec2(0, 0));
        bg_layer_1->setAnchorPoint(Vec2(0, 0));
        scene->addChild(bg_layer_1,99);
        auto bg_layer_2 = cocos2d::LayerColor::create(Color4B(0, 0, 0, 255),width,pos_y);
        bg_layer_2->setAnchorPoint(Vec2(0, 0));
        bg_layer_2->setPosition(Vec2(0, pos_y+height));
        scene->addChild(bg_layer_2,99);

    }
    
    layer->setTag(99);
    
    scene->addChild(layer,1);
    
    // return the scene
    return scene;
}

MainScene::MainScene()
:_duration(0)
,_isGameover(false)
,_score(0)
,_scaleRate(0)
,_orginPoint(Vec2(0,0))
,_gameOverTime(0)
,_isAllReady(false)
,_isShowScore(false)
,_player(nullptr)
{
    
}

MainScene::~MainScene(){
    
}

void MainScene::addBoxBody(Sprite *sprite,Node *body,bool isShapeFromPlist,const std::string& name,
                           float scale) {
    b2BodyDef spriteBodyDef;
    spriteBodyDef.type = b2_dynamicBody;
    spriteBodyDef.position.Set(body->getPosition().x/PTM_RATIO, body->getPosition().y/PTM_RATIO);
    spriteBodyDef.userData = body;
    b2Body *spriteBody = _world->CreateBody(&spriteBodyDef);
    
    //isShapeFromPlist = false;
    if (isShapeFromPlist) {
        GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(spriteBody, name,scale);
    }
    else{
        
        
        b2PolygonShape spriteShape;
        spriteShape.SetAsBox(sprite->getContentSize().width*sprite->getScaleX()/PTM_RATIO/2,
                             sprite->getContentSize().height*sprite->getScaleY()/PTM_RATIO/2);
        
        b2FixtureDef spriteShapeDef;
        spriteShapeDef.shape = &spriteShape;
        spriteShapeDef.density = 10.0;
        spriteShapeDef.isSensor = true;
        spriteShapeDef.filter.categoryBits = 10;
        spriteShapeDef.filter.maskBits = 12;
        spriteBody->CreateFixture(&spriteShapeDef);

    }
    
    
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
    
    _world = new b2World(gravity);
    
    _world->SetAllowSleeping(false);
    
    // Enable debug draw
    _debugDraw = new GLESDebugDraw( PTM_RATIO );
    _world->SetDebugDraw(_debugDraw);
    
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    _debugDraw->SetFlags(flags);
    
    // Create contact listener
    _contactListener = new MyContactListener();
    _world->SetContactListener(_contactListener);

    
    return true;

}
void MainScene::onEnter(){
    Layer::onEnter();
    
    
    
    auto winSize = getContentSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //精灵帧类,提高效率
    SpriteFrameCache *frameCache=SpriteFrameCache::getInstance();
    
    frameCache->addSpriteFramesWithFile("images.plist");
    
    
    /////////////////////////////
    
    // add "HelloWorld" splash screen"
    /*
    _player = Player::create("xhj.png",QjDataInfo::getInstance()->GetPlayerName(QjDataInfo::getInstance()->GetPlayerAccId()),true);
    
    // position the sprite on the center of the screen
    _player->setPosition(Vec2(winSize.width/2 , winSize.height/2 ));
    
    // add the sprite as a child to this layer
    this->addChild(_player, 0);
    
    _player->setGameLayer(this);
    
    addBoxBody(_player->getSprite(),_player,true,"xhj",0.1);
     */
    
    _other_players.clear();
    
    auto rivalPlayers = DataDoc::getInstance()->getRivalInfo();
    
    for (auto iter = rivalPlayers.begin(); iter != rivalPlayers.end(); iter++) {
        int acc_id = (*iter)->acc_id();
        
        auto _rival_player = Player::create("xhj.png",QjDataInfo::getInstance()->GetPlayerName(acc_id),false);
        _rival_player->setPosition(Vec2(winSize.width/2 , winSize.height/2));
        // add the sprite as a child to this layer
        this->addChild(_rival_player, 0);
        _rival_player->setGameLayer(this);
        
        log("添加了对手 acc_id = %d",acc_id);
        _rival_player->setAlphaEffect();
        _other_players.emplace(acc_id,_rival_player);
    }
    
    
    
     _ai_player = AIPlayer::create("xhj.png");
     
     // position the sprite on the center of the screen
     _ai_player->setPosition(Vec2(winSize.width/2 , winSize.height/2 ));
     _ai_player->setGameLayer(this);
     // add the sprite as a child to this layer
     this->addChild(_ai_player, 0);
    
    
     addBoxBody(_ai_player->getSprite(),_ai_player,true,"xhj",0.1);
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        
        return true;
    };
    
    listener1->onTouchMoved = [=](Touch* touch, Event* event){
        if(_player && (_player->getLifeState() == Player::PlayerLifeState::alive or _player->getLifeState() == Player::PlayerLifeState::umharmed )){
            auto preLocation =  touch->getPreviousLocation();
            auto location =  touch->getLocation();
            auto dir = location-preLocation;
            //dir.normalize();
            if(_player){
                if (dir.length()>1.0 && (!_isGameover)&&_isAllReady) {
                    
                    Vec2 pos = _player->getPosition()+dir;
                    _player->setPosition(pos);
                    
                    auto normalization_pos = (pos)/_scaleRate;
                    //提交标准化坐标点
                    QjSocket::getInstance()->SendNetBattleOper(::jynetwork::proto::eNetBattleOper::eBattle_move,DataDoc::getInstance()->getPlayerInfo()->acc_id(),normalization_pos.x,normalization_pos.y);
                }
                
                
            }
        }
        
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        //        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        //        log("sprite onTouchesEnded.. ");
        
    };
    
    
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    cocos2d::EventListenerCustom* listenerDataSys = cocos2d::EventListenerCustom::create("dataSys", [&](cocos2d::EventCustom *event){
        
        _other_players_data.clear();
        auto& data = DataDoc::getInstance()->getBattlePlayersData();
        for(auto iter = data.begin();iter != data.end();iter++){
            _other_players_data.emplace(iter->first,iter->second);
        }
    });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerDataSys, this);
    
    cocos2d::EventListenerCustom* listenerGameOverSys = cocos2d::EventListenerCustom::create("GameOver", [&](cocos2d::EventCustom *event){
        
        _isGameover = true;
    });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerGameOverSys, this);
    
    
    cocos2d::EventListenerCustom* listenerPlayersReadySys = cocos2d::EventListenerCustom::create("AllPlayersReady", [&](cocos2d::EventCustom *event){
        
        if(!_isAllReady){
            _isAllReady = true;
           this->scheduleUpdate();
        }
        
    });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerPlayersReadySys, this);
    
    BulletManager::getInstance()->setGameLayer(this);
    BulletManager::getInstance()->launch();
    
    ZoneManager::getInstance()->init();
    ZoneManager::getInstance()->setGameLayer(this);
    
 //   auto engine = LuaEngine::getInstance();
 //   engine->executeScriptFile("showScore.lua");
    
    if(DataDoc::getInstance()->getPlayerInfo()){
        
        QjSocket::getInstance()->SendNetBattleOper(::jynetwork::proto::eNetBattleOper::eBattle_next_wave,DataDoc::getInstance()->getPlayerInfo()->acc_id());
    }
    else{
        this->scheduleUpdate();
    }
    
    
    
   
    
}

void MainScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    Layer::draw(renderer, transform, flags);
    
    _customCmd.init(_globalZOrder, transform, flags);
    _customCmd.func = CC_CALLBACK_0(MainScene::onDraw, this, transform, flags);
    renderer->addCommand(&_customCmd);
}

void MainScene::onDraw(const Mat4 &transform, uint32_t flags)
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    
    GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );
    
    _world->DrawDebugData();
    CHECK_GL_ERROR_DEBUG();
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

int MainScene::getBulletNumVisible(){
    //in Step() function
     auto winSize = Director::getInstance()->getWinSize();
    MyQueryCallback queryCallback;
    b2AABB aabb;
    aabb.lowerBound = b2Vec2(0.0, 0.0);
    aabb.upperBound = b2Vec2(winSize.width/PTM_RATIO, winSize.height/PTM_RATIO);
    _world->QueryAABB( &queryCallback, aabb );
    return (int)queryCallback.foundBodies.size();
}

bool MainScene::removeBulletFromBox2D(Node *body){
    
    for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext()) {
        if (b->GetUserData() == body){
             _world->DestroyBody(b);
            //log("移除子弹成功");
            return true;
        }
    }
    return false;
}

//播放死亡倒计时
void MainScene::showRiviveCountDown(const Vec2 & point ,int number,bool isMyself){
    Label * lbl_number = Label::createWithSystemFont(StringUtils::format("%d",number), "Helvetica", 24);
    lbl_number->setScale(0.01);
    lbl_number->setPosition(point);
    if(isMyself){
        lbl_number->setColor(Color3B::GREEN);
    }
    addChild(lbl_number);
    lbl_number->runAction(Sequence::create(ScaleTo::create(0.9, 1),FadeOut::create(0.09),CallFunc::create([lbl_number]{
        lbl_number->removeFromParent();
    }), NULL));
}

void MainScene::setIsInZone(bool isInZone){
    if(_isInZone == isInZone){
        return;
    }
    _isInZone = isInZone;
    if (_isInZone) {
        if (DataDoc::getInstance()->getPlayerInfo()) {
              QjSocket::getInstance()->SendNetBattleOper(::jynetwork::proto::eNetBattleOper::eBattle_player_enter,DataDoc::getInstance()->getPlayerInfo()->acc_id());
        }
       
    }
    else{
        if(DataDoc::getInstance()->getPlayerInfo()){
            QjSocket::getInstance()->SendNetBattleOper(::jynetwork::proto::eNetBattleOper::eBattle_player_leave,DataDoc::getInstance()->getPlayerInfo()->acc_id());
        }
        
    }
    
}

void MainScene::update(float dt) {

    auto winSize = Director::getInstance()->getWinSize();
    
   
    
    _duration += dt;
    
    if (  !_isShowScore && _duration >0.5) {
        _isShowScore = true;
        auto engine = LuaEngine::getInstance();
        engine->executeScriptFile("showScore.lua");

    }
    
    if (_isGameover && _duration>=0 ) {
        
       // auto engine = LuaEngine::getInstance();
        //engine->executeGlobalFunction("g_showBtn");
        //g_showBtn();
        
        Button* button = Button::create("clickme.png",
                                        "clickme_down.png");
        button->setPosition(Vec2(winSize.width / 2.0f, winSize.height / 2.0f ));
  
        button->addClickEventListener([=](Ref* sender){
            DataDoc::getInstance()->clearPlayerScore();
            
             auto engine = LuaEngine::getInstance();
            engine->executeString("kode.facade:send(g_Event.login.open)");
        });
        //button->setName("GameOver");
        
        addChild(button,9999);
        
        
        _duration = -10000;
    }
    
    if (_isGameover) {
        return ;
    }
    
    if (_player) {
        _player->update(dt);
    }
    
    if (_ai_player) {
         _ai_player->update(dt);
    }
 
    
    
    //双倍区域判定

    for (auto rivial_player_iter = _other_players.begin(); rivial_player_iter!= _other_players.end(); rivial_player_iter++) {
         auto _rival_player =  rivial_player_iter->second;
        _rival_player->update(dt);
    }

    if(_other_players_data.size()>0){
        for (auto iter_data = _other_players_data.begin(); iter_data != _other_players_data.end() ; ) {
            
            auto acc_id = iter_data->first;
            auto sec = iter_data->second;
            
            switch (sec->oper()) {
                case ::jynetwork::proto::eNetBattleOper::eBattle_move :
                {
                    auto _rival_player_iter = _other_players.find(acc_id);
                    if (_rival_player_iter != _other_players.end()) {
                        auto _rival_player =  _rival_player_iter->second;
                        
                        //把标准化坐标转化为实际坐标
                        Vec2 real_point = Vec2(sec->x()*_scaleRate,sec->y()*_scaleRate);
                        
                        auto dir = Vec2(real_point.x-_rival_player->getPositionX(), real_point.y-_rival_player->getPositionY());
                        
                        bool couldMove = true;
                        if (fabs(dir.x) <= 3.0 && fabs(dir.y) <= 3.0) {
                            couldMove = false;
                        }
                        
                        
                        if (couldMove) {
                            dir.normalize();
                            dir = dir*5;
                            _rival_player->setPosition(real_point);
                        }

                    }
                    else{
                        //log("找不到 acc_id = %d 的玩家",acc_id);
                    }
                    iter_data++;
                }
                    
                    break;
                case ::jynetwork::proto::eNetBattleOper::eBattle_player_die :
                {
                    log("acc_id=%d的玩家死了",acc_id);
                    if (acc_id != DataDoc::getInstance()->getPlayerInfo()->acc_id()) {
                        auto _rival_player_iter = _other_players.find(acc_id);
                        if (_rival_player_iter != _other_players.end()) {
                            auto _rival_player =  _rival_player_iter->second;
                           // _rival_player->setVisible(false);
                            _rival_player->setLifeState(Player::PlayerLifeState::deaded);
                        }
                    }
                    //iter_data++;
                    //删除死亡数据
                    iter_data = _other_players_data.erase(iter_data);
                    
                    DataDoc::getInstance()->delete_battle_player_data(acc_id);
                    
                }
                    
                    break;
             
                case ::jynetwork::proto::eNetBattleOper::eBattle_player_relife :
                {
                    log("acc_id=%d的玩家 复活了",acc_id);
                    if (acc_id != DataDoc::getInstance()->getPlayerInfo()->acc_id()) {
                        auto _rival_player_iter = _other_players.find(acc_id);
                        if (_rival_player_iter != _other_players.end()) {
                            auto _rival_player =  _rival_player_iter->second;
                            if ( _rival_player) {
                                _rival_player->setLifeState(Player::PlayerLifeState::umharmed);
                            }
                          
                        }
                    }
                    else{
                        
                        _player->setLifeState(Player::PlayerLifeState::umharmed);
                    }
                    //iter_data++;
                    //删除复活数据
                    iter_data = _other_players_data.erase(iter_data);
                    DataDoc::getInstance()->delete_battle_player_data(acc_id);
                    
                }
                    break;
                case ::jynetwork::proto::eNetBattleOper::eBattle_player_score :
                {
                   
                    iter_data++;
                    
                }
                    
                    break;
                default:
                {
                    //log("未知的指令%d",sec->oper());
                    //删除复活数据
                    //iter_data = _other_players_data.erase(iter_data);
                    //DataDoc::getInstance()->delete_battle_player_data(acc_id);
                    iter_data++;
                }
                    break;
            }
        }
    }
    
   
    
    
//    _ai_player->update(dt);
    // Updates the physics simulation for 10 iterations for velocity/position
    _world->Step(dt, 10, 10);
    BulletManager::getInstance()->update(dt);
    ZoneManager::getInstance()->update(dt);
    
    // Loop through all of the Box2D bodies in our Box2D world..
    for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext()) {
        
        // See if there's any user data attached to the Box2D body
        // There should be, since we set it in addBoxBodyForSprite
        if (b->GetUserData() != NULL) {
            
            // We know that the user data is a sprite since we set
            // it that way, so cast it...
            Sprite *sprite = (Sprite *)b->GetUserData();
            
            // Convert the Cocos2D position/rotation of the sprite to the Box2D position/rotation
            b2Vec2 b2Position = b2Vec2(sprite->getPosition().x/PTM_RATIO,
                                       sprite->getPosition().y/PTM_RATIO);
            float32 b2Angle = -1 * CC_DEGREES_TO_RADIANS(sprite->getRotation());
            
            // Update the Box2D position/rotation to match the Cocos2D position/rotation
            b->SetTransform(b2Position, b2Angle);
        }
    }

    
    if(_player && _player->getLifeState() != Player::PlayerLifeState::alive){
        setIsInZone(false);
        return;
    }
    
  
    // Loop through all of the box2d bodies that are currently colliding, that we have
    // gathered with our custom contact listener...
    bool isInZone = false;
    std::vector<MyContact>::iterator pos;
    for(pos = _contactListener->_contacts.begin(); pos != _contactListener->_contacts.end(); ++pos) {
        MyContact contact = *pos;
        
        // Get the box2d bodies for each object
        b2Body *bodyA = contact.fixtureA->GetBody();
        b2Body *bodyB = contact.fixtureB->GetBody();
        if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
            
            auto *spriteA = (Node *) bodyA->GetUserData();
            
            auto *spriteB = (Node *) bodyB->GetUserData();
            
            Bullet *bullet = dynamic_cast<Bullet*>(spriteA);
            
            if (bullet) {

                    auto  *player = dynamic_cast<Player*>(spriteB);
                    if (player) {
                        if (player == _player) {
                            _player->setLifeState(Player::PlayerLifeState::deaded);
                        }
                        else if(player == _ai_player){
                            _ai_player->setLifeState(Player::PlayerLifeState::deaded);
                        }
                    }
            }
            else{
                bullet = dynamic_cast<Bullet*>(spriteB);
                if (bullet) {
                        auto *player = dynamic_cast<Player*>(spriteA);
                        if (player) {
                            if (player == _player) {
                                _player->setLifeState(Player::PlayerLifeState::deaded);
                            }
                            else if(player == _ai_player){
                                _ai_player->setLifeState(Player::PlayerLifeState::deaded);
                            }

                        }
                }
                else{
                    isInZone = true;

                }
                
                
            }

        }
    }
    
    setIsInZone(isInZone);
    
    if(_player && _player->getLifeState() == Player::PlayerLifeState::deaded){
              log("acc_id=%d的玩家死了",DataDoc::getInstance()->getPlayerInfo()->acc_id());
            QjSocket::getInstance()->SendNetBattleOper(::jynetwork::proto::eNetBattleOper::eBattle_player_die,DataDoc::getInstance()->getPlayerInfo()->acc_id());
        
    }
    

}
