if kode == nil then return end


local loginController = BaseController:extend{
    name = "loginController2014-12-19";
}
local meta = loginController

local loginModelClass = app.model("login")

local loginModel
local loginView


local function onPressButton(sender,controlEvent)
    
--    local scene = cc.MainScene:createScene()
--    cc.Director:getInstance():replaceScene(scene)
--UI.ccb.Match


    if cc.QjDataInfo:getInstance():GetPlayerAccId() == 0 then
        --cc.QjSocket:getInstance():connectDefault()
        cc.QjDataInfo:getInstance():ToGameScene()
    	return
    end
    
    --Match
    --Score
    
    
    local layer = require("UI.ccb.Match"):new()
    
    local scene = cc.Scene:create()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene)
   
   
   
    --showScore
    --require "showScore"
    
    
   
  -- cc.QjDataInfo:getInstance():ToGameScene()
end



local function pressedClose(sender,controlEvent)

end


local function update(dt)

end

local function onNodeEvent(event)
    if event == "exit" then

--        loginView = nil
    elseif event == "enter" then
         cc.QjSocket:getInstance():connectDefault()
    end
end


local function onLogin()
    loginView:fill()

end

function meta:action_login_open_(notification)
   
    loadSDk = false
    loginModel = loginModelClass.new()

    if ccb["Login"] == nil then
        local Login = {}
        Login["onPressButton"] = onPressButton
        ccb["Login"] = Login
    end

    
    
     cc.Director:getInstance():getTextureCache():removeAllTextures()
    
    --初始化视图－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
    loginView = app.view("login","loginView").new("Login.ccbi",ccb["Login"],false)
    loginView:init(loginModel)

    loginView:registerScriptHandler(onNodeEvent)

    local scene = cc.Scene:create()
    scene:addChild(loginView)

    cc.Director:getInstance():replaceScene(scene)
    
    local eventDispatcher = loginView:getEventDispatcher()

    local eventListener = cc.EventListenerCustom:create("onLogin", onLogin)

    eventDispatcher:addEventListenerWithSceneGraphPriority(eventListener, loginView)

    
end

return meta
