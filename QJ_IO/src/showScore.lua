--Score

require "Score1"
local layer = require("UI.ccb.Score"):new()--CreateScore()
local scene = cc.Director:getInstance():getRunningScene()
--layer:setAnchorPoint(cc.p(0.5,0.5))
scene:addChild(layer,9999)