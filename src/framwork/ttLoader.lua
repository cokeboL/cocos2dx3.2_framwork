local fileUtils = cc.FileUtils:getInstance()
local frameCache = cc.SpriteFrameCache:getInstance()
local textureCache = cc.TextureCache:getInstance()

local ttLoader = 
{
	loadingNum = 0,
	ok = true,
}

ttLoader.images = {}
ttLoader.plists = {}

function ttLoader:loadImages(files)	
	if type(files) == 'string' then
		files = { [1] = files }
	end
	
	if type(files) ~= 'table' then
		return
	end
	
	for _, file in pairs(files) do
		self.images[#self.images+1] = file
	end
	
	self.ok = false
	
	local file
	local function load_()
		
		if #self.images > 0 then
			file = self.images[1]
			table.remove(self.images, 1)
			
			local tfile = fileUtils:fullPathForFilename(file .. ".png")
			if not tfile then
				tfile = fileUtils:fullPathForFilename(file .. ".pvr.ccz")
			end
			local function onTxextureLoaded(texture)
				load_()
			end
			if tfile then
				textureCache:addImageAsync(tfile, onTxextureLoaded)
			else
				load_()
			end
		else
			self.ok = true
			if callback then
				callback()
			end
		end
	end
	load_()
end

function ttLoader:loadPlists(files, callback)
	--[[
	if callCount % 2 == 1 then
		files = loadList1
	else
		files = loadList2
	end
	callCount = callCount + 1
	--]]
	
	if type(files) == 'string' then
		files = { [1] = files }
	end
	
	if type(files) ~= 'table' then
		return
	end
	
	for _, file in pairs(files) do
		self.plists[#self.plists+1] = file
	end
	
	self.ok = false
	
	local file
	local function load_()
		if #self.plists > 0 then
			file = self.plists[1]
			table.remove(self.plists, 1)

			local pfile = fileUtils:fullPathForFilename(file .. ".plist")
			local tfile = fileUtils:fullPathForFilename(file .. ".pvr.ccz")
			if not tfile then
				tfile = fileUtils:fullPathForFilename(file .. ".png")
			end
			local function onTxextureLoaded(texture)
				frameCache:addSpriteFrames(pfile, texture);
				load_()
			end
			if pfile and tfile then
				textureCache:addImageAsync(tfile, onTxextureLoaded)
			else
				load_()
			end
		else
			self.ok = true
			if callback then
				callback()
			end
		end
	end
	load_()
end

return ttLoader