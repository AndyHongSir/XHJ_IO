#include "scripting/lua-bindings/auto/lua_cocos2dx_qj_auto.hpp"
#include "CppToLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

int lua_cocos2dx_qj_QjDataInfo_GetRivalAccId(lua_State* tolua_S)
{
    int argc = 0;
    QjDataInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"QjDataInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (QjDataInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_qj_QjDataInfo_GetRivalAccId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "QjDataInfo:GetRivalAccId");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjDataInfo_GetRivalAccId'", nullptr);
            return 0;
        }
        int ret = cobj->GetRivalAccId(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "QjDataInfo:GetRivalAccId",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_qj_QjDataInfo_GetRivalAccId'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_qj_QjDataInfo_GetRivalNum(lua_State* tolua_S)
{
    int argc = 0;
    QjDataInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"QjDataInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (QjDataInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_qj_QjDataInfo_GetRivalNum'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjDataInfo_GetRivalNum'", nullptr);
            return 0;
        }
        int ret = cobj->GetRivalNum();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "QjDataInfo:GetRivalNum",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_qj_QjDataInfo_GetRivalNum'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_qj_QjDataInfo_ToGameScene(lua_State* tolua_S)
{
    int argc = 0;
    QjDataInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"QjDataInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (QjDataInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_qj_QjDataInfo_ToGameScene'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjDataInfo_ToGameScene'", nullptr);
            return 0;
        }
        cobj->ToGameScene();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "QjDataInfo:ToGameScene",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_qj_QjDataInfo_ToGameScene'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_qj_QjDataInfo_GetPlayerName(lua_State* tolua_S)
{
    int argc = 0;
    QjDataInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"QjDataInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (QjDataInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_qj_QjDataInfo_GetPlayerName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "QjDataInfo:GetPlayerName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjDataInfo_GetPlayerName'", nullptr);
            return 0;
        }
        std::string ret = cobj->GetPlayerName(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "QjDataInfo:GetPlayerName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_qj_QjDataInfo_GetPlayerName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_qj_QjDataInfo_GetPlayerScore(lua_State* tolua_S)
{
    int argc = 0;
    QjDataInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"QjDataInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (QjDataInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_qj_QjDataInfo_GetPlayerScore'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "QjDataInfo:GetPlayerScore");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjDataInfo_GetPlayerScore'", nullptr);
            return 0;
        }
        int ret = cobj->GetPlayerScore(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "QjDataInfo:GetPlayerScore",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_qj_QjDataInfo_GetPlayerScore'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_qj_QjDataInfo_GetPlayerAccId(lua_State* tolua_S)
{
    int argc = 0;
    QjDataInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"QjDataInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (QjDataInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_qj_QjDataInfo_GetPlayerAccId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjDataInfo_GetPlayerAccId'", nullptr);
            return 0;
        }
        int ret = cobj->GetPlayerAccId();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "QjDataInfo:GetPlayerAccId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_qj_QjDataInfo_GetPlayerAccId'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_qj_QjDataInfo_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"QjDataInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjDataInfo_getInstance'", nullptr);
            return 0;
        }
        QjDataInfo* ret = QjDataInfo::getInstance();
        object_to_luaval<QjDataInfo>(tolua_S, "QjDataInfo",(QjDataInfo*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "QjDataInfo:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_qj_QjDataInfo_getInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_qj_QjDataInfo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    QjDataInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjDataInfo_constructor'", nullptr);
            return 0;
        }
        cobj = new QjDataInfo();
        tolua_pushusertype(tolua_S,(void*)cobj,"QjDataInfo");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "QjDataInfo:QjDataInfo",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_qj_QjDataInfo_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_qj_QjDataInfo_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (QjDataInfo)");
    return 0;
}

int lua_register_cocos2dx_qj_QjDataInfo(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"QjDataInfo");
    tolua_cclass(tolua_S,"QjDataInfo","QjDataInfo","",nullptr);

    tolua_beginmodule(tolua_S,"QjDataInfo");
        tolua_function(tolua_S,"new",lua_cocos2dx_qj_QjDataInfo_constructor);
        tolua_function(tolua_S,"GetRivalAccId",lua_cocos2dx_qj_QjDataInfo_GetRivalAccId);
        tolua_function(tolua_S,"GetRivalNum",lua_cocos2dx_qj_QjDataInfo_GetRivalNum);
        tolua_function(tolua_S,"ToGameScene",lua_cocos2dx_qj_QjDataInfo_ToGameScene);
        tolua_function(tolua_S,"GetPlayerName",lua_cocos2dx_qj_QjDataInfo_GetPlayerName);
        tolua_function(tolua_S,"GetPlayerScore",lua_cocos2dx_qj_QjDataInfo_GetPlayerScore);
        tolua_function(tolua_S,"GetPlayerAccId",lua_cocos2dx_qj_QjDataInfo_GetPlayerAccId);
        tolua_function(tolua_S,"getInstance", lua_cocos2dx_qj_QjDataInfo_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(QjDataInfo).name();
    g_luaType[typeName] = "QjDataInfo";
    g_typeCast["QjDataInfo"] = "QjDataInfo";
    return 1;
}

