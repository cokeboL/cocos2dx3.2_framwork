local director = require "director"
local uiWidgetFunctions = require "uiWidgetFunctions/uiWidgetFunctions"

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


function ui.GrayLayer()
    return cc.LayerColor:create(cc.c4b(0,0,0,150))
end

function ui.Sprite(image)
	return cc.Sprite:create(image)
end

function ui.LabelTTF(default, fontFamily, size)
    return cc.LabelTTF:create(default, fontFamily, size)
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
    return ccs.GUIReader:getInstance():widgetFromBinaryFile(constant.uiPath .. file)
end

function ui.jsonWidget(file)
    return ccs.GUIReader:getInstance():widgetFromJsonFile(constant.uiPath .. file)
end

function ui.binArmature(file)
    if file == "pkskill_412100001" or file == "pkskill_412100003" then
        ccs.ArmatureDataManager:getInstance():addArmatureFileInfo(file .. ".csb")
    else
        ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("skilleff/" .. file .. ".csb")
    end
    return ccs.Armature:create(file)
end

--[[
function ui.jsonArmature(file)
    return ccs.GUIReader:getInstance():widgetFromJsonFile(constant.uiPath .. file)
end
--]]

function ui.Button()
    return ccui.Button:create()
end

function ui.CheckBox()
	local cbox = ccui.ImageView:create()

    local tab = { isSelected = false }
    function tab.cBoxOnTouch(sender,eventType)
        local self = tab
        if eventType == ccui.TouchEventType.began then
            if self.moving then
                cbox:loadTexture(self.moving, self.isFrame)
            elseif self.isSelected then
                cbox:loadTexture(self.unselected, self.isFrame)
            else
                cbox:loadTexture(self.selected, self.isFrame)
            end
        elseif eventType == ccui.TouchEventType.moved then

        elseif eventType == ccui.TouchEventType.ended then
            self.isSelected = (not self.isSelected)
            if self.isSelected then
                cbox:loadTexture(self.selected, self.isFrame)
                self.listner(sender, ccui.CheckBoxEventType.selected)
            else
                cbox:loadTexture(self.unselected, self.isFrame)
                self.listner(sender, ccui.CheckBoxEventType.unselected)
            end
        elseif eventType == ccui.TouchEventType.canceled then
            if self.isSelected then
                cbox:loadTexture(self.selected, self.isFrame)
            else
                cbox:loadTexture(self.unselected, self.isFrame)
            end
        end
        
    end
    function tab:loadTextures(unselected, selected, moving, isFrame)
        self.unselected  = unselected
        self.selected = selected
        if moving and moving ~= "" then
            self.moving = moving 
        else
            self.moving = nil
        end
        
        self.isFrame = isFrame or 0

        cbox:loadTexture(self.unselected, self.isFrame)
    end
    function tab:addTouchEventListener(listner)
        self.listner = listner
    end
    function tab:setSelectedState(state)
        if self.isSelected ~= state then
            self.isSelected = state
            if self.isSelected then
                cbox:loadTexture(self.selected, self.isFrame)
            else
                cbox:loadTexture(self.unselected, self.isFrame)
            end
        end
    end

    cbox:setTouchEnabled(true)
    cbox:addTouchEventListener(tab.cBoxOnTouch)
    
    tolua.setpeer(cbox, tab)

    return cbox
end

function ui.CheckBox2()
    local cboxBg = ccui.ImageView:create()
    local cboxText = ccui.ImageView:create()
    cboxBg:addChild(cboxText)

    local tab = { isSelected = false }
    function tab.cBoxOnTouch(sender,eventType)
        local self = tab

        if eventType == ccui.TouchEventType.began then
            if self.isSelected then
                cboxBg:loadTexture(self.bgNorm, self.isFrame)
                cboxText:loadTexture(self.textNorm, self.isFrame)
            else
                cboxBg:loadTexture(self.bgSelected, self.isFrame)
                cboxText:loadTexture(self.textSelected, self.isFrame)
            end
        elseif eventType == ccui.TouchEventType.moved then
            
        elseif eventType == ccui.TouchEventType.ended then
            self.isSelected = (not self.isSelected)
            if self.isSelected then
                self.listner(sender, ccui.CheckBoxEventType.selected)
            else
                self.listner(sender, ccui.CheckBoxEventType.unselected)
            end
        elseif eventType == ccui.TouchEventType.canceled then
            if self.isSelected then
                cboxBg:loadTexture(self.bgSelected, self.isFrame)
                cboxText:loadTexture(self.textSelected, self.isFrame)
            else
                cboxBg:loadTexture(self.bgNorm, self.isFrame)
                cboxText:loadTexture(self.textNorm, self.isFrame)
            end
        end
    end
    function tab:loadTextures(bgNorm, bgSelected, textNorm, textSelected, isFrame)
        self.bgNorm  = bgNorm
        self.bgSelected = bgSelected
        self.textNorm  = textNorm
        self.textSelected = textSelected
        
        self.isFrame = isFrame or 0

        cboxBg:loadTexture(self.bgNorm, self.isFrame)
        cboxText:loadTexture(self.textNorm, self.isFrame)
        
        local bgSize = cboxBg:getContentSize()
        cboxText:setPosition(cc.p(bgSize.width/2, bgSize.height/2))
    end
    function tab:addTouchEventListener(listner)
        self.listner = listner
    end

    function tab:setSelectedState(state)
        if self.isSelected ~= state then
            self.isSelected = state
            if self.isSelected then
                cboxBg:loadTexture(self.bgSelected, self.isFrame)
                cboxText:loadTexture(self.textSelected, self.isFrame)
            else
                cboxBg:loadTexture(self.bgNorm, self.isFrame)
                cboxText:loadTexture(self.textNorm, self.isFrame)
            end
        end
    end

    cboxBg:setTouchEnabled(true)
    cboxBg:addTouchEventListener(tab.cBoxOnTouch)
    
    tolua.setpeer(cboxBg, tab)

    return cboxBg
