//
//  Player.cpp
//  QJ_IO
//
//  Created by Andy Hong on 2016/12/30.
//
//

#include "Player.hpp"

#include "MainScene.h"
#include "CppToLua.h"
#include "DataDoc.h"
//
// EffectSprite
//


class Effect;
//
// Effect
//

bool Effect::initGLProgramState(const std::string &fragmentFilename)
{
    auto fileUtiles = FileUtils::getInstance();
    auto fragmentFullPath = fileUtiles->fullPathForFilename(fragmentFilename);
    auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
    auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    _fragSource = fragSource;
#endif
    
    _glprogramstate = (glprogram == nullptr ? nullptr : GLProgramState::getOrCreateWithGLProgram(glprogram));
    CC_SAFE_RETAIN(_glprogramstate);
    
    return _glprogramstate != nullptr;
}

Effect::Effect()
: _glprogramstate(nullptr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    _backgroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                                      [this](EventCustom*)
                                                      {
                                                          auto glProgram = _glprogramstate->getGLProgram();
                                                          glProgram->reset();
                                                          glProgram->initWithByteArrays(ccPositionTextureColor_noMVP_vert, _fragSource.c_str());
                                                          glProgram->link();
                                                          glProgram->updateUniforms();
                                                      }
                                                      );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backgroundListener, -1);
#endif
}

Effect::~Effect()
{
    CC_SAFE_RELEASE_NULL(_glprogramstate);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backgroundListener);
#endif
}





// Grey
class EffectAlpha : public Effect
{
public:
    CREATE_FUNC(EffectAlpha);
    
protected:
    bool init() {
        initGLProgramState("shaders/alpha.fsh");
        return true;
    }
};


Player::Player()
: _direction(Vec2(0,0))
, _speed(0)
,_dead_time(0)
,_reviveNumTime(0)
,_umharmed_time(0)
,_is_blink(false)
,_lifeState(PlayerLifeState::alive)
{

}

void  Player::setLifeState(PlayerLifeState state){
    if(_lifeState == state){
        return;
    }
    if (_lifeState == PlayerLifeState::umharmed && state == PlayerLifeState::deaded) {
        log("无效的状态设置");
        return;
    }
    if (_lifeState == PlayerLifeState::reviving && state == PlayerLifeState::deaded) {
        log("无效的状态设置");
        return;
    }
     _lifeState = state;
    switch (_lifeState) {
        case PlayerLifeState::deaded :
        {
            
               setVisible(false);
        }
            break;
        case PlayerLifeState::reviving :
        {
            _dead_time = 0;
            _reviveNumTime = 3;
        }
            break;
        case PlayerLifeState::umharmed :
        {
            _umharmed_time = 0;
            _is_blink = false;
        }
            
            break;
        case PlayerLifeState::alive :
        {
            setVisible(true);
        }
            break;
        default:
            break;
    }
}


void Player::update(float dt){
    switch (_lifeState) {
        case PlayerLifeState::deaded :
        {
            setLifeState(PlayerLifeState::reviving);
        }
            break;
        case PlayerLifeState::reviving :
        {
            _dead_time += dt;
            if (_dead_time>=3) {
                setLifeState(PlayerLifeState::umharmed);
            }
            else if(_dead_time>=2){
                if (_reviveNumTime == 1) {
                    //播放死亡倒计时动画
                    _game_layer->showRiviveCountDown(getPosition(), _reviveNumTime,_isMyself);
                    _reviveNumTime--;
                    
                }
            }
            else if(_dead_time>=1){
                if (_reviveNumTime == 2) {
                    //播放死亡倒计时动画
                    _game_layer->showRiviveCountDown(getPosition(), _reviveNumTime,_isMyself);
                    _reviveNumTime--;
                }
            }
            else{
                if (_reviveNumTime == 3) {
                    //播放死亡倒计时动画
                    _game_layer->showRiviveCountDown(getPosition(), _reviveNumTime,_isMyself);
                    _reviveNumTime--;
                }

            }

        }
            break;
        case PlayerLifeState::umharmed :
        {
            if (!_is_blink ) {
                _is_blink = true;
                runAction(Sequence::create(Blink::create(1.0, 30),CallFunc::create([this]{
                    _is_blink = false;
                    this->setLifeState(PlayerLifeState::alive);
                }), NULL));
            }
            
        }

            break;
        case PlayerLifeState::alive :
        {
        }
            break;
        default:
            break;
    }
}

bool Player::isOverBoundary(const Vec2&  pos){
    auto winSize = _game_layer->getContentSize();
    auto scale = _sp->getScale();
    if (pos.x<=_sp->getContentSize().width*scale/2 || pos.x>= winSize.width-_sp->getContentSize().width*scale/2 || pos.y<=_sp->getContentSize().height*scale/2 ||pos.y >= winSize.height-_sp->getContentSize().height*scale/2 ) {
        return true;
    }
    return false;
}


Player * Player::create(const std::string& filename,const std::string& rolename,bool isMySelf){
    Player *player = new (std::nothrow) Player();
    if (player && player->init(filename,rolename, isMySelf))
    {
       
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

void Player::setAlphaEffect(){
    if (_sp) {
        _sp->setOpacity(128);
        //_sp->setEffect(EffectAlpha::create());
    }
}

bool Player::init(const std::string& filename,const std::string& rolename,bool isMySelf){
     bool result = false;
    if(Node::init()){
        auto sp = EffectSprite::create(filename);
        sp->setScale(0.1);
        addChild(sp);
        _sp = sp;
        result = true;
        
        _lbl_name = Label::createWithSystemFont(rolename,"Helvetica", 5);
        _lbl_name->setPosition(0,-10);
        
        if (isMySelf) {
            _lbl_name->setColor(Color3B::GREEN);
        }
        _isMyself =  isMySelf;
        addChild(_lbl_name);

    }
    return result;
   
}
