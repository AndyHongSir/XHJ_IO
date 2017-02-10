--[[
file name :    globarVar.lua
author  :      洪德森
created :      2015-11-10
purpose :      常量文件
--]]

g_lang = {
    cn = 1,
    tw = 2,
    en = 3,
}

g_sysLang = g_lang.tw

g_shopBtnType = {
    altar = 1,
    shop = 2,
    market = 3,
    vipshop = 4,
    recharge = 5,
}
--招募类型
g_alterType = {
    energy = 1,
    gold = 2,
    diamond = 3,
}
--位置类型
g_posType = {
    left = 1,
    center = 2,
    right = 3,
}
--任务类型
g_taskType = {
    story = 1,
    daily = 2,
    achievement = 3,
    beyond = 4,
}
--手指由左向右移动
g_slideDirection = {
    toRight = 1,
    toLeft = 2,
}
--任务完成类型
g_taskFinishType = {
    --[[
    1=通关关卡（必须手动）
    2=扫荡关卡（手动扫荡都可）
    3=装备强化（强化次数）
    4=装备升级（升级次数）
    5=装备升星（达到星级）
    6=人物升级（达到X级）
    7=人物转职（达到X转）
    8=卡片升级（升级次数）
    9=卡片强化（强化次数）
    10=卡片升星（达到星级）
    11=无尽模式达到X分
    12=无尽模式参加次数
    13=竞技场参加次数
    14=加入公会
    ……
    ]]      
    }
--主界面5个按钮
g_mainBtns = {
    --阵营
    home = 1,
    --队伍
    team = 2,
    --战斗
    fighter = 3,
    --任务
    task = 4,
    --商店
    shop = 5,

}

g_colorType_richText = {
    [1] = cc.c3b(255,255,255),
    [2] = cc.c3b(40,253,0),
    [3] = cc.c3b(21,229,255),
    [4] = cc.c3b(253,108,255),
    [5] = cc.c3b(254,251,0),
    [6] = cc.c3b(213,197,232),
    [7] = cc.c3b(101,149,197),
    [8] = cc.c3b(171,223,255),
    [9] = cc.c3b(255,0,0),
    [10] = cc.c3b(171,223,255),
    [11] = cc.c3b(240,17,141),
    [12] = cc.c3b(125,125,140),
    [13] = cc.c3b(255,131,33),
    --灰色
    [14] = cc.c3b(135,135,137),
    --紫色
    [15] = cc.c3b(255,9,152),
}

g_colorType = {
    [1] = cc.c3b(255,255,255),
    [2] = cc.c3b(55,255,0),
    [3] = cc.c3b(17,224,255),
    [4] = cc.c3b(170,132,255),
    [5] = cc.c3b(255,20,255),
    [6] = cc.c3b(255,255,0),

    [7] = cc.c3b(213,197,232),
    [8] = cc.c3b(101,149,197),
    [9] = cc.c3b(171,223,255),
    [10] = cc.c3b(255,0,0),
    [11] = cc.c3b(171,223,255),
    [12] = cc.c3b(240,17,141),
    [13] = cc.c3b(125,125,140),
    [14] = cc.c3b(255,131,33),
    --灰色
    [15] = cc.c3b(140,140,140),
    --紫色
    [16] = cc.c3b(255,9,152),
    --聊天中玩家名字的颜色
    [17] = cc.c3b(225,178,86),

}

if g_lang.cn == g_sysLang then
    g_fontName = {
        [1] = g_systemfonts,
        [2] = g_systemfonts,
    }
elseif g_lang.tw == g_sysLang then
    g_fontName = {
        [1] = g_systemfonts,
        [2] = g_systemfonts,
    }
end

g_fontSize = {
    [1] = 8,
    [2] = 9,
    [3] = 10,
    [4] = 11,
    [5] = 12,
    [6] = 14,
    [7] = 16,
    [8] = 18,
    [9] = 20,
    [10] = 22,
    [11] = 24,
    [12] = 26,
    [13] = 28,
    [14] = 30,
}

--商店兑换的标签类型
g_shopExchangeType = {
    warrior = 21,
    mage = 22,
    archer = 23,
    stone = 24,
    warrior2 = 27,
    mage2 = 28,
    archer2 = 29,
    stone1 = 30,--强化石
    stone2 = 31,--兑换石
    stone3 = 32,--附魔石
    warrior3 = 37,
    mage3 = 38,
    archer3 = 39,

}
--兑换商店筛选类型
g_shopExchangeFilterType = {
    --1 weapon 3 body, 2 head, 6 necklace, 5 ring, 4 offhand;
    all =0,
    weapon = 1,
    treasure = 4,
    head = 2,
    body = 3,
    necklace = 6,
    ring = 5,

}

g_buyMainType = {
    shop = 1,
    exchange = 2,
}
g_shopType = {
    base = 1,
    pvp = 2,
    recharge = 3,
    vip = 4,
}

g_baseShopType ={
    normal = 1,
    market = 2,
}

g_exchangeType = {
    normal = 1,
    suit = 2,
    stone = 3,
    ticket = 4,
}

g_shopViewTag = {
    buy = 100001,
    recharge = 100002,
    exchange = 100003,
    vip = 100004,
    pvp = 100005,
}

g_serverStatus = {
    rest = 0,
    smooth =1,
    hot =2,

}

g_serverColorType = {
    [0] = cc.c3b(180,179,177),
    [1] = cc.c3b(250,241,0),
    [2] = cc.c3b(250,241,0),
}
--聊天里的通配符
g_equipTag = "$$$*_"
g_propTag = "$^^^^"
--$^^__
g_normalTag = "$^^__"
g_eiteTag = "$^^^_"
g_random_eiteTag = "$^_^_"
--$^___连协副本
g_helpTag = "$^___"
g_nameTag = "$_^_^"
--$$^_^
g_friendsTag = "$$^_^"

g_languageIdTag = "$$#^^"
--$^$
g_strTag = "$^$"

g_shopContentViewTag = 100001
g_systemfonts = "Arial-BoldMT"


g_ToTeamTag = 0

