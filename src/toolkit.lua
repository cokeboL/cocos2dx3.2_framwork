local ui       = require "ui"
local extern   = require "extern"
local constant = require "constant"


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

function toolkit.disableTouch()
    local running = cc.Director:getInstance():getRunningScene()
    if running then
    	local mask = running:getChildByTag(constant.zorderMax)
    	if not mask then
        	running:addChild(ui.maskLayer(), constant.zorderMax, constant.zorderMax)
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

function toolkit.reloadLua(file)
    package.loaded[file]  = nil
    return require(file)
end

return toolkit