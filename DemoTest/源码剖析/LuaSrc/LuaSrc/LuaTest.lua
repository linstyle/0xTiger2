--[[
debug.sethook(print, "l")

function trace(event, line)
	local s=debug.getinfo(2).short_src
	print(s..":"..line)
end

debug.sethook(trace, "l")

trace("event_test", 2)
]]--

local Counters={}
local Names={}


function getname(func)
	local n=Names[func]
	if n.what=="c" then
		return n.name
	end
	
	local lc=string.format("[%s]:%s", n.short_src, n.linedefined)
	if n.namewhat ~= "" then
		return string.format("%s (%s)", lc, n.name)
	else
		return lc
	end
end

local function hook()
	local f=debug.getinfo(2,"f").func
	if Counters[f]==nil then  --第一次调用吗
		Counters[f]=1
		Names[f]=debug.getinfo(2,"Sn")
	else
		Counters[f]=Counters[f]+1
	end
end

local f = loadfile("LuaTest1.lua")
debug.sethook(hook, "c")
f()
debug.sethook()


for func, count in pairs(Counters) do
	print(getname(func), count)
end