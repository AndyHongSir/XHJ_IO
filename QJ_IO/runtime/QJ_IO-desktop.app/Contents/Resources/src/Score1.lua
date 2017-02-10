local Score =   {}
ccb["Score"] = Score
local layer

local function onGameOver(sender,controlEvent)
    kode.facade:send(g_Event.login.open)
end

Score["onGameOver"] = onGameOver

function CreateScore()
    local proxy = cc.CCBProxy:create()
    local schedulerID 
    layer = CCBReaderLoad("Score.ccbi", proxy, Score) 

    local dispatcher = cc.Director:getInstance():getEventDispatcher();
    
    local self =  Score
    
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

  


    local function updateScore()
        print("updateScore")
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
        print("rival_num=%d",rival_num)
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
            return item1.score < item2.score
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

    self.btnGameOver:setVisible(false)
    
    
    local function onNodeEvent(event)
        if event == "exit" then
            if schedulerID then
                cc.Director:getInstance():getScheduler():unscheduleScriptEntry(schedulerID)
                schedulerID  = nil
            end
        elseif event == "enter" then
            self.btnGameOver:setVisible(false)
            schedulerID = cc.Director:getInstance():getScheduler():scheduleScriptFunc(updateScore, 1.0, false)
            
            local eventDispatcher = cc.Director:getInstance():getEventDispatcher()

            local function showBtn()
                print("showBtn")
                self.btnGameOver:setVisible(true)
            end
            local eventListener = cc.EventListenerCustom:create("showBtn", showBtn)
            eventDispatcher:addEventListenerWithSceneGraphPriority(eventListener, layer)
        end
    end

    
    
    layer:registerScriptHandler(onNodeEvent)
    
    return layer


end