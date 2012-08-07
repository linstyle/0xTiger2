--[[
local l_lindp=1
g_lindp=1
for n in pairs(_G) do print(n) end
]]--
--����һ
--[[
a = 1     -- create a global variable
-- change current environment to a new empty table
setfenv(1, {})
print(a)
]]--



--���Ӷ�
--[[
a = 1 -- create a global variable
-- change current environment
setfenv(1, {_G = _G})
_G.print(a)       --> nil
_G.print(_G.a)    --> 1

]]--


--������
--[[
a = 1
local newgt = {}     -- create new environment
setmetatable(newgt, {__index = _G})
setfenv(1, newgt)    -- set it
print(a)             --> 1
]]--

--[[
--������
a=1
print(a)
]]--