
cc.FileUtils:getInstance():setPopupNotify(false)
cc.FileUtils:getInstance():addSearchPath("src/")
cc.FileUtils:getInstance():addSearchPath("res/")
--resources-iphonehd
cc.FileUtils:getInstance():addSearchPath("res/resources-iphonehd/")

require('mobdebug').start() 
require "config"
require "cocos.init"


require("kode/init")     -- framework
require("mvc/init")          -- app
require("mvc/helper/globalVar")
require("mvc/helper/globalFunc")
require("mvc/modules/base/baseView")

if ccb == nil then
	ccb = {}
	
end

local function main()
    --require("app.MyApp"):create():run()
    kode.facade:send(g_Event.login.open)
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    print(msg)
end
