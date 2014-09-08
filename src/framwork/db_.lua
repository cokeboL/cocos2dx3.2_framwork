local db = {}

db.inited = false
db.decodeNumPerFram = 10

db.files = {
	"config/config_cards.db",
    "config/languages.db"
}

db.items = {}

function db.get(itemId)
	if itemId then
		return clone(db.items[itemId])
	end
	return nil
end

function db.init(dbInitedCallback)
	local dbMgr = DBMgr:getInstance()
	local scheduler = cc.Director:getInstance():getScheduler()
	local scheduleEntry
	for _, v in pairs(db.files) do
		dbMgr:addFile(v)
	end
    dbMgr:loadAll()
    
    local function loadItems()
    	local item
    	for i=1, db.decodeNumPerFram do
    		if dbMgr:isAllLoaded() then
    			item = dbMgr:getAndRemoveOneItem()
    			if string.len(item) > 0 then
    				item = json.decode(item)
    				db.items[item.id] = item
    			else
    				scheduler:unscheduleScriptEntry(scheduleEntry)
    				dbMgr:clear()
    				db.inited = true
    				if dbInitedCallback then
    					dbInitedCallback()
    				end
    				break
    			end
    		else
    			item = dbMgr:getAndRemoveOneItem()
    			if string.len(item) > 0 then
    				item = json.decode(item)
    				db.items[item.id] = item
    			else
    				break
    			end
    		end
    	end
    end
	scheduleEntry = scheduler:scheduleScriptFunc(loadItems, 1/30, false);
end

return db