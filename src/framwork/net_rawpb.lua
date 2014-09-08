local ui = require "ui"
local constant = require "constant"
local director = require "director"

net = {}

net.gate = { addr = "192.168.2.134", port = 10101 }

function net:clearListeners()
	self.listeners = {};
end
function net:addListener(msgName, callback)
	if(type(msgName) == "string" and type(callback) == "function")then
		self.listeners[msgName] = callback;
	end
end
function net:removeListener(msgName)
	self.listeners[msgName] = nil;
end

function net:loadingAnimation()
	return ui.Node()
end

function net:addMask()
	if(not self.mask)then
		self.mask = ui.maskLayer();
		self.mask:addChild(self.loadingAnimation())
		director.getRunningScene():addChild(self.mask, constant.zorderNet, constant.zorderNet);
	end
end
function net:removeMask()
	if(self.mask)then
		self.mask:removeFromParent();
		self.mask = nil;
	end
end

function net.onMessage()
	local self = net
	
	local m = self.instance:getMessage()
	
	local msgName = m.name
	local msg = m.content
	
	if(self.callBack[msgName]) then
		self.callBack[msgName](msgName, msg)
		self.callBack[msgName] = nil;
		self.removeMask()
	elseif(self.listeners[msgName]) then
		self.listeners[msgName](msgName, msg)
	end
end
	
function net.onConnected()
	local self = net
	
	if self.connCB then
		self.connCB()
		self.connCB = nil
	end
	self.removeMask()
end
	
function net.onDisConnected()
	
end
	
function net.onConnectError()
	cclog("onConnectError");
end
	
function net.onConnectTimeout()
	cclog("onConnectTimeout");
	mainScene.runScene();
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

function net:httpRequest(url, callback)
	self.instance():httpRequest(url, callback);
end

function net:connect(ip, port, callback)
	self.connCB = callback
	self.instance:close();
	self.instance:setAddress(ip, port);
	self.instance:connect()
	self.addMask()
end

function net:sendMessage(msgName, msg, callback)
	if(type(msgName) == "string" and type(msg) == "string") then
		self.addMask()
		if(msgName and callback)then
			self.callBack[msgName] = callback;
		end
		self.instance:sendMessage(msgName, string.len(msg), msg);
	end
end