end

function ui.ImageView(file, isFrame)
    if file then
    	local image = ccui.ImageView:create()
        isFrame = isFrame or 0
        image:loadTexture(file, isFrame)
        return image
    else
        return ccui.ImageView:create()
    end
end

function ui.RichText()
	return ccui.RichText:create()
end

--richText:ignoreContentAdaptWithSize(true/false)
--richText:setContentSize(cc.size(100, 100))    
--[[
function ui.HtmlText(file, id, ...)
    local function convert(s)
        local head = '<font color="#'
        local tail = '</font>'
        local headLen = string.len('<font color="#FFFFFF">')
        local tailLen = string.len(tail)
        local fontBeginLen = string.len(head)
        local fontBegin = string.find(s, head)
        if not fontBegin then
            return { text_1 = s }
        end
        
        local textCount = 0
        local fontEnd
        local texts = {}
        repeat
            textCount = textCount + 1
            if fontBegin > 1 then
                texts["text_" .. textCount] = string.sub(s, 1, fontBegin)
                s = string.sub(s, fontBegin)
            else
                fontEnd = string.find(s, tail)
                texts["text_" .. textCount] = string.sub(s, fontBegin+headLen, fontEnd-1)

                texts["color_" .. textCount] = "0x" .. string.sub(s, fontBegin+fontBeginLen, fontBegin+fontBeginLen+5)
                texts["color_" .. textCount] = tonumber(texts["color_" .. textCount])
                
                s = string.sub(s, fontEnd+tailLen)
            end
            fontBegin = string.find(s, head)
        until(not fontBegin)
        if string.len(s) > 0 then
            texts["text_" .. (textCount+1)] = s
        end

        return texts
    end
    local richText = ui.RichText()

    local itemString = require("cfg/" .. file)[id]
    
    print(itemString)
    local texts = convert(itemString)
    --local texts = item.texts

    local fmt = {...}
    local needFormat = false
    if #fmt > 0 then
        needFormat = true
    end

    local n = 0
    for _, _ in pairs(texts) do
        n = n+1
    end

    local i = 1
    local j = 1
    local fmtCount = 1
    local color = cc.c3b(0x00,0x00,0x00)
    local tmpColor, r, g, b, tmpText, tmpRichText, fmtPos
    repeat
        tmpColor = texts["color_" .. i]
        if tmpColor then
            print("***** tmpColor ", j)
            r = math.floor(tmpColor/0x00FFFF)
            g = math.floor((tmpColor-r)/0x0000FF)
            b = tmpColor-r-g
            color = cc.c3b(r,g,b)
            j = j + 1

        else
            color = cc.c3b(0x00,0x00,0x00)
        end
        tmpText = texts["text_" .. i] 
        if tmpText then
            print("***** tmpText ", j)
            if needFormat then
                fmtPos = string.find(tmpText, '%%')
                if fmtPos then
                    repeat
                        tmpText = string.format(tmpText, fmt[fmtCount])
                        fmtCount = fmtCount + 1
                        fmtPos = string.find(tmpText, '%%')
                    until(not fmtPos)
                end
            end
            tmpRichText = ccui.RichElementText:create(1, color, 255, tmpText, "Helvetica", 26)
            richText:pushBackElement(tmpRichText)
            j = j + 1
        end
        i = i + 1
    until(j > n)

    local tab = {}
    function tab:setSize(size)
        self:ignoreContentAdaptWithSize(false)
        self:setContentSize(size)
    end
    tolua.setpeer(richText, tab)
    
    return richText
end
--]]


