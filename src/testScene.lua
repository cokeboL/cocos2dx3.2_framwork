require "testpb"

local ui = require "ui"
local net = require "net"
local toolkit = require "toolkit"
local director = require "director"

net:init()
local testScene = {}

-- init module 
function testScene:initVars()
	self.scene = nil
	self.layer = nil
	self.widget = nil

	self.loadFrameCount = 0
end

function testScene:getData()
	--[[
	local msgName = "xxx"
	local msg = "xxxx"
	net:sendMessage(msgName, msg, self.setData)
	--]]
	self.setData()
end

function testScene.setData(msgName, msg)
	-- xxx
	local self = testScene

	self:loadScene()
end

function testScene.loadResource()
	local self = testScene
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

function testScene:onEnter()
	self.widget = ui.binWidget("NewUi_1.csb")
	--self.widget = ui.jsonWidget(file)
	self.layer:addChild(self.widget)


	local function btnOnTouch(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            testpb()
        end
    end

    local btn_1 = self.widget:getChildByName("btn_1")
    btn_1:addTouchEventListener(btnOnTouch)

    local btn_2 = self.widget:getChildByName("btn_2")
    btn_2:addTouchEventListener(btnOnTouch)

    schedule(self.loadNode, self.loadResource, 0)
end

function testScene:loadScene()
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

function testScene.clear()
	toolkit.clearModule(testScene)
end

function testScene:run()	
	-- push loading UI to the running scene
	toolkit.disableTouch()
	
	-- init module base data
	self:initVars()
	
	-- get server data by net
	self:getData()
end

-- ************************************

-- ************************************

return testScene
