--[[
file name :    events.lua
author  :      洪德森
created :      2014-12-4
purpose :      所有通知事件的定义都写在这里
--]]
Event.EVENT_APP_START = "app_start"

--通知事件名称
g_Event = {
    
    --商店系统
    shop = {
        open = "shop_open",
        close = "shop_close",
    },
    --任务系统
    task = {
        open = "task_open",
        openQuick = "task_openQuick",
        go = "task_go",
        update = "task_update",
        download = "task_download",
    },
    --商城核心
    shopMain = {
         open = "shopMain_open",
    },
    shopMainGroup = {
         open = "shopMainGroup_open",
    },
    gift = {
         open = "gift_open",
    },
    chat = {
         open = "chat_open",
    },
    shopExchange = {
         open = "shopExchange_open",
    },
    guild = {
         open = "guild_open",
    },
    recharge = {
         open = "recharge_open",
    },
    login = {
         open = "login_open",
    },
    
}