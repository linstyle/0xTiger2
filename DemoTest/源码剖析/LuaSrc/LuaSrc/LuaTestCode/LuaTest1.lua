--例子一
--[[
t={}
quest = Quest.CreateQuest(1)
--print(Quest.GetCommonQuestType(quest))
print(getmetatable(quest))
print(quest.GetCommonType())
]]--

Set = {}
local mt={}


--[[
--例子二
function Set.new(l)
	local set={}
	setmetatable(set,mt)
	for _,v in ipairs(l) do set[v] = true end
	return set
end

function Set.union(a,b)
	local res=Set.new{}
	
	for k in pairs(a) do 
		res[k] = true 
	end
	for k in pairs(b) do res[k] = true end 

	return res
end

function Set.intersection(a,b)
	local res=Set.new{}
	for k in pairs(a) do
		res[k]=b[k]
	end
	return res
end

function Set.tostring(set)
	local l={}
	for e in pairs(set) do
		l[#l+1]=e
	end
	return "{"..table.concat(l,",").."}"
end

function Set.print(s)
	print(Set.tostring(s))
end


mt.__add=Set.union

s1=Set.new{10,20,30,50}
s2=Set.new{30,1}
s3=s1+s2
--print(getmetatable(s1))
--print(getmetatable(s2))
Set.print(s3)
]]--


--例子三__index方法

Window={}
Window.prototype={x=0,y=0,width=100,height=100}
Window.mt={}

function Window.new(o)
	setmetatable(o, Window.mt)
	return o
end

Window.mt.__index=function(table, key)
	quest = Quest.CreateQuest(1)
	return Window.prototype[key]

	--return Window.prototype[key]
	quest = Quest.CreateQuest(1)
end

--Window.mt.__index=Window.prototype


w=Window.new{x=10,y=20}
print(w.width)





--例子四__index方法
--[[
function setDefault(t,d)
	local mt={__index=function() return d end}
	setmetatable(t,mt)
end

tab={x=10,y=20}
print(tab.x, tab.z)
setDefault(tab,0)
print(tab.x, tab.z)
]]--


--[[

--例子五--代理一
_t={}

t={}

--创建元表
local mt={
		__index=
		function(t,k)
			print("*access to element "..tostring(k))
			return _t[k]  --访问原来的table
		end,

		__newindex=
		function(t,k,v)
			print("*update of element "..tostring(k).." to "..tostring(v))
			_t[k]=v
		end
}
setmetatable(t,mt)

t[2]="hello"
print(t[2])

]]--

--例子五--代理二
--[[
local index={}

local mt={
	__index=function(t,k)
		print("*access to element "..tostring(k).."	t:"..tostring(t))
		return t[index][k]
	end,
	
	__newindex=function(t,k,v)
		print("*update of element "..tostring(k).." to "..tostring(v))
		t[index][k]=v		
	end
}


function track(t)
	local proxy={}
	proxy[index]=t	
	setmetatable(proxy,mt)
	
	print("t:"..tostring(t).."  proxy:"..tostring(proxy).."  proxy[index]:"..tostring(proxy[index]))
	return proxy
end

t1={}
t1=track(t1)

t2={}
t2=track(t2)

--print("t1:"..tostring(t1).."t2:"..tostring(t2))

t1[2]="hello t1"
print(t1[2])


t2[2]="hello t2"
print(t2[2])

]]--

--[[
--例子六--只读table
function readOnly(t)
	local proxy={}
	local mt={
		__index=t,
		__newindex = 
		function(t,k,v)
			error("attempt to update a read-only table", 2)
		end
	}
	setmetatable(proxy, mt)
	return proxy
end


days=readOnly{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
							"Saturday"}

print(days[1])
days[2]="Noday"

]]--