int lua_cocos2dx_qj_QjSocket_SendNetBattleOper(lua_State* tolua_S)
{
    int argc = 0;
    QjSocket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"QjSocket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (QjSocket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_qj_QjSocket_SendNetBattleOper'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "QjSocket:SendNetBattleOper");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "QjSocket:SendNetBattleOper");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjSocket_SendNetBattleOper'", nullptr);
            return 0;
        }
        cobj->SendNetBattleOper(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        int arg0;
        int arg1;
        double arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "QjSocket:SendNetBattleOper");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "QjSocket:SendNetBattleOper");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "QjSocket:SendNetBattleOper");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjSocket_SendNetBattleOper'", nullptr);
            return 0;
        }
        cobj->SendNetBattleOper(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 4) 
    {
        int arg0;
        int arg1;
        double arg2;
        double arg3;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "QjSocket:SendNetBattleOper");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "QjSocket:SendNetBattleOper");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "QjSocket:SendNetBattleOper");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "QjSocket:SendNetBattleOper");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjSocket_SendNetBattleOper'", nullptr);
            return 0;
        }
        cobj->SendNetBattleOper(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 5) 
    {
        int arg0;
        int arg1;
        double arg2;
        double arg3;
        double arg4;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "QjSocket:SendNetBattleOper");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "QjSocket:SendNetBattleOper");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "QjSocket:SendNetBattleOper");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "QjSocket:SendNetBattleOper");

        ok &= luaval_to_number(tolua_S, 6,&arg4, "QjSocket:SendNetBattleOper");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjSocket_SendNetBattleOper'", nullptr);
            return 0;
        }
        cobj->SendNetBattleOper(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "QjSocket:SendNetBattleOper",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_qj_QjSocket_SendNetBattleOper'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_qj_QjSocket_connectDefault(lua_State* tolua_S)
{
    int argc = 0;
    QjSocket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"QjSocket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (QjSocket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_qj_QjSocket_connectDefault'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjSocket_connectDefault'", nullptr);
            return 0;
        }
        cobj->connectDefault();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "QjSocket:connectDefault",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_qj_QjSocket_connectDefault'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_qj_QjSocket_SendNetBattleBegin(lua_State* tolua_S)
{
    int argc = 0;
    QjSocket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"QjSocket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (QjSocket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_qj_QjSocket_SendNetBattleBegin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "QjSocket:SendNetBattleBegin");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "QjSocket:SendNetBattleBegin");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjSocket_SendNetBattleBegin'", nullptr);
            return 0;
        }
        cobj->SendNetBattleBegin(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "QjSocket:SendNetBattleBegin",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_qj_QjSocket_SendNetBattleBegin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_qj_QjSocket_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"QjSocket",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjSocket_getInstance'", nullptr);
            return 0;
        }
        QjSocket* ret = QjSocket::getInstance();
        object_to_luaval<QjSocket>(tolua_S, "QjSocket",(QjSocket*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "QjSocket:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_qj_QjSocket_getInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_qj_QjSocket_constructor(lua_State* tolua_S)
{
    int argc = 0;
    QjSocket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_qj_QjSocket_constructor'", nullptr);
            return 0;
        }
        cobj = new QjSocket();
        tolua_pushusertype(tolua_S,(void*)cobj,"QjSocket");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "QjSocket:QjSocket",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_qj_QjSocket_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_qj_QjSocket_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (QjSocket)");
    return 0;
}

int lua_register_cocos2dx_qj_QjSocket(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"QjSocket");
    tolua_cclass(tolua_S,"QjSocket","QjSocket","",nullptr);

    tolua_beginmodule(tolua_S,"QjSocket");
        tolua_function(tolua_S,"new",lua_cocos2dx_qj_QjSocket_constructor);
        tolua_function(tolua_S,"SendNetBattleOper",lua_cocos2dx_qj_QjSocket_SendNetBattleOper);
        tolua_function(tolua_S,"connectDefault",lua_cocos2dx_qj_QjSocket_connectDefault);
        tolua_function(tolua_S,"SendNetBattleBegin",lua_cocos2dx_qj_QjSocket_SendNetBattleBegin);
        tolua_function(tolua_S,"getInstance", lua_cocos2dx_qj_QjSocket_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(QjSocket).name();
    g_luaType[typeName] = "QjSocket";
    g_typeCast["QjSocket"] = "QjSocket";
    return 1;
}
TOLUA_API int register_all_cocos2dx_qj(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_qj_QjSocket(tolua_S);
	lua_register_cocos2dx_qj_QjDataInfo(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

