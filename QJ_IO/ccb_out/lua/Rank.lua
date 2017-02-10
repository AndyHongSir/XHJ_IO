local CCBLoader = require("CCB.Loader")
local Oop = require("Oop.init")

--[[
Callbacks:
    

Members:
    self.nodeList CCNode
]]--
local Rank = Oop.class("Rank", function(owner)
    -- @param "UI.ccb" => code root
    -- @param "ccb/"   => ccbi folder
    CCBLoader:setRootPath("UI/ccb", "")
    return CCBLoader:load("Rank", owner)
end)

function Rank:ctor()
    -- @TODO: constructor
    --self:init()
end

--[[
function Rank:init()
    self:registerScriptHandler(function (event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end)
end

function Rank:onEnter()
end

function Rank:onExit()
end
]]--



return Rank