--require "LuaRequire\\LuaRequireA"

--PrintInfo()

function foo(a,b)
	local x
	do local c = a-b end
	local a=1
	while true do
		local name,value=debug.getlocal(1,a)
		if not name then break end
		print(name, value)
		a=a+1
	end
end



--foo(10,20)




--尝试局部
function getvarvalue(name)
	local value,found

	for i=1, math.huge do
		local n,v=debug.getlocal(2,i)
		if not n then break end
		if n==name then
			value=v
			found=true
		end
	end	


	if found then return value end
	
--尝试非局部
	local func = debug.getinfo(2, "f").func
	print(tostring(func))
	for i=1, math.huge do
		local n,v=debug.getupvalue(func,i)
		if not n then break end
		if n==name then return v end
	end
	
	return getfenv(func)[name]
end


function foo1()
	local g1=10;
	print(getvarvalue('g1'))
end


print(tostring(foo1))
print(foo1())
