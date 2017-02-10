#include "AppDelegate.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "audio/include/SimpleAudioEngine.h"
#include "cocos2d.h"
#include "scripting/lua-bindings/manual/lua_module_register.h"
#include "lua_cocos2dx_qj_auto.hpp"

#include "HandlePacket.hpp"
#include "SCMessage.pb.h"
#include "MainScene.h"
#include "GB2ShapeCache-x.h"
using namespace CocosDenshion;

USING_NS_CC;
using namespace std;

const float kVirtualScreenWidth = 568.0f ;
const float kVirtualScreenHeight = 320.0f;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();

#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
    // NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
    RuntimeEngine::getInstance()->end();
#endif

}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // set default FPS
    Director::getInstance()->setAnimationInterval(1.0 / 60.0f);
    
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Fighter");
        director->setOpenGLView(glview);
    }
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    cocos2d::Size size = glview->getFrameSize();
#else
    cocos2d::Size size(640, 1136);
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    glview->setFrameSize(kVirtualScreenWidth, kVirtualScreenHeight);
#endif
    glview->setDesignResolutionSize(kVirtualScreenWidth, kVirtualScreenHeight, ResolutionPolicy::SHOW_ALL);
    
     Director::getInstance()->setContentScaleFactor(2.0);
   
    Director::getInstance()->setDisplayStats(true);
    // register lua module
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);

    register_all_packages();
    register_all_cocos2dx_qj(engine->getLuaStack()->getLuaState());

    LuaStack* stack = engine->getLuaStack();
    stack->setXXTEAKeyAndSign("2dxLua", strlen("2dxLua"), "XXTEA", strlen("XXTEA"));

    //register custom function
    //LuaStack* stack = engine->getLuaStack();
    //register_custom_function(stack->getLuaState());
    
    BaseSocket::getInstance()->SetHandleMessage(HandleMessage);
    
    //50.22.140.18
    //192.168.1.201
    BaseSocket::getInstance()->SetDefaultConnect("192.168.1.201", 20001);
    

//    auto  scene = MainScene::createScene();
//    Director::getInstance()->replaceScene(scene);
    FileUtils::getInstance()->addSearchPath("res/");
    GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("physic.plist");
    
    if (engine->executeScriptFile("src/main.lua"))
    {
        //                return false;
    }
   
    

    
    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
