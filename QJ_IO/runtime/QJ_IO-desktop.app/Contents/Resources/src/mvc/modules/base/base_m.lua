
baseModel =  class("baseModel",kode.notifier:extend())   
local meta = baseModel

function meta:ctor()

end

--设置控制器部分的事件处理方法数据
function meta:setEventHandlerData(eventHandlerDataMap)
    -- body
    for key,var in pairs(eventHandlerDataMap) do
        self[key] = var
    end
end


return baseModel