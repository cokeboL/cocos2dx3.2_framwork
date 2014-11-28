local ui = require "ui"
local constant = require "constant"
local director = require "director"
local toolkit = require "toolkit"
local gscheduler = require "scheduler"
local pb = require "pb"

local heartBeatInterval = 30
local msgTimeout = 5

pb.import("GamerMessage.proto")

--net = { gateIp = "192.168.10.20", gatePort = 8080, state = "" }
net = { gateIp = "auth.tzb.ilongyuan.cn", gatePort = 8080, state = "" }

function net:clearListeners()
	self.listeners = {}
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

function net.onMessage(err, cmd, action, flags, option, time, message)
	local self = net

	print("---------- onMessage cmd: ", cmd, " action: ", action, " err: ", err)
	
	if message == "syncServerTime" and self.state == "connected" then
		self:getTimestamp()
		print("---------- onMessage syncServerTime")
		return
	end
	if err ~= 0 then
		
		local pack = self.packQueue[1]
		print("-------------- err : ", pack.cmd, pack.action)
		if pack and (self.callBack[pack.cmd] and self.callBack[pack.cmd][pack.action]) then
			self.callBack[pack.cmd][pack.action](err, pack.cmd, pack.action, flags, option, time, message)
			table.remove(self.packQueue, 1)
		else
			toolkit.pushMsg("err code: " .. err)
		end
		toolkit.finishLoading()
	elseif(self.callBack[cmd] and self.callBack[cmd][action]) then
		self.callBack[cmd][action](err, cmd, action, flags, option, time, message)
		table.remove(self.packQueue, 1)
		toolkit.finishLoading()
	elseif(self.listeners[cmd] and self.listeners[cmd][action]) then
		self.listeners[cmd][action](err, cmd, action, flags, option, time, message)
	end
	self.packResponsed = true
end

local heartbeatCount = 0
function net.heartBeatCB(t)
	--print("...................... timestamp: ", t)
end
function net.heartBeat()
	local self = net

	print("***** 111")
	if self.state ~= "connected" and self.state ~= "connecting" then
		return 
	end
	print("***** 222")
	--cclog("***heartBeat**")

	local timeInterval = os.time() - self.lastSendPackTime
	if not self.packResponsed and timeInterval >= msgTimeout then
		cclog("-------------- heartbeat connect time out ")
		self.onNetErr()
	elseif timeInterval >= heartBeatInterval then
		net:getTimestamp(self.heartBeatCB)
		cclog("-------- heartbeat pack, player id: " .. self.heroId .. "  pack count: " .. heartbeatCount)
		heartbeatCount = heartbeatCount + 1
	end

end

function net.gamerMsgListener(err, cmd, action, flags, option, time, message)
	local self = net

	local msg = pb.new("PB_GamerMessage")
	pb.parseFromString(msg, message)
	
	self.gamerMsgs[#self.gamerMsgs+1] = msg
end

function net.onConnected()

	local self = net

	--self.netErr = false
	self.state = "connected"
print("============= onConnected")
	if self.isLogicServer then
		gScheduler:new("startHeartbeat", function()
			gScheduler:delete("heartbeat")
			gScheduler:new("heartbeat", self.heartBeat, 1, false)
			gScheduler:delete("startHeartbeat")
		end, 5, false)
		self.isLogicServerOn = true
		self:addListener(1, 3, self.gamerMsgListener)
	else
	end
	if self.connCB then
		self.connCB()
	end
	self.packResponsed = true
	toolkit.finishLoading()
end

function net.onDisConnected()
	local self = net
	self.state = ""

	self.onNetErr()

	cclog("--------------- onDisConnected xxxx")
end
	
function net.onConnectError()
	local self = net
	self.state = ""

	self.onNetErr()
	cclog("--------------- onConnectError")
	--[[
	do return end
	
	self.state = ""
	
	if self.isLogicServer and self.reconnSession then
		local timeNow = os.time()
		if timeNow - self.reconnStartTime < 5 then
			--self.onDisConnected()
		else
			self.reconnectCount = 0
			self.reconnStartTime = 0
			cclog("#################  check your net config")
		end
	else
		cclog("#################  check your net config")
	end
	--]]
end
	
function net.onConnectTimeout()
	local self = net
	self.state = ""
	
	self.onNetErr()
	cclog("--------------- onConnectTimeout")
	--[[
	self.reconnectCount = 0
	self.reconnStartTime = 0
	if self.reconnectCount < 2 then
		self.reconnectCount = self.reconnectCount + 1
		self:connect(self.ip, self.port, self.connCB, self.isLogicServer)
	else
		self.reconnectCount = 0
		toolkit.finishLoading()
		toolkit.pushMsg("|*** Log ***| err: connect server failed: timeout")
	end
	--]]
end
	
function net:init()
	self.connCB = nil
	self.isLogicServer = nil
	self.reconnectCount = 0
	self.reconnStartTime = 0
	self.timestampIncrement = 0
	self.ip = nil
	self.port = nil
	self.lastSendPackTime = -1
	self.gameEchoStr = nil
	self.packResponsed = false
	self.state = ""
	--self.netErr = false
	self.isLogicServerOn = false

	self.callBack = {}
	self.listeners = {}
	self.gamerMsgs = {}

	self.packQueue = {}

	self.instance = NetMgr:getInstance()
	
	--self.instance:close()
	
	gScheduler:delete("heartbeat")

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

function net:connect(ip, port, callback, isLogicServer)
	print("--------- connect: ", ip, port, callback, isLogicServer)
	self.connCB = callback
	self.isLogicServer = isLogicServer
	self.ip = ip
	self.port = port
	self.instance:close()
	self.instance:connect(ip, port)
	--[[
	if not self.netErr then
		toolkit.startLoading()
	end
	--]]
	self.packResponsed = false
	self.state = "connecting"
	self.lastSendPackTime = os.time()
end

function net:sendMessage(len, cmd, action, pbMsg, callback, disableTouch)
	--[[if cmd ~= 1 and action ~= 8 then
		self.lastCmd = cmd
		self.lastAction = action
	end
	--]]
	print("----sendMessage: ", len, cmd, action, pbMsg, callback, disableTouch)
	self.callBack[cmd] = self.callBack[cmd] or {}
	self.callBack[cmd][action] = callback
	if disableTouch or disableTouch == nil then
		toolkit.startLoading(scene)
	end
	self.packResponsed = false
	self.instance:sendMessage(len, cmd, action, pbMsg)
	self.lastSendPackTime = os.time()

	self.packQueue[#self.packQueue+1] = {cmd=cmd, action=action, msg=pbMsg, cb=callback}
end

function net:getTimestamp(callback)
	pb.import("GamerInit.proto")
	local gameEchoC2s = pb.new("PB_GamerEcho_C2S")
	local heroInfo = db.get("heroInfo")
	gameEchoC2s.id = heroInfo.id
	self.heroId = heroInfo.id
	print("---------------getTimestamp id: ", gameEchoC2s.id)
	self.gameEchoStr = pb.serializeToString(gameEchoC2s)

	self:sendMessage(string.len(self.gameEchoStr), 1, 8, self.gameEchoStr, function(err, cmd, action, flags, option, timestamp, message)
		print("------- get time stamp, msg len: ", string.len(message), ' err: ', err)
		local gameEchoS2c = pb.new("PB_GamerEcho_S2C")
		pb.parseFromString(gameEchoS2c, message)
		print("------- get time stamp, msg len: ", string.len(message))
		self.timestampIncrement = gameEchoS2c.time - os.time()
		if callback then
			--print("---- callback is true 111")
			callback(gameEchoS2c.time)
			--print("---- callback is true 222")
		end
	end, false)
end

function net.reconnect()
	cclog("--------------- reconnect xxxx")

	local self = net

	self.state = ""

	local function reconnCheck(error, cmd, action, flags, option, time, message)
		cclog("--- 000 reconnCheck")
		print(error, cmd, action, flags, option, time, message)
		cclog("--- 111 reconnCheck")

		local msg = pb.new("PB_GamerInit_S2C")
		pb.parseFromString(msg, message)
		self.reconnSession = msg.reconn

		table.remove(self.packQueue, 1)
		toolkit.finishLoading()

		if #self.packQueue > 0 then
			local pack
			local packNeedToSend = clone(self.packQueue)
			self.packQueue = {}
			for i=1, #packNeedToSend-1 do
				pack = packNeedToSend[i]
				net:sendMessage(string.len(pack.msg), pack.cmd, pack.action, pack.msg, pack.cb)
			end
			--self.packQueue = {}
		end
	end
	local function onReconnected()
		print("----------- onReconnected")
		local loginReq = pb.new("PB_GamerInit_C2S")
		loginReq.reconn = self.reconnSession
		print("--- -1-1-1 self.reconnSession: ", self.reconnSession)
		if self.reconnSession then
			loginReq.session = ""
		else
			loginReq.session = self.session
		end
		loginReq.version = "2.0.0.0"
		local req = pb.serializeToString(loginReq)
		net:sendMessage(string.len(req), 1, 2, req, reconnCheck)
	end
	if self.isLogicServerOn then
		self:connect(self.ip, self.port, onReconnected, self.isLogicServer)
	else
		self:connect(self.ip, self.port, self.connCB, self.isLogicServer)
	end

end

function net.onNetErr(cb)
	--gScheduler:delete("heartbeat")

	local self = net

	self.state = "error"
	self.instance:close()
	toolkit.finishLoading()
	toolkit.pushMsg("网络出错，请重试!", function()
		if cb then cb() end
		--self.netErr = false
		--self.reconnectCount = 0
		--cclog("pop messageBox")
		toolkit.startLoading()
		if self.isLogicServer or self.isLogicServerOn then
			self.reconnect()
		end
	end)
	cclog("--- net err, please check your net and retry!")
end

function net.httpOnNetErr(cb)
	local self = net
	self.state = "error"
	toolkit.finishLoading()
	toolkit.pushMsg("网络出错，请重试!")
end

return net