--richText:ignoreContentAdaptWithSize(true/false)
--richText:setContentSize(cc.size(100, 100))    
function ui.HtmlText(text, ...)
    if #{...} > 0 then
        text = string.format(text, ...)
    end

    local richText = ui.RichText()

    local defaultSize = 26
    local defaultFont = "Helvetica"
    local defaultColor = cc.c3b(0xFF,0xFF,0xFF) --cc.c3b(0xFF,0xFF,0xFF)
    local defaultImgColor = cc.c3b(0xFF,0xFF,0xFF)

    local head_font = "<font"
    local tail_font = "</font>"
    local head_img = "<img"
    local tail_img = "/>"
    local head_norm = "<"
    local tail_norm = ">"

    local type_norm = 1
    local type_font = 2
    local type_img = 3

    local texts = {}
    local elements = {}

    local pbegin, pend, s1, s2, s3, count, elementNum

    local function parse_norm(s)
        elementNum = #elements + 1
        local richElementText = ccui.RichElementText:create(elementNum, defaultColor, 255, s, defaultFont, defaultSize)
        richText:pushBackElement(richElementText)
        elements[elementNum] = richElementText
    end
    local function parse_img(s)
        elementNum = #elements + 1
        pbegin = string.find(s, 'src="') + 5
        s = string.sub(s, pbegin)
        pend = string.find(s, '"') - 1
        s = string.sub(s, 1, pend)
        local richElementImage = ccui.RichElementImage:create(elementNum, defaultImgColor, 255, s)
        richText:pushBackElement(richElementImage)
        elements[elementNum] = richElementImage
    end
    local function parse_font(s)
        local size, color
        pend = string.find(s, tail_norm)
        s1 = string.sub(s, 1, pend)
        pbegin = string.find(s1, 'size="')
        if pbegin then
            s2 = string.sub(s1, pbegin+6)
            pend = string.find(s2, '"')
            size = string.sub(s2, 1, pend-1)
            size = tonumber(size)
        else
            size = defaultSize
        end
        pbegin = string.find(s1, 'color="#')
        if pbegin then
            local r, g, b
            s2 = string.sub(s1, pbegin+8)
            pend = string.find(s2, '"')
            color = tonumber("0x" .. string.sub(s2, 1, pend-1))
            r = math.floor(color / 0x00FFFF)
            g = math.floor(color % 0x010000 / 0x000100)
            b = color - r * 0x010000 - g * 0x000100
            color = cc.c3b(r, g, b)
        else
            color = defaultColor
        end
        pend = string.find(s, tail_norm)
        s = string.sub(s, pend+1)
        repeat
            pbegin = string.find(s, head_img)
            if not pbegin then
                
                pbegin = string.find(s, tail_font)
                s = string.sub(s, 1, pbegin-1)
                elementNum = #elements + 1
                local richElementText = ccui.RichElementText:create(elementNum, color, 255, s, defaultFont, size)
                richText:pushBackElement(richElementText)
                elements[elementNum] = richElementText
                return
            else
                if pbegin == 1 then
                    pend = string.find(s, tail_norm)
                    s2 = string.sub(s, 1, pend)
                    parse_img(s2)
                else
                    s1 = string.sub(s, 1, pbegin-1)
                    elementNum = #elements + 1
                    local richElementText = ccui.RichElementText:create(elementNum, color, 255, s1, defaultFont, size)
                    richText:pushBackElement(richElementText)
                    elements[elementNum] = richElementText

                    s2 = string.sub(s, pbegin)
                    pend = string.find(s2, tail_norm)
                    s = string.sub(s2, pend+1)
                    s2 = string.sub(s2, 1, pend)
                    parse_img(s2)
                end
            end
        until(not pbegin)
    end
    
    local function split(s)
        if string.len(s) == 0 then return end
        count = #texts + 1
        if string.sub(s, 1, 5) == "<font" then
            pend = string.find(s, tail_font) + 6
            texts[count] = type_font
            texts[count+1] = string.sub(s, 1, pend)
            if pend+1 ~= string.len(s)then
                s = string.sub(s, pend+1)
            else
                return
            end
        elseif string.sub(s, 1, 4) == "<img" then
            pend = string.find(s, tail_img) + 1
            texts[count] = type_img
            texts[count+1] = string.sub(s, 1, pend)
            if pend+1 ~= string.len(s)then
                s = string.sub(s, pend+1)
            else
                return
            end
        else
            texts[count] = type_norm
            pbegin = string.find(s, head_norm)
            if pbegin then
                texts[count+1] = string.sub(s, 1, pbegin-1)
                s = string.sub(s, pbegin)
            else
                texts[count+1] = s
                return
            end
            
        end
        split(s)
    end
    split(text)
    for i=1, (#texts)/2 do
        if texts[i*2-1] == type_norm then
            parse_norm(texts[i*2])
        elseif texts[i*2-1] == type_font then
            parse_font(texts[i*2])
        else
            parse_img(texts[i*2])
        end
    end
    
    return richText
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

function ui.Utf8Text(str, fontsize, color, width, direction)
    local utf8 = require("utf8_simple")
    print("--- utf8 str: " .. utf8.len(str) .. " str: " .. str)
    local s = str
    local currStart = 1
    local currByteLen = 0
    local len = utf8.len(s)
    local newline = ""
    local currline = ""
    local node = ui.Node()
    local currText = ui.Text()
    currText:setFontSize(fontsize)
    local i = 0
    local lineCount = 0
    local function pushText(text)

        lineCount = lineCount + 1
        print("-- " .. lineCount .. " " .. currline)
        local height = text:getContentSize().height
        if direction == "left" then
            -- 左对齐
            text:setAnchorPoint(cc.p(0, 0.5))
            text:setPosition(cc.p(-width / 2,(height*0.8)*(1-lineCount)))
        else
            -- 居中对齐
            text:setAnchorPoint(cc.p(0.5,0.5))
            text:setPosition(cc.p(0,(height*0.8)*(1-lineCount)))
        end
        
        text:setColor(color)
        node:addChild(text, lineCount, lineCount)
    end
    while true do
        i = i+1
        if i > utf8.len(s) then
            pushText(currText)
            break
        end
        newline = utf8.sub(s, currStart, i)
        currText:setString(newline)
        if currText:getContentSize().width <= width then
            currline = newline
        else
            currText:setString(currline)
            pushText(currText)
            s = utf8.sub(s, i, -1)
            if utf8.len(s) == 0 then
                break
            end
            currline = ""
            i = 0
            currStart = 1
            currText = ui.Text()
            currText:setFontSize(fontsize)
        end
        
    end
    
    return node
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


function ui.BagView()
    --local layer = ui.Layer()
    local bag = ui.ScrollView()
    bag:setBounceEnabled(true)
    bag:setTouchEnabled(true)
    bag:setInnerContainerSize(cc.size(0,0))

    local tab = 
    {
        scrollDirection = ccui.ScrollViewDir.vertical,
        putDirection = ccui.ScrollViewDir.horizontal,
        itemNum = 0,
        numInRow = 1,
        numInColumn = 1,
        rowInternal = 0,
        columnInternal = 0,
        model = nil,
        modelSize = cc.size(0,0),
    }
    --layer:addChild(bag)
    function tab:setSize(size)
        self.size = size
        self:setContentSize(size)
        self:setInnerContainerSize(size)
    end
    function tab:setScrollDirection(direction)
        self.scrollDirection  = direction
        self:setDirection(direction)
    end
    function tab:setPutDirection(direction)
        self.putDirection  = direction
    end
    function tab:setItemNumInRow(num)
        self.numInRow = num
    end
    function tab:setRowInternal(internal)
        self.rowInternal = internal
    end
    function tab:setItemNumInColumn(num)
        self.numInColumn = num
    end
    function tab:setColumnInternal(internal)
        self.columnInternal = internal
    end
    function tab:setModel(model)
        self.model = model
        local scalex = model:getScaleX()
        local scaley = model:getScaleY()
        self.modelSize = model:getContentSize()
        self.modelSize.width = self.modelSize.width * scalex
        self.modelSize.height = self.modelSize.height * scaley
    end
    function tab:setModelSize(size)
        self.modelSize = size
    end
    function tab:autoInternal(model)
        if self.putDirection == ccui.ScrollViewDir.horizontal then
            self.rowInternal = (self.size.height - self.modelSize.height*self.numInColumn) / (self.numInColumn-1)
            self.columnInternal = (self.size.width - self.modelSize.width*self.numInRow) / (self.numInRow-1)
        else
            self.rowInternal = (self.size.height - self.modelSize.height*self.numInColumn) / (self.numInColumn-1)
            self.columnInternal = (self.size.width - self.modelSize.width*self.numInRow) / (self.numInRow-1)
        end
    end
    function tab:resize()
        if self.putDirection == ccui.ScrollViewDir.horizontal then
            local rowIdx = self.itemNum % self.numInRow
            if rowIdx == 0 then
                rowIdx = self.numInRow
            end
            local rowNum = math.floor((self.itemNum-1)/self.numInRow) + 1
            local newHeight = self.modelSize.height*rowNum + self.rowInternal*(rowNum-1)
            if newHeight < self.size.height then
                newHeight = self.size.height
            end
            local innerSize = self:getInnerContainerSize()
            if newHeight ~= innerSize.height then
                local heightAdd = newHeight - innerSize.height
                innerSize.height = newHeight
                self:setInnerContainerSize(innerSize)
                local pos
                for i=1, self.itemNum do
                    pos = cc.p(self.items[i]:getPosition())
                    pos.y = pos.y + heightAdd
                    self.items[i]:setPosition(pos)
                end
            end
        else
            local innerSize = self:getInnerContainerSize()
            local rowNum = self.itemNum/self.numInColumn
            if self.itemNum%self.numInColumn > 0 then
                rowNum = math.floor(rowNum+1)
            end
            innerSize.width = self.modelSize.width*rowNum + self.columnInternal*(rowNum-1)
            self:setInnerContainerSize(innerSize)
        end
    end
    function tab:addItem(item)
        self:addChild(item)
        
        self.items = self.items or {}
        self.itemNum = self.itemNum + 1
        self.items[self.itemNum] = item

        local itemInfo = { idx = self.itemNum }
        tolua.setpeer(item, itemInfo)

        local itemPos = cc.p(0,0)
        local innerSize = self:getInnerContainerSize()

        if self.putDirection == ccui.ScrollViewDir.horizontal then
            local rowIdx = self.itemNum % self.numInRow
            if rowIdx == 0 then
                rowIdx = self.numInRow
            end
            
            itemPos.x = self.modelSize.width*(rowIdx-0.5) + self.columnInternal*(rowIdx-1)
            if self.itemNum % self.numInRow == 1 then
                local rowNum = math.floor((self.itemNum-1)/self.numInRow) + 1
                local newHeight = self.modelSize.height*rowNum + self.rowInternal*(rowNum-1)
                if newHeight > innerSize.height then
                    local heightAdd = newHeight - innerSize.height
                    innerSize.height = newHeight
                    self:setInnerContainerSize(innerSize)
                    local preItem, prePos
                    for i=1, self.itemNum-1 do      
                        preItem = self.items[i]
                        prePos = cc.p(preItem:getPosition())
                        prePos.y = prePos.y + heightAdd--self.modelSize.height + self.rowInternal
                        preItem:setPosition(prePos)
                    end
                end
            end
            if self.itemNum == 1 then
                itemPos.y = self.size.height - self.modelSize.height/2
            else
                if self.itemNum % self.numInRow == 1 then
                    _, itemPos.y = self.items[self.itemNum-1]:getPosition()
                    itemPos.y = itemPos.y - (self.modelSize.height+self.rowInternal)
                else
                    _, itemPos.y = self.items[self.itemNum-1]:getPosition()
                end
            end
        else
            local rowIdx = math.floor((self.itemNum-1)/self.numInColumn) + 1
            local columnIdx = self.itemNum%self.numInColumn
            if columnIdx == 0 then
                columnIdx = self.numInColumn
            end
            itemPos.x = self.modelSize.width*(rowIdx-0.5) + self.columnInternal*(rowIdx-1)
            itemPos.y = self.size.height - (self.modelSize.height*(columnIdx-0.5) + self.rowInternal*(columnIdx-1))
            if self.itemNum % self.numInColumn == 1 then
                local rowNum = math.floor(self.itemNum/self.numInColumn) + 1
                innerSize.width = self.modelSize.width*rowNum + self.columnInternal*(rowNum-1)
                self:setInnerContainerSize(innerSize)
            end
        end
        item:setPosition(itemPos)
    end
    function tab:removeItem(idx)
        local x, y
        local maxIdx = self.itemNum
        
        if idx > maxIdx then return end

        for i = maxIdx, idx+1, -1 do
            x, y = self.items[i-1]:getPosition()
            if y then
                self.items[i]:setPosition(cc.p(x,y))
            else
                self.items[i]:setPosition(x)
            end
            self.items[i].idx = i-1
        end
        self.items[idx]:removeFromParent()
        table.remove(self.items, idx)
        self.itemNum = self.itemNum - 1
        
        self:resize()
    end
    function tab:removeAllItem()
        local itemNum = self.itemNum
        for i=1, itemNum do
            self:removeItem(1)
        end
    end
    function tab:getItemNum()
        return self.itemNum
    end
    function tab:getItem(idx)
        return self.items[idx]
    end

    tolua.setpeer(bag, tab)

    return bag
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

function ui.callbackLayer(callback)
    local layer = ui.Layer()
    layer:setTouchEnabled(true)
    layer:registerScriptTouchHandler(function (event, x, y)
        local _x, _y = layer:getPosition()
        print("xxxxxxx: 111 ", _x, _y)
        if event == "ended" then 
            if callback then
                if _x == 0 and _y == 0 then
                    print("xxxxxxx: 2222")
                    callback()
                end
            end
        end
        if _x == 0 and _y == 0 then
            return true
        else
            return false
        end
    end)

    return layer
end

-- create a edit box
function ui.soldierEditBox(boxBg, editName, funVar)
    local bg = cc.Scale9Sprite:create("leirongkuang.png")
    -- local bg = ui.scale9SpriteWithFrame("leirongkuang.png")
    local bg1 = boxBg:getChildByName(editName)
    local label = bg1:getChildByName("label")
    local label1 = ui.LabelTTF(label:getString(), "marker felt", 25)
    local label2 = ui.LabelTTF("", "marker felt", 25)
    local defaultLabel = ui.LabelTTF(label:getString(), "marker felt", 25)
    label2:setVisible(false)
    defaultLabel:setVisible(false)
    bg1:setVisible(false)
    local size = bg:getContentSize()
    local name = cc.EditBox:create(cc.size(size.width, size.height), bg)
    name:setPosition(bg1:getPosition())
    name:setPlaceHolder("")
    name:setMaxLength(16)
    name:setInputMode(cc.EDITBOX_INPUT_MODE_SINGLELINE)
    name:setReturnType(cc.KEYBOARD_RETURNTYPE_SEND )
    name:registerScriptEditBoxHandler(funVar)
    name:addChild(label1)
    name:addChild(label2)
    name:addChild(defaultLabel)
    label1:setTag(1)
    label2:setTag(2)
    defaultLabel:setTag(3)
    label1:setPosition(label:getPosition())
    label2:setPosition(label:getPosition())
    defaultLabel:setPosition(label:getPosition())

    return name
end

function ui.messageBox(msg, callback)
    local layer = ui.Layer()
    local box = ui.binWidget("messageBox.csb")
    box:setTouchEnabled(false)
    layer:addChild(box)
    layer:setTouchEnabled(true)

    local text = box:getChildByName("text")
    text:setString(msg)

    local function layerOnTouch(event, x, y)
        if event == "ended" then
            if callback then
                callback()
            end
            layer:removeFromParent()
        end
        return true
    end
    layer:registerScriptTouchHandler(layerOnTouch)
    return layer
end

--[[
function ui.messageBox(message, okCallBack, cancelCallBack)
    local mask = ui.Layer()
    local widget = ccs.GUIReader:getInstance():widgetFromJsonFile(res.ccs_messageBox)
    local layer = cc.Layer:create()
    layer:addChild(mask)
    layer:addChild(widget)

    local okBtn = widget:getChildByName("okBtn")
    okBtn:setScaleY(0.6)
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
    end
    
    mask:registerScriptTouchHandler(maskOnTouch)
    okBtn:addTouchEventListener(okHandler)
    cancelBtn:addTouchEventListener(cancelHandler)
    boxBg:addTouchEventListener(maskOnly)
    
    return layer
end
--]]

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
            if self.currLayer.onHide then
                self.currLayer:onHide()
            end
        end
        if self[layer] then
            layer:setPosition(cc.p(0,0))
            if layer.onShow then
                layer:onShow()
            end
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


--[[
local icon = ui.Icon({bg = "whiteIconBg.png", head = "107400025.png", border = "whiteFrame.png"}, function(icon) 
    print(icon.bg, icon.head, icon.border)
end)
icon:setPosition(director.center)
local layer = ui.Layer()
layer:addChild(self.icon)
]]

function ui.Icon(equipment, eid, iconBg, hasNum, itemNum, scale)
    -- equipment 物品配置表
    -- eid 物品id
    -- iconBg icon的model，为一个ccsprite(image)
    -- hasNum 是否在右下角显示数量
    -- itemNum 数量值
    -- scale 缩放比例
    local quality = equipment[eid].quality
    local qualitySp
    local qualitySp1
    local bgSp = cc.Node:create()
    bgSp:setContentSize(iconBg:getContentSize())
    bgSp:setAnchorPoint(iconBg:getAnchorPoint())
    bgSp:setPosition(iconBg:getPosition())
    iconBg:getParent():addChild(bgSp)
    iconBg:setVisible(false)

    if quality == 1 then
      qualitySp = cc.Sprite:create("image/qualityBg/white_1.png")
      qualitySp1 = cc.Sprite:create("image/qualityBg/white_2.png")
    elseif quality == 2 then
      qualitySp = cc.Sprite:create("image/qualityBg/green_1.png")
      qualitySp1 = cc.Sprite:create("image/qualityBg/green_2.png")
    elseif quality == 3 then
      qualitySp = cc.Sprite:create("image/qualityBg/blue_1.png")
      qualitySp1 = cc.Sprite:create("image/qualityBg/blue_2.png")
    elseif quality == 4 then
      qualitySp = cc.Sprite:create("image/qualityBg/purple_1.png")
      qualitySp1 = cc.Sprite:create("image/qualityBg/purple_2.png")
    elseif quality == 5 then
      qualitySp = cc.Sprite:create("image/qualityBg/orange_1.png")
      qualitySp1 = cc.Sprite:create("image/qualityBg/orange_2.png")
    elseif quality == 6 then
      qualitySp = cc.Sprite:create("image/qualityBg/red_1.png")
      qualitySp1 = cc.Sprite:create("image/qualityBg/red_2.png")
    elseif quality == 7 then
      qualitySp = cc.Sprite:create("image/qualityBg/yellow_1.png")
      qualitySp1 = cc.Sprite:create("image/qualityBg/yellow_2.png")
    else
      cclog("quality is error")
    end

    qualitySp:setScale(scale)
    qualitySp:setPosition(cc.p(46, 47))
    qualitySp:setLocalZOrder(1)
    qualitySp1:setScale(scale)
    qualitySp1:setPosition(cc.p(46, 47))
    qualitySp1:setLocalZOrder(2)
    bgSp:addChild(qualitySp)
    bgSp:addChild(qualitySp1)

    local str2 = string.sub(eid,0,2)
    if str2 == "36" then
        local str = "10"..string.sub(eid,3,string.len(eid))
        signSp = cc.Sprite:create("image/head/"..str..".png")
        if signSp then
            signSp:setScale(scale)
            signSp:setLocalZOrder(4)
            signSp:setPosition(cc.p(46,47))
            bgSp:addChild(signSp)
        end
    elseif str2 == "30" or str2 == "31" or str2 == "32" or str2 == "33" then
        local str = "2"..string.sub(eid,2,string.len(eid))
        local equippeper_down = cc.Sprite:create("image/equippeper_down.png")
        equippeper_down:setPosition(cc.p(46,47))
        bgSp:addChild(equippeper_down)
        equippeper_down:setLocalZOrder(3)
        equippeper_down:setScale(1.0)
        signSp = cc.Sprite:create("image/item/"..str..".png")
        if signSp then
            signSp:setScale(scale * 2)
            signSp:setLocalZOrder(4)
            signSp:setPosition(cc.p(46,47))
            bgSp:addChild(signSp)
        end
        local equippeper_up = cc.Sprite:create("image/equippeper_up.png")
        equippeper_up:setPosition(cc.p(46,47))
        bgSp:addChild(equippeper_up)
        equippeper_up:setLocalZOrder(4)
        equippeper_up:setScale(1.0)
    else
        local signSp = cc.Sprite:create("image/item/"..equipment[eid].iconID..".png")
        if signSp then
            signSp:setLocalZOrder(4)
            signSp:setPosition(cc.p(46, 47))
            bgSp:addChild(signSp)
        end
    end
    
    if hasNum then
        local numLb = cc.LabelTTF:create(itemNum, "Marker Felt", 20)
        numLb:setAnchorPoint(cc.p(1.0, 0))
        numLb:setPosition(cc.p(bgSp:getContentSize().width - 10, 10))
        numLb:setLocalZOrder(5)
        bgSp:addChild(numLb)
    end
end

function ui.itemIcon(info,touchHandler)
    local qualityImage = ui.binWidget("itemModel.csb"):getChildByName("qualityImage"):clone()
    qualityImage:setTag(info.leid)
    local qualityborder = qualityImage:getChildByName("qualityBorder")
    local itemImage = qualityImage:getChildByName("itemImage")
    itemImage:setTag(info.leid)
    local itemNumLabel = qualityImage:getChildByName("itemNumLabel")
    local quality = info.quality
    if quality == 1 then
      qualityborder:loadTexture("image/qualityBg/white_1.png")
      qualityImage:loadTexture("image/qualityBg/white_2.png")
    elseif quality == 2 then
      qualityborder:loadTexture("image/qualityBg/green_1.png")
      qualityImage:loadTexture("image/qualityBg/green_2.png")
    elseif quality == 3 then
      qualityborder:loadTexture("image/qualityBg/blue_1.png")
      qualityImage:loadTexture("image/qualityBg/blue_2.png")
    elseif quality == 4 then
      qualityborder:loadTexture("image/qualityBg/purple_1.png")
      qualityImage:loadTexture("image/qualityBg/purple_2.png")
    elseif quality == 5 then
      qualityborder:loadTexture("image/qualityBg/orange_1.png")
      qualityImage:loadTexture("image/qualityBg/orange_2.png")
    elseif quality == 6 then
      qualityborder:loadTexture("image/qualityBg/red_1.png")
      qualityImage:loadTexture("image/qualityBg/red_2.png")
    elseif quality == 7 then
      qualityborder:loadTexture("image/qualityBg/yellow_1.png")
      qualityImage:loadTexture("image/qualityBg/yellow_2.png")
    else
      return nil
    end
    if math.floor(info.eid/10000000) == 30 or math.floor(info.eid/10000000) == 31 or math.floor(info.eid/10000000) == 32 or math.floor(info.eid/10000000) == 33 then
        info.eid = info.eid%100000000 + 200000000
    end
    itemImage:loadTexture("item/"..info.eid..".png")
    if info.showNum == true then
        itemNumLabel:setString(""..info.num)
    else
        itemNumLabel:setString("")
    end
    local function onItemClick(sender,eventType)
        if eventType == ccui.TouchEventType.began then
        
        elseif eventType == ccui.TouchEventType.ended then
            if touchHandler then
                touchHandler(info)
            end
        elseif eventType == ccui.TouchEventType.canceled then

        end
    end
    qualityImage:addTouchEventListener(onItemClick)
    qualityImage:setAnchorPoint(0.5,0.5)
    qualityImage:setTouchEnabled(true)
    return qualityImage
end

function ui.showTip(str)
    local label = cc.LabelTTF:create(str, "Marker Felt", 30)
    local size = cc.Director:getInstance():getWinSize()
    label:setPosition(size.width/2.0,size.height/2.0)
    label:setColor(cc.c3b(255, 255, 0))
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(label,10)
    local function removeSelf()
        label:removeFromParentAndCleanup(true)
    end
    local action = cc.Spawn:create(cc.MoveBy:create(1, cc.p(0,100)),cc.FadeOut:create(1))
    label:runAction(cc.Sequence:create(action,cc.CallFunc:create(removeSelf)))
end

function ui.soldierIcon(info, touchHandler)
    local soldierItem = ui.binWidget("soldierItem.csb")
    local bg = soldierItem:getChildByName("bg")
    bg = bg:clone()
    if info.id ~= 0 then
        local head = bg:getChildByName("head")
        head:loadTexture("head/"..info.id..".png")
        local jobIcon = bg:getChildByName("jobIcon")
        jobIcon:loadTexture("jobicon/"..info.jobicon..".png")
        local LvLabel = bg:getChildByName("LvLabel")
        LvLabel:setString("LV."..info.lv)
        bg:setTag(info.id)
    else
        local head = bg:getChildByName("head")
        head:loadTexture("headnull.png")
        local jobIcon = bg:getChildByName("jobIcon")
        jobIcon:setVisible(false)
        local LvLabel = bg:getChildByName("LvLabel")
        LvLabel:setVisible(false)
    end
    
    if info.showTrainType ~= nil and info.showTrainType == true then
        if info.trainType == 1 then
            bg:getChildByName("trainImage"):loadTexture("title85.png")
        elseif info.trainType == 2 then
            bg:getChildByName("trainImage"):loadTexture("title86.png")
        elseif info.trainType == 3 then
            bg:getChildByName("trainImage"):loadTexture("title84.png")
        end
    else
        bg:getChildByName("trainImage"):setVisible(false)
    end

    local size = bg:getContentSize()
    bg:setTouchEnabled(true)
    local function headOnTouch(sender,eventType)
        if eventType == ccui.TouchEventType.began then
        
        elseif eventType == ccui.TouchEventType.ended then
            touchHandler(info)
        elseif eventType == ccui.TouchEventType.canceled then

        end
    end
    bg:addTouchEventListener(headOnTouch)
    bg:setAnchorPoint(cc.p(0.5,0.5))
    return bg
end
function ui.skillDetailBox(info)
    if info.skillIconid == nil then
        return nil
    end
    local skillDeatailBox = ui.binWidget("skillDetailBox_1.csb")
    local scene = cc.Director:getInstance():getRunningScene()
    scene:addChild(skillDeatailBox,20)
    local bg = skillDeatailBox:getChildByName("Image_1")
    local skillImage = bg:getChildByName("skillImage")
    skillImage:loadTexture("skillicon/"..info.skillIconid..".jpg")
    local skillNameLabel = bg:getChildByName("skillNameLabel")
    skillNameLabel:setString(""..info.skillname)
    local blueLabel = bg:getChildByName("blueLabel")
    blueLabel:setString(""..info.blueNum)
    local CDLabel = bg:getChildByName("CDLabel")
    CDLabel:setString(""..info.cdTime)
    local desPos = bg:getChildByName("Image_9")
    local des = ui.HtmlText(info.des)
    des:setSize(desPos:getContentSize())
    des:ignoreContentAdaptWithSize(false)
    des:setPosition(desPos:getPosition())
    bg:addChild(des)
    local function closeskillDetailBox(sender,eventType)
        if eventType == ccui.TouchEventType.began then
            scheduleOnce(scene, function()
            skillDeatailBox:removeFromParent(true)
            end, 0)
        end
    end
    skillDeatailBox:addTouchEventListener(closeskillDetailBox)
end
function ui.selectAnimation(item,scaleSize)

    local itemSize = item:getContentSize()
    local cache = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("image/texiao/xuanzhong.plist")
    local signSelectedSP = cc.Sprite:createWithSpriteFrame(cache:getSpriteFrame(string.format("xuanzhong_1.png")))
    signSelectedSP:setName("signSelectedSP")
    item:addChild(signSelectedSP,1,100)

    local animFrames = {}
    for j=1, 19 do 
        local frame = cache:getSpriteFrame(string.format("xuanzhong_%d.png", j))
        animFrames[j] = frame
    end
    local animation = cc.Animation:createWithSpriteFrames(animFrames, 2/19)
    signSelectedSP:runAction(cc.RepeatForever:create(cc.Animate:create(animation)))
    --signSelectedSP:setPosition(cc.p(46,47))
    local signSelectedSPSize = signSelectedSP:getContentSize()
    signSelectedSP:setAnchorPoint(0,0)
    signSelectedSP:setScaleX(itemSize.width/signSelectedSPSize.width)
    signSelectedSP:setScaleY(itemSize.height/signSelectedSPSize.height)
    if scaleSize then
        signSelectedSP:setScale(scaleSize)
    end
end


function ui.confirmWindow(text, confirmCallBack, cancelCallBack, cancelTex, confirmTex)--显示内容 取消按钮图片 确认图片 取消消息 确认消息
    -- body
    local layer = nil
    local function closeCb()
        -- body
        layer:removeFromParent()
    end
    layer = ui.callbackLayer(closeCb)

    
    local widget = ui.binWidget("Confirm_1.csb")
    layer:addChild(widget)
    local text1 = widget:getChildByName("text")
    local label = ui.Utf8Text(text, 25,cc.c3b(255, 255, 255), 449)
    if label then
        local m,n = text1:getPosition()
        label:setPosition(cc.p(m, n+35))
        widget:addChild(label)
    end
   -- local ttf = cc.LabelTTF:create("", "marker felt", 23)
    --ttf:setPosition(cc.p(text1:getPosition()))
    --ttf:setDimensions(cc.size(text1:getContentSize()))
    --ttf:setDimensions(cc.size(textt:getTextAreaSize()))
    --print("setDimensions", text1:getContentSize().width, text1:getContentSize().hight)
    --widget:addChild(ttf)
    --ttf:setString(text)

    local cancel = widget:getChildByName("cancel")
    local confirm = widget:getChildByName("confirm")

    local function removeFunc()
        -- body
        layer:removeFromParent()
    end

    local function  clickCancel(sender, eventType)
        -- body
        if eventType == ccui.TouchEventType.ended then
            if cancelCallBack then
                cancelCallBack()
            end
            layer:runAction(cc.Sequence:create(cc.DelayTime:create(0.1), cc.CallFunc:create(removeFunc)))
        end
    end

    local function  clickConfirm(sender, eventType)
        -- body
        if eventType == ccui.TouchEventType.ended then
            if confirmCallBack then
                confirmCallBack()
            end
            layer:runAction(cc.Sequence:create(cc.DelayTime:create(0.1), cc.CallFunc:create(removeFunc)))
        end
    end
    cancel:addTouchEventListener(clickCancel)
    confirm:addTouchEventListener(clickConfirm)


    local cancelBg = widget:getChildByName("cancelTex")
    local confirmBg = widget:getChildByName("confirmTex")
    if confirmTex then
        confirmBg:loadTexture(confirmTex)
    end
    if cancelTex then
        cancelBg:loadTexture(cancelTex)
    end

    local running = director.getRunningScene()
    running:addChild(layer)
end


function ui.bubbleTip(text)
    -- body
    local label = ui.LabelTTF(text, "marker felt", 25)
    label:setColor(cc.c3b(255, 255, 0))
    label:setPosition(director.center)
    local running = director.getRunningScene()
    running:addChild(label)

    local function clean()
        -- body
        label:removeFromParent()
    end
    label:runAction(cc.Sequence:create(cc.Spawn:create(cc.ScaleTo:create(1.5, 1.5), cc.MoveBy:create(1.5, cc.p(0, 400))), cc.CallFunc:create(clean)))
end


return ui
