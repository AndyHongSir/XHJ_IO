--[[
file name :    generalFunc.lua
author  :      洪德森
created :      2014-11-28
purpose :      全局方法
--]]

--  获得屏幕尺寸
local visibleSize = nil
function getSceneSize()
    if visibleSize == nil then
        visibleSize = cc.Director:getInstance():getVisibleSize()
    end
    return visibleSize
end

function round(value)
    local floor = math.floor(value)
    local ciel = math.ceil(value)
    local avg = (floor+ciel)/2
    if value>=avg then
        return ciel
    else
        return floor
    end
end

function printT(tb)

    for key,var in pairs(tb) do
        print("key = "..key..",var="..var)
    end
end

local ccbRes = {}
local ownerMap = {}
function CCBRes(ccbPath,proxy,owner)
    if ccbRes[ccbPath] == nil then
        ccbRes[ccbPath] = CCBReaderLoad(ccbPath,proxy,owner)
        ccbRes[ccbPath]:retain()
        ownerMap[ccbPath] =  owner
--        ownerMap[ccbPath]:retain()
    end
    return ccbRes[ccbPath],ownerMap[ccbPath]
end

function  g_getStringTable(str)
    local tab = {}
    for uchar in string.gfind(str, "[%z\1-\127\194-\244][\128-\191]*") do
        tab[#tab+1] = uchar
    end
    return tab
end

function g_getContent(content)
    print("content="..content)
    local start,endpos = string.find(content,g_languageIdTag)
    
    if endpos == nil then
        return content
    end

    local subcontent = string.sub(content,endpos+1)
    
--    print("subcontent="..subcontent)
    
--    print("g_strTag="..g_strTag)

    start,endpos = string.find(subcontent,g_languageIdTag)
    
--    print("start="..start..",endpos="..endpos)
    
    local langId
    local newStr
    local items = {}
    
    local function  subStr(subcontent)
        local start,endpos = string.find(subcontent,g_languageIdTag)
--        print("subStr start="..start..",endpos="..endpos)
        if endpos ~= nil then   
--            print("subStr start="..start..",endpos="..endpos)
            table.insert(items,string.sub(subcontent,1,start-1))           
            local subcon= string.sub(subcontent,endpos+1)
--            print("subcon="..subcon)
            start,endpos = string.find(subcon,g_languageIdTag)
            if endpos == nil then
                table.insert(items,subcon)
            else
                subStr(subcontent)
            end
        else
            table.insert(items,subcontent)
        end  
    end

    if start ~= nil  then
    	langId = string.sub(subcontent,1,start-1)
--        print("langId="..langId)
        subStr(string.sub(subcontent,endpos+1))
    else
        langId = subcontent
--        print("langId="..langId)
    end
    langId = tonumber(langId)
    local newStr
    print("#items ="..#items)
    if #items == 0 then
    	newStr =  qjDocInfo:GetGeneralLanguage(langId)
    elseif #items == 1 then
        newStr =  string.format(qjDocInfo:GetGeneralLanguage(langId),tonumber(items[1]))
    elseif #items == 2 then
        newStr =  string.format(qjDocInfo:GetGeneralLanguage(langId),tonumber(items[1]),tonumber(items[2]))
    elseif #items == 3 then
        newStr =  string.format(qjDocInfo:GetGeneralLanguage(langId),tonumber(items[1]),tonumber(items[2]),tonumber(items[3]))
    end
    return newStr
end

function g_maxChatNum()
   return  "50"
end

function NewName()
    --efe521863758764d32aa71262e8eeea18943d23b
    --ea21738cc2c146e59a567488ac28827e7ad51b6a
    --ffjhghghgkk]g
    --cdcb035c271c7aae9a142ce061b64433ac9918ab
    --7192dbe2a92a721251ce95734d3f5f2883ecdae5
    --cdcb035c271c7aae9a142ce061b64433ac9918ab
    --7aae9a142ce061b64433ac99b
    --odfdhhfhddlld
    --ce920f02bdf3240f900bfcc4f1126cd183574d63
    --12tttytnyuuu
    --uuuttt
    --uuuttt22
    return "uuuttt22"
end
