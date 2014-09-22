local director = require "director"

ui = {}

function ui.Node()
	return cc.Node:create()
end

function ui.Scene()
	return cc.Scene:create()
end

function ui.Layer()
	return cc.Layer:create()
end

function ui.LayerColor(color)
    return cc.LayerColor:create(color)
end


function ui.Sprite(image)
	return cc.Sprite:create(image)
end

function ui.SpriteBg(file)
	local sp = cc.Sprite:create("bg/" .. file)
	local size = sp:getContentSize()
	sp:setScaleX(director.width / size.width)
	sp:setScaleX(director.height / size.height)
    sp:setAnchorPoint(cc.p(0,0))
    sp:setPosition(cc.p(0,0))
	return sp
end

function ui.ProgressTimer(sprite)
    return cc.ProgressTimer:create(sprite)
end

-- widgets
function ui.Layout()
    return ccui.Layout:create()
end

function ui.Widget()
	return ccui.Widget:create()
end

function ui.binWidget(file)
    return ccs.GUIReader:getInstance():widgetFromBinaryFile(file)
end

function ui.jsonWidget(file)
    return ccs.GUIReader:getInstance():widgetFromJsonFile(file)
end

function ui.Button()
    return ccui.Button:create()
end

function ui.CheckBox()
	return ccui.CheckBox:create()
end

function ui.ImageView()
	local image = ccui.ImageView:create()
    --image:setAnchorPoint(cc.p(0.5,0.5))
    return image
end

function ui.RichText()
	return ccui.RichText:create()
end

function ui.Slider()
	return ccui.Slider:create()
end

function ui.Text(text)
    local t = ccui.Text:create()
    if text then
        t:setString(text)
    end
    return t
end

function ui.Text2()
    local t = ccui.Text:create()
    if text then
        t:setString(text)
    end
    return t
end

function ui.Text3()
    local t = ccui.Text:create()
    if text then
        t:setString(text)
    end
    return t
end

function ui.TextAtlas()
	return ccui.TextAtlas:create()
end

function ui.TextBMFont()
	return ccui.TextBMFont:create()
end

function ui.TextField()
	return ccui.UICCTextField:create()
end

-- scroll widgets
function ui.ScrollView()
	return ccui.ScrollView:create()
end

function ui.PageView()
	return ccui.PageView:create()
end

function ui.ListView()
	return ccui.ListView:create()
end

--[[
function ui.RingListView()
    return ccui.RingListView:create()
end
--]]

function ui.maskLayer()
    --[[
    --swallow touch event
    local function onTouch(event, x, y)
        --if event == "began", "moved", "ended", "cancled" then return true end
        return true
    end
    --]]
    local layer = ui.Layer()
    layer:setTouchEnabled(true)
    layer:registerScriptTouchHandler(function (event, x, y)
        return true
    end)

    return layer
end

function ui.messageBox(message, okCallBack, cancelCallBack)
    local mask = ui.Layer()
    local widget = ccs.GUIReader:getInstance():widgetFromJsonFile(res.ccs_messageBox)
    local layer = cc.Layer:create()
    layer:addChild(mask)
    layer:addChild(widget)

    local okBtn = widget:getChildByName("okBtn")
    okBtn:setScaleY(0.6)
    --okBtn:setTitleText("")
    local cancelBtn = widget:getChildByName("cancelBtn")
    cancelBtn:setScaleY(0.6)
    
    local textArea = widget:getChildByName("textArea")
    local boxBg = widget:getChildByName("boxBg")
    local boxSize = boxBg:getContentSize()
    boxBg:loadTexture("Battle_choose_background_1.png")
    local currBoxSize = boxBg:getContentSize()
    boxBg:setScaleX(boxSize.width/currBoxSize.width)
    boxBg:setScaleY(0.85)
    textArea:setText(message)
    mask:setTouchEnabled(true)
    okBtn:setTouchEnabled(true)
    cancelBtn:setTouchEnabled(true)
    boxBg:setTouchEnabled(true)
    
    --swallow touch event
    local function maskOnTouch(event, x, y)
        if event == "began" then
            return true
        elseif event == "ended" then
            if(okCallBack and (not cancelCallBack))then
                layer:removeFromParent()
                okCallBack()    
            elseif(okCallBack and cancelCallBack)then
                layer:removeFromParent()
                cancelCallBack()
            end
            return true
        end
    end
    local function okHandler(sender,eventType)
        if eventType == ccui.TouchEventType.ended then
            layer:removeFromParent()
            if(okCallBack)then
                okCallBack()
            end
        end
    end
    local function cancelHandler(sender,eventType)
        if eventType == ccui.TouchEventType.ended then
            layer:removeFromParent()
            if(cancelCallBack)then
                cancelCallBack()
            elseif(okCallBack)then
                okCallBack()
            end
        end
    end
    local function maskOnly(sender,eventType)
        --cclog("boxBg be touched!")
    end
    
    mask:registerScriptTouchHandler(maskOnTouch)
    okBtn:addTouchEventListener(okHandler)
    cancelBtn:addTouchEventListener(cancelHandler)
    boxBg:addTouchEventListener(maskOnly)
    
    return layer
end

function ui.layerMgr()
    local lmgr = { currLayer = nil }
    
    function lmgr:add(layer)
        self[layer] = layer
    end
    function lmgr:remove(layer)
        if self.currLayer == layer then
            self.currLayer = nil
        end
        self[layer] = nil
    end
    -- all layers will be set out of window when layer == nil 
    function lmgr:set(layer)
        if self.currLayer and self.currLayer ~= layer then
            self.currLayer:setPosition(director.out)
        end
        if self[layer] then
            layer:setPosition(cc.p(0,0))
            self.currLayer = layer
        end
    end

    return lmgr
end

function ui.getSpriteFrame(file)
    return cc.SpriteFrameCache:getInstance():getSpriteFrameByName(file)
end

function ui.spriteWithFrame(file)
    local frame = cc.SpriteFrameCache:getInstance():getSpriteFrameByName(file)
    return cc.Sprite:createWithSpriteFrame(frame)
end

function ui.scale9SpriteWithFrame(file)
    local frame = cc.SpriteFrameCache:getInstance():getSpriteFrameByName(file)
    return cc.Scale9Sprite:createWithSpriteFrame(frame)
end
--[[
function ui.pushWindow(mbox)
    director.getRunningScene():addChild(mbox, 1000)
end

function util.getRingListOnTouchEndedFunc()
    local flag = false
    local function isTouchEnded()
        return flag
    end
    local function setTouchEnded(ended)
        flag = ended
    end

    return isTouchEnded, setTouchEnded
end

function util.RichTextOfNum(n, imgName)
    local text = util.RichText()
    local revertN = 0

    repeat
        revertN = revertN*10 + n%10
        n = math.floor(n/10)
    until(n==0)
    repeat
        local subText = ccui.RichElementImage:create(6, cc.c3b(255, 255, 255), 255, imgName .. revertN%10 .. ".png")
        revertN = math.floor(revertN/10)
        text:pushBackElement(subText)
    until(revertN==0)
    return text
end
--]]

return ui
