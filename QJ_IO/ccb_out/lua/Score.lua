local CCBLoader = require("CCB.Loader")
local Oop = require("Oop.init")

--[[
Callbacks:
    "onGameOver",

Members:
    self.nodeMyScore CCNode
    self.lbl_myscore CCLabelTTF
    self.nodeRank CCNode
    self.lbl_player1 CCLabelTTF
    self.lbl_player2 CCLabelTTF
    self.lbl_player3 CCLabelTTF
    self.lbl_player4 CCLabelTTF
    self.lbl_player5 CCLabelTTF
    self.lbl_player6 CCLabelTTF
    self.lbl_player7 CCLabelTTF
    self.lbl_player8 CCLabelTTF
    self.btnGameOver CCControlButton
]]--
local Score = Oop.class("Score", function(owner)
    -- @param "UI.ccb" => code root
    -- @param "ccb/"   => ccbi folder
    CCBLoader:setRootPath("UI/ccb", "")
    return CCBLoader:load("Score", owner)
end)

function Score:ctor()
    -- @TODO: constructor
    --self:init()
end

--[[
function Score:init()
    self:registerScriptHandler(function (event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end)
end

function Score:onEnter()
end

function Score:onExit()
end
]]--

function Score:onGameOver(sender, event)
    -- @TODO: implement this
end

return Score