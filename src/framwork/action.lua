action = {}

-- action bubble
function action.bubble(target, duration)
	local size = target:getContentSize()
	local currScaleX = target:getScaleX()
	local currScaleY = target:getScaleY()
	
	local n = 3
	local dScale = 0.2
	local dMove = size.height * dScale
	local duration = duration*1.0/(n*3)
	local moves = {}
	local scales = {}
	for i=1, n do
		scales[#scales+1] = cc.ScaleTo:create(duration, (1-dScale/n*(n+1-i))*currScaleY)
		if(i==1)then
			moves[#moves+1] = cc.MoveBy:create(duration, cc.p(0, dMove*0.5))
			moves[#moves+1] = cc.MoveBy:create(duration*2, cc.p(0, -dMove*1.5))
			scales[#scales+1] = cc.ScaleTo:create(duration*2, (1+dScale/n*(n-i))*currScaleY)	
			dMove = dMove * 1.5
		elseif(i ~= n)then
			moves[#moves+1] = cc.MoveBy:create(duration, cc.p(0, dMove))
			moves[#moves+1] = cc.MoveBy:create(duration/3*2, cc.p(0, -dMove*2/3))
			scales[#scales+1] = cc.ScaleTo:create(duration/3*2, (1+dScale/n*(n-i))*currScaleY)	
			dMove = dMove * 0.5
		else
			moves[#moves+1] = cc.MoveBy:create(duration, cc.p(0, dMove))
			moves[#moves+1] = cc.MoveBy:create(duration/3*2, cc.p(0, -dMove/3))
			scales[#scales+1] = cc.ScaleTo:create(duration/3*2, (1+dScale/n*(n-i))*currScaleY)	
		end
	end
	
	local seqMoves = cc.Sequence:create(unpack(moves))
	local seqScales = cc.Sequence:create(unpack(scales))
		
	target:runAction(seqMoves)
	target:runAction(seqScales)
end

return action