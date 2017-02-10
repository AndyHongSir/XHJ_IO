local CCBLoader = require("CCB.Loader")
local Oop = require("Oop.init")

--[[
Callbacks:
    

Members:
    self.lbl_player_1 CCLabelTTF
    self.lbl_player_2 CCLabelTTF
]]--
local Match = Oop.class("Match", function(owner)
    -- @param "UI.ccb" => code root
    -- @param "ccb/"   => ccbi folder
    CCBLoader:setRootPath("UI/ccb", "")
    return CCBLoader:load("Match", owner)
end)

function Match:ctor()
    -- @TODO: constructor
    self:init()
end


function Match:init()
    self.lbl_player_1:setString(cc.QjDataInfo:getInstance():GetPlayerAccId())
    --等待匹配
    self.lbl_player_2:setString("等待匹配")
    self.lbl_player_3:setString("等待匹配")
    self:registerScriptHandler(function (event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end)
end



function Match:onEnter()
     cc.QjSocket:getInstance():SendNetBattleBegin(1,1)
    local eventDispatcher = self:getEventDispatcher()
    local matchIndex = 1;
    local function onAddRival()
        --print("onAddRival")
        local acc_id = cc.QjDataInfo:getInstance():GetRivalAccId(matchIndex)
        print("acc_id="..acc_id)
        if acc_id ~= 0 then
            print("matchIndex ="..matchIndex)
            
            matchIndex = matchIndex+1
            if self["lbl_player_"..matchIndex] then
                self["lbl_player_"..matchIndex]:setString(acc_id)
            end
            
        end
        
    end
    
    local eventListener = cc.EventListenerCustom:create("addRival", onAddRival)
    eventDispatcher:addEventListenerWithSceneGraphPriority(eventListener, self)
end

function Match:onExit()
    
end




return Match