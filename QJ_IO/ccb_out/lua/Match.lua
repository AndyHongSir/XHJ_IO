local CCBLoader = require("CCB.Loader")
local Oop = require("Oop.init")

--[[
Callbacks:
    

Members:
    self.lbl_player_1 CCLabelTTF
    self.lbl_player_2 CCLabelTTF
    self.lbl_player_3 CCLabelTTF
]]--
local Match = Oop.class("Match", function(owner)
    -- @param "UI.ccb" => code root
    -- @param "ccb/"   => ccbi folder
    CCBLoader:setRootPath("UI/ccb", "")
    return CCBLoader:load("Match", owner)
end)

function Match:ctor()
    -- @TODO: constructor
    --self:init()
end

--[[
function Match:init()
    self:registerScriptHandler(function (event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end)
end

function Match:onEnter()
end

function Match:onExit()
end
]]--



return Match