if kode == nil then return end
local loginView = class("loginView",function(ui,owner,center) return baseView.new(ui,owner,center) end)
local meta = loginView

function meta:init(data)
    local lblID = self.owner["lblID"]
    
    if cc.QjDataInfo:getInstance():GetPlayerAccId() == 0 then
        lblID:setString("未登陆")
    else
        lblID:setString(cc.QjDataInfo:getInstance():GetPlayerAccId())
    end
   
   
    return self

end

function meta:fill()
    local lblID = self.owner["lblID"]
    lblID:setString(cc.QjDataInfo:getInstance():GetPlayerAccId())

end




return meta