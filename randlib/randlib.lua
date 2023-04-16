RANDLIB_MAX = 32767
INT_LIMIT = 2147483657
seed = 0
prevSeed = seed

local Randlib = {}

function NewRand()
	repeat
		seed = os.time()
	until seed ~= prevSeed
	prevSeed = seed
	return ((8253739 * seed + 2396403) % INT_LIMIT) % RANDLIB_MAX
end

function Randlib.Set_RANDLIB_MAX(value)
	RANDLIB_MAX = value
end

function Randlib.Randint(min, max)
	if min > max then
		max1 = max
		max = min
		min = max1
	end
	min = math.floor(min+0.5)
	max = math.floor(max+0.5)
	local value = min + (NewRand()%(max - min +1))
	return value
end

function Randlib.Randfloat(min, max)
	if min > max then
		max1 = max
		max = min
		min = max1
	end
	pre = Randlib.Randint(math.floor(min),math.floor(max)-1)
	post = NewRand()/10^ math.floor(math.log(RANDLIB_MAX, 10))
	return pre + post
end

function Randlib.Randchar(excludeWhitespaces)
	local c
	local whitespaces ={' ', '\t', '\n'}
	if not excludeWhitespaces then
		if Randlib.Randint(0,6) == 6 then
			c = whitespaces[Randlib.Randint(1,3)]
		else
			c = string.char(Randlib.Randint(33,126))
		end
	else
		c = string.char(Randlib.Randint(33,126))
	end
	return c
end

function Randlib.Randstring(length, excludeWhitespaces)
	local text = ""
	for i=0, length-1 do
		repeat
			c = Randlib.Randchar(excludeWhitespaces)
		until c ~= nil
		text = text .. c
	end
	return text
end

return Randlib 
