local ui = require "ui"
local constant = require "constant"
local director = require "director"
local toolkit = require "toolkit"

net = {}

net.gate = { addr = "115.29.111.174", port = 8080 }

function net:clearListeners()
	self.listeners = {};
end
function net:addListener(cmd, action, callback)
	self.listeners[cmd] = self.listeners[cmd] or {}
	self.listeners[cmd][action] = callback
end
function net:removeListener(cmd, action)
	if self.listeners[cmd] and self.listeners[cmd][action] then
		self.listeners[cmd][action] = nil
	end
end

function net:loadingAnimation()
	return ui.Node()
end

--[[
function net:addMask()
	
	if(not self.mask)then
		self.mask = ui.maskLayer()
		self.mask:addChild(self.loadingAnimation())
		director.getRunningScene():addChild(self.mask, constant.zorderNet, constant.zorderNet)
	end
	
end

function net:removeMask()
	if(self.mask)then
		self.mask:removeFromParent()
		self.mask = nil
	end
end
--]]

function net.onMessage(error, cmd, action, flags, option, time, message)
	local self = net
	
	if(self.callBack[cmd] and self.callBack[cmd][action]) then
		self.callBack[cmd][action](error, cmd, action, flags, option, time, message)
		self.callBack[cmd][action] = nil
		--self:removeMask()
		toolkit.enableTouch()
	elseif(self.listeners[cmd] and self.listeners[cmd][action]) then
		self.listeners[cmd][action](error, cmd, action, flags, option, time, message)
		self.listeners[cmd][action] = nil
	end
end
	
function net.onConnected()
	local self = net
	if self.connCB then
		self.connCB()
		self.connCB = nil
	end
	--self:removeMask()
	toolkit.enableTouch()
end
	
function net.onDisConnected()
	
end
	
function net.onConnectError()
	cclog("onConnectError")
end
	
function net.onConnectTimeout()
	cclog("onConnectTimeout")
end
	
function net:init()
	self.connCB = nil
	self.callBack = {}
	self.listeners = {}

	self.instance = NetMgr:getInstance()
	
	self.instance:close();
	
	self.instance:registerCallBacks(
		self.onConnected,
		self.onDisConnected,
		self.onConnectError,
		self.onConnectTimeout,
		self.onMessage
	)
end

function net:httpGet(url, callback)
	self.instance:httpRequest(url, callback);
end

function net:httpPost(url, data, callback)
	self.instance:httpPost(url, data, callback);
end

function net:connect(ip, port, callback)
	self.connCB = callback
	self.instance:close()
	self.instance:connect(ip, port)
	--self:addMask()
	toolkit.disableTouch()
end

function net:sendMessage(len, cmd, action, pbMsg, callback)
	self.callBack[cmd] = self.callBack[cmd] or {}
	self.callBack[cmd][action] = callback
	--self:addMask()
	toolkit.disableTouch(scene)
	self.instance:sendMessage(len, cmd, action, pbMsg)
end

function net:getTimestamp(callback)
	self:sendMessage(0, 1, 8, "", function(error, cmd, action, flags, option, timetamp, message)
	    callback(timetamp)
	end)
end

return net