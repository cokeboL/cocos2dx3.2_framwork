local ui = require "ui"
local net = require "net"
local toolkit = require "toolkit"
local director = require "director"


local main = {}

-- init module 
function main:initVars()
	self.scene = nil
	self.layer = nil
	self.widget = nil

	self.loadFrameCount = 0
end

function main:getData()
	local msgName = "xxx"
	local msg = "xxxx"
	net:sendMessage(msgName, msg, self.setData)
end

function main.setData(msgName, msg)
	-- xxx
	local self = main

	self:loadScene()
end

function main.loadResource()
	local self = main
	self.loadFrameCount = self.loadFrameCount + 1

	if self.loadFrameCount == 2 then

	elseif self.loadFrameCount == 4 then

	elseif self.loadFrameCount == 6 then

	elseif self.loadFrameCount == 8 then

	elseif self.loadFrameCount == 10 then
		self.loadNode:removeFromParent()
		toolkit.enableTouch()
	end
end

function main:onEnter()
	self.widget = ui.binWidget(file)
	--self.widget = ui.jsonWidget(file)
	self.layer:addChild(self.widget)

    schedule(self.loadNode, self.loadResource, 0)
end

function main:loadScene()
	self.scene = ui.Scene()
	
	self.layer = ui.Layer()
    self.scene:addChild(self.layer)

	self.layer:registerScriptHandler(function(eventType)
	    if "enter" == eventType then
	        self:onEnter()
	    end
	end)    

	self.loadNode = ui.Node()
	self.layer:addChild(self.loadNode)
	
    director.runScene(self.scene, self.clear)
end

function main.clear()
	toolkit.clearModule(main)
end

function main:run()	
	-- push loading UI to the running scene
	toolkit.disableTouch()
	
	-- init module base data
	self:initVars()
	
	-- get server data by net
	self:getData()
end

-- ************************************

-- ************************************

return main
