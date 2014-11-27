db = 
{
	--GamerInit.proto
	heroInfo = nil, -- 玩家信息,  PB_GamerInit_S2C, type: pbstr
	npcInfo = nil, --NPC信息，  PB_GamerGetNPC_S2C, type: pbmsg
	--GamerEquip.proto
	equipInfo = nil, --装备信息 PB_GamerGetEquip_S2C , type: pbstr
	otherEquipInfo = nil, --他人装备信息 PB_GamerGetEquip_S2C , type: pbstr
	--GamerSoldier.proto
	soldierInfo = nil, --士兵信息 PB_GamerGetSoldier_S2C , type: pbstr
	otherSoldierInfo = nil, --他人士兵信息 PB_GamerGetSoldier_S2C , type: pbstr
	recruitSoldierInfo = nil, -- 招募士兵信息 PB_GamerRecruitSoldier_S2C ，type:pbstr
	--GamerFriends.proto
	friendsInfo = nil, --好友信息 PB_GamerGetFriends_S2C , type: pbstr
	achieveInfo = nil, --成就信息,PB_GamerAchieve_S2C, type: pbstr

	currTDMsg = nil, --当前塔防信息, PB_GamerStartPVE_S2C, from: GamerPVE.proto

	perDayInfo = nil, --每日信息,PB_GamerPerDayOper_S2C,type: pbstr
	otherArmyMsg = nil, --集训营敌方数据 PB_GamerCamp,type: pbstr
	myArmyMsg = nil, --集训营 我方数据 PB_GamerCamp,type: pbstr
	blackList = nil, -- 黑名單
}

function db.get(key)
	return db[key]
end

function db.set(key, value)
	db[key] = value
end

function db.getEquipNumByID(id)
	local num = 0
	local equipInfo = db.get("equipInfo")
	for i=1,equipInfo.equip:len() do
		if equipInfo.equip:get(i).eid == id then
			num = num + equipInfo.equip:get(i).count
		end
	end
	return num
end

return db