//
//  Player.hpp
//  QJ_IO
//
//  Created by Andy Hong on 2016/12/30.
//
//

#ifndef Player_hpp
#define Player_hpp
#include "cocos2d.h"

USING_NS_CC;


class MainScene;
//
// Effect
//
class EffectSprite;

class Effect : public cocos2d::Ref
{
public:
    cocos2d::GLProgramState* getGLProgramState() const { return _glprogramstate; }
    virtual void setTarget(EffectSprite *sprite){}
    
protected:
    bool initGLProgramState(const std::string &fragmentFilename);
    Effect();
    virtual ~Effect();
    cocos2d::GLProgramState* _glprogramstate;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    std::string _fragSource;
    cocos2d::EventListenerCustom* _backgroundListener;
#endif
};

static int tuple_sort( const std::tuple<ssize_t,Effect*,QuadCommand> &tuple1, const std::tuple<ssize_t,Effect*,QuadCommand> &tuple2 )
{
    return std::get<0>(tuple1) < std::get<0>(tuple2);
}

class EffectSprite : public Sprite
{
public:
    static EffectSprite *create(const std::string& filename) {
        auto ret = new (std::nothrow) EffectSprite;
        if(ret && ret->initWithFile(filename)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_RELEASE(ret);
        return nullptr;
    }
    
    void setEffect(Effect* effect) {
        if(_defaultEffect != effect) {
            effect->setTarget(this);
            
            CC_SAFE_RELEASE(_defaultEffect);
            _defaultEffect = effect;
            CC_SAFE_RETAIN(_defaultEffect);
            
            setGLProgramState(_defaultEffect->getGLProgramState());
        }
    }
    void addEffect(Effect *effect, ssize_t order) {
        effect->retain();
        effect->setTarget(this);
        
        _effects.push_back(std::make_tuple(order,effect,QuadCommand()));
        
        std::sort(std::begin(_effects), std::end(_effects), tuple_sort);
    }
    
    void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override
    {
#if CC_USE_CULLING
        // Don't do calculate the culling if the transform was not updated
        _insideBounds = (flags & FLAGS_TRANSFORM_DIRTY) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
        
        if(_insideBounds)
#endif
        {
            // negative effects: order < 0
            int idx=0;
            for(auto &effect : _effects) {
                
                if(std::get<0>(effect) >=0)
                    break;
                auto glProgramState = std::get<1>(effect)->getGLProgramState();
                if (glProgramState)
                {
                    QuadCommand &q = std::get<2>(effect);
                    q.init(_globalZOrder, _texture->getName(), glProgramState, _blendFunc, &_quad, 1, transform, flags);
                    renderer->addCommand(&q);
                }
                idx++;
            }
            
            // normal effect: order == 0
            _trianglesCommand.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, _polyInfo.triangles, transform, flags);
            renderer->addCommand(&_trianglesCommand);
            
            // postive effects: oder >= 0
            for(auto it = std::begin(_effects)+idx; it != std::end(_effects); ++it) {
                QuadCommand &q = std::get<2>(*it);
                q.init(_globalZOrder, _texture->getName(), std::get<1>(*it)->getGLProgramState(), _blendFunc, &_quad, 1, transform, flags);
                renderer->addCommand(&q);
                idx++;
            }
        }
    }
protected:
    EffectSprite() : _defaultEffect(nullptr)
    {
        _effects.reserve(2);
    }
    ~EffectSprite() {
        for(auto &tuple : _effects) {
            std::get<1>(tuple)->release();
        }
        CC_SAFE_RELEASE(_defaultEffect);
    }
    
    std::vector<std::tuple<ssize_t,Effect*,QuadCommand>> _effects;
    Effect* _defaultEffect;
};




class Player : public cocos2d::Node
{
public:
    //玩家生命状态
    enum class PlayerLifeState {
        alive,//正常活着
        deaded,//刚死亡
        reviving,//复活中
        umharmed//刚复活时不受伤害
    };
    
    Player();
    static Player* create (const std::string& filename,const std::string& rolename,bool isMySelf);
    
    // bool isOverBoundary();
    virtual bool init(const std::string& filename,const std::string& rolename,bool isMySelf) ;
    virtual void update(float dt) ;
    
    bool isOverBoundary(const Vec2&  pos);
    
    virtual EffectSprite *getSprite(){
        return _sp;
    }
    
    virtual void  setLifeState(PlayerLifeState state);
    PlayerLifeState getLifeState(){
        return _lifeState;
    }
    
    void setGameLayer( MainScene *game_layer){
        _game_layer = game_layer;
    }

    
    virtual void setAlphaEffect();
protected:
    cocos2d::Vec2 _direction ;
    float _speed;
    
    float _delay;
    //当前帧率
    int _frame;
    //帧数
    int _random_frame;
    int _random_rotation;
    PlayerLifeState _lifeState;
    //记录死亡时间
    float _dead_time;
    //播放复活倒计时数字的次数
    int _reviveNumTime;
    //无敌时间
    float _umharmed_time;
    bool _is_blink;
    
     MainScene *_game_layer;
    
    bool _isMyself;

private:
   
    int acc_id;
    EffectSprite *_sp;
    Label *_lbl_name;
    
};

#endif /* Player_hpp */
