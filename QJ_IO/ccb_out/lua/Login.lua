local CCBLoader = require("CCB.Loader")
local Oop = require("Oop.init")

--[[
Callbacks:
    "onPressButton",

Members:
    self.lblID CCLabelTTF
    self.lblNickName CCLabelTTF
]]--
local Login = Oop.class("Login", function(owner)
    -- @param "UI.ccb" => code root
    -- @param "ccb/"   => ccbi folder
    CCBLoader:setRootPath("UI/ccb", "")
    return CCBLoader:load("Login", owner)
end)

function Login:ctor()
    -- @TODO: constructor
    --self:init()
end

--[[
function Login:init()
    self:registerScriptHandler(function (event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end)
end

function Login:onEnter()
end

function Login:onExit()
end
]]--

function Login:onPressButton(sender, event)
    -- @TODO: implement this
end

return Login