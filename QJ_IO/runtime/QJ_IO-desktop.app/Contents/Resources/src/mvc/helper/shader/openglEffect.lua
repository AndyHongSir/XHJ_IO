--[[
file name :    openglEffect.lua
author  :      洪德森
created :      2014/11/25
purpose :      shader
--]]

GL_Shader = class("GL_Shader")
local meta = GL_Shader

local vertFile = "src/mvc/helper/shader/ccPositionTextureColor_vert.vsh"
local fragFile = {
    gray = "src/mvc/helper/shader/gray.fsh",

}
GL_Shader.EffectType = {
    gray = 1,
}
local effectFileRef = {
    [GL_Shader.EffectType.gray] = {v=vertFile,f = fragFile.gray},
}
function meta.loadShaderVertex(vert,frag,addition)
    local glprogram  = cc.GLProgram:createWithFilenames(vert,frag)
    local glprogramstate = cc.GLProgramState:getOrCreateWithGLProgram(glprogram)
    if addition then
        for key,var in pairs(addition) do
            glprogramstate:setUniformInt(key,tonumber(var))
        end
    end
    return glprogramstate
end
--对目标施加效果
--target:需要添加效果的目标
--effectId:效果id,从GL_Shader.EffectType里取值

function meta.setEffectOnTarget(target,effectId,addition)
    local findswordsx,findswordsy=string.find(target:getDescription(),"Sprite")
    local effectFileInfo = effectFileRef[effectId]
    local render = target
    if findswordsx==nil then
        render=target:getBackgroundSpriteForState(1):getSprite()
    end
    assert(render,"被渲染的对象不能为空")
    if effectId == GL_Shader.EffectType.narmal then
        render:setGLProgram(cc.GLProgramCache:getInstance():getGLProgram("ShaderPositionTextureColor_noMVP"))
    else
        render:setGLProgramState(meta.loadShaderVertex(effectFileInfo.v,effectFileInfo.f,addition));
    end

end
