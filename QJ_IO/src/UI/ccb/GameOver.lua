local CCBLoader = require("CCB.Loader")
local Oop = require("Oop.init")

--[[
Callbacks:
    "onClickLike",

Members:
    self.lbl_player_1 CCLabelTTF
    self.btnLike CCControlButton
]]--
local GameOver = Oop.class("GameOver", function(owner)
    -- @param "UI.ccb" => code root
    -- @param "ccb/"   => ccbi folder
    CCBLoader:setRootPath("UI/ccb", "")
    return CCBLoader:load("GameOver", owner)
end)

function GameOver:ctor()
    -- @TODO: constructor
    --self:init()
end

--[[
function GameOver:init()
    self:registerScriptHandler(function (event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end)
end

function GameOver:onEnter()
end

function GameOver:onExit()
end
]]--

function GameOver:onClickLike(sender, event)
    -- @TODO: implement this
end

return GameOver