local commen = {}

local count = 0

local function loadBaseModules()
	if count == 0 then
		require "AudioEngine"
		require "bitExtend"
	elseif count == 1 then
		require "Cocos2d"
		require "Cocos2dConstants"
	elseif count == 2 then
		require "CocoStudio"
		require "Deprecated"
	elseif count == 3then
		require "DeprecatedClass"
		require "DeprecatedEnum"
	elseif count == 4 then
		require "DeprecatedOpenglEnum"
		require "DrawPrimitives"
	elseif count == 5 then
		require "experimentalConstants"
		require "extern"
	elseif count == 6 then
		require "GuiConstants"
		require "json"
	elseif count == 7 then
		local targetPlatform = cc.Application:getInstance():getTargetPlatform()
		if (cc.PLATFORM_OS_ANDROID == targetPlatform) then
			require "luaj"
		end
		if (cc.PLATFORM_OS_IPHONE == targetPlatform)  or (cc.PLATFORM_OS_IPAD == targetPlatform)
			or (cc.PLATFORM_OS_MAC == targetPlatform) then
			require "luaoc"
		end
	
		require "Opengl"
	elseif count == 8 then
		require "OpenglConstants"
		require "StudioConstants"
		gScheduler:delete("commen")
		commen.cb()
	end
	count = count + 1
end

function commen:init(callback)
	self.cb = callback
	local gScheduler = require "gScheduler"
	gScheduler:new("commen", loadBaseModules, 0.3/8, false)
end

return commen
