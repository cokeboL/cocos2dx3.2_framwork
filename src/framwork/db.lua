db = {}

function db.get(key)
	return db[key]
end

function db.set(key, value)
	db[key] = value
end

return db