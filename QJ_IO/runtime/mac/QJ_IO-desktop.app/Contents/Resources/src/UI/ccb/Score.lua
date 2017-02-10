local CCBLoader = require("CCB.Loader")
local Oop = require("Oop.init")

--[[
Callbacks:


Members:
self.lbl_myscore CCLabelTTF
self.lbl_player1 CCLabelTTF
self.lbl_player2 CCLabelTTF
self.lbl_player3 CCLabelTTF
self.lbl_player4 CCLabelTTF
self.lbl_player5 CCLabelTTF
self.lbl_player6 CCLabelTTF
self.lbl_player7 CCLabelTTF
self.lbl_player8 CCLabelTTF
]]--
local Score = Oop.class("Score", function(owner)
    -- @param "UI.ccb" => code root
    -- @param "ccb/"   => ccbi folder
    CCBLoader:setRootPath("UI/ccb", "")
    return CCBLoader:load("Score", owner)
end)

function Score:ctor()
    -- @TODO: constructor
    self:init()

end

local btn

function g_showBtn()
    print("g_showBtn")
    if btn then
    	btn:setVisible(true)
    	
    end
    return 1
end

function Score:init()
    print("Score:init")
    
    
    self.btnGameOver:setVisible(false)
    
    btn = self.btnGameOver
   -- self.nodeMyScore:setScale(2)
    --self.nodeRank:setScale(2)
    --    self.lbl_myscore:setIgnoreContentScaleFactor(true);
    self:registerScriptHandler(function (event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end)

    local player_num = cc.QjDataInfo:getInstance():GetRivalNum()+1

    if player_num < 8 then
        for i=player_num+1,8 do
            local lbl_score = self["lbl_player"..i]
            if lbl_score then
               --lbl_score:setString("")
               lbl_score:setVisible(false)
            end
        end
    end
    
    local eventDispatcher = cc.Director:getInstance():getEventDispatcher()

    local function showBtn()
        print("showBtn")
        --self.btnGameOver:setVisible(true)
    end
    local eventListener = cc.EventListenerCustom:create("showBtn", showBtn)
    eventDispatcher:addEventListenerWithSceneGraphPriority(eventListener, self)

    
    local function updateScore()
        --print("updateScore")
        local accid_tb = {}
        local accid = cc.QjDataInfo:getInstance():GetPlayerAccId()
        local myscore = cc.QjDataInfo:getInstance():GetPlayerScore(accid)
        self.lbl_myscore:setString(string.format("我的分数%d",myscore))
        local item = {}
        item.id = accid
        item.score = myscore
        item.name = cc.QjDataInfo:getInstance():GetPlayerName(accid)
        table.insert(accid_tb,item)
        local rival_num = cc.QjDataInfo:getInstance():GetRivalNum()
        --print("rival_num=%d",rival_num)
        for i=1,rival_num do
            local rival_id = cc.QjDataInfo:getInstance():GetRivalAccId(i)
            local rivial_score = cc.QjDataInfo:getInstance():GetPlayerScore(rival_id)

            local item = {}
            item.id = rival_id
            item.score = rivial_score
            item.name = cc.QjDataInfo:getInstance():GetPlayerName(rival_id)
            table.insert(accid_tb,item)

        end

        table.sort(accid_tb,function(item1,item2)
            return item1.score > item2.score
        end)

        for i=1,#accid_tb do
            local lbl_score = self["lbl_player"..i]
            local item = accid_tb[i]
            if lbl_score then
                lbl_score:setString(string.format("%s：%d",item.name,item.score))
                if item.id == accid then
                    lbl_score:setColor(cc.c3b(40,253,0))
                else
                    lbl_score:setColor(cc.c3b(255,255,255))
                end
            end
        end
        
    end
    
   


    self.schedulerID = cc.Director:getInstance():getScheduler():scheduleScriptFunc(updateScore, 1.0, false)

   
end

function Score:onEnter()
    print("onEnter")
   
end

function Score:onExit()
    
    if self.schedulerID then
        cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self.schedulerID)
        self.schedulerID  = nil
    end
  
end

function Score:onGameOver(sender, event)
-- @TODO: implement this
    kode.facade:send(g_Event.login.open)
end




return Score