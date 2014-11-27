local range = 10000

constant = 
{
	-- zorders' range
	zorder_1  = range * 1,
	zorder_2  = range * 2,
	zorder_3  = range * 3,
	zorder_4  = range * 4,
	zorder_5  = range * 5,
	zorder_6  = range * 6,
	zorder_7  = range * 7,
	zorder_8  = range * 8,
	zorder_9  = range * 9,
	zorderMax = range * 100,
	zorderNet = range * 200,

	transitionTime = 0.65,
}

function getuidir()
	winSize = cc.Director:getInstance():getWinSize()
	rate = winSize.width/winSize.height
	rate1 = 960/640.0
	rate2 = 1280.0/720.0
	rate3 = 1024.0/768.0
	sub1 = (rate1 - rate) / rate
	if sub1 < 0 then 
		sub1 = -sub1
	end
	sub2 = (rate2 - rate) / rate;
	if sub2 < 0 then
		sub2 = -sub2
	end
	sub3 = (rate3 - rate) / rate;
	if sub3 < 0 then
		sub3 = -sub3
	end

	if sub1 < sub2 and sub1 < sub3 then
		constant.uiPath = "res/ui/960_640/"
	end
	if sub2 < sub1 and sub2 < sub3 then
		constant.uiPath = "res/ui/1280_720/"
	end

	constant.uiPath = "res/ui/1024_768/"

	constant.uiPath = "res/ui/1280_720/"
end

getuidir()

return constant