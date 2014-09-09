local targetPlatform = cc.Application:getInstance():getTargetPlatform()

require "AudioEngine"
require "bitExtend"
require "Cocos2d"
require "Cocos2dConstants"
require "CocoStudio"
require "Deprecated"
require "DeprecatedClass"
require "DeprecatedEnum"
require "DeprecatedOpenglEnum"
require "DrawPrimitives"
require "experimentalConstants"
require "extern"
require "GuiConstants"
require "json"
if (cc.PLATFORM_OS_ANDROID == targetPlatform) then
require "luaj"
end
if (cc.PLATFORM_OS_IPHONE == targetPlatform)  or (cc.PLATFORM_OS_IPAD == targetPlatform)
	or (cc.PLATFORM_OS_MAC == targetPlatform) then
require "luaoc"
end
require "Opengl"
require "OpenglConstants"
require "StudioConstants"
