local ui       = require "ui"
local extern   = require "extern"
local constant = require "constant"


local frameCache = cc.SpriteFrameCache:getInstance()



local toolkit = {}

function toolkit.clearModule(m)
    for k, v in pairs(m) do
        if type(v) ~= 'function' then
            m[k] = nil
        end
    end
    --cc.SpriteFrameCache:getInstance():removeUnusedSpriteFrames()
end

function toolkit.enableTouch()
    local running = cc.Director:getInstance():getRunningScene()
    if running then
        local mask = running:getChildByTag(constant.zorderMax)
        if mask then
            mask:removeFromParent()
        end
    end
end

function toolkit.disableTouch(scene)
    local running = scene or cc.Director:getInstance():getRunningScene()
    if running then
    	local mask = running:getChildByTag(constant.zorderMax)
    	if not mask then
        	running:addChild(ui.maskLayer(), constant.zorderMax, constant.zorderMax)
        end
    end
end

function toolkit.finishLoading()
    local running = cc.Director:getInstance():getRunningScene()
    if running then
        local mask = running:getChildByTag(constant.zorderMax-1)
        if mask then
            mask:removeFromParent()
        end
    end
end

function toolkit.startLoading(scene)
    local running = scene or cc.Director:getInstance():getRunningScene()
    if running then
        local mask = running:getChildByTag(constant.zorderMax-1)
        if not mask then
            running:addChild(ui.maskLayer(), constant.zorderMax-1, constant.zorderMax-1)
        end
    end
end

function toolkit.finishLoading2()
    local running = cc.Director:getInstance():getRunningScene()
    if running then
        local mask = running:getChildByTag(constant.zorderMax-2)
        if mask then
            mask:removeFromParent()
        end
    end
end

function toolkit.startLoading2(scene)
    local running = scene or cc.Director:getInstance():getRunningScene()
    if running then
        local mask = running:getChildByTag(constant.zorderMax-2)
        if not mask then
            running:addChild(ui.maskLayer(), constant.zorderMax-2, constant.zorderMax-2)
        end
    end
end

function toolkit.finishLoading3()
    local running = cc.Director:getInstance():getRunningScene()
    if running then
        local mask = running:getChildByTag(constant.zorderMax-3)
        if mask then
            mask:removeFromParent()
        end
    end
end

function toolkit.startLoading3(scene)
    local running = scene or cc.Director:getInstance():getRunningScene()
    if running then
        local mask = running:getChildByTag(constant.zorderMax-3)
        if not mask then
            running:addChild(ui.maskLayer(), constant.zorderMax-3, constant.zorderMax-3)
        end
    end
end
function toolkit.bind(sprite, attr, super)
    local t = clone(attr)
    tolua.setpeer(sprite, t)
    if super then
    	setmetatable(t, super)
	end
    return sprite
end

function toolkit.reloadLuaFile(file)
    package.loaded[file]  = nil
    return require(file)
end

function toolkit.addSpriteFrames(file)
    frameCache:addSpriteFramesWithFile(file)
end

local language = require "cfg/language"
function language.get(key)
    return language[key].value
end

return toolkit