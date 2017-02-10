--[[
file name :    baseView.lua
author  :      洪德森
created :      2014-12-12
purpose :      build视图层 所有建筑信息界面的父类
--]]
if kode == nil then return end

baseView = class("baseView",function(ccbPath,owner,center,IsforceReload)
    if ccbPath == nil then
        return cc.Layer:create()
    else
        local  proxy = cc.CCBProxy:create()
        
        local  root
        root  = CCBReaderLoad(ccbPath,proxy,owner)
        if owner == nil then
            print("ccbPath="..ccbPath)
        end
        root.owner = table.clone(owner)
        if center == nil or center == true  then
            root:setAnchorPoint(0.5,0.5)
            root:setPosition(getSceneSize().width * 0.5,getSceneSize().height * 0.5)
        end
        return root
    end
end)



