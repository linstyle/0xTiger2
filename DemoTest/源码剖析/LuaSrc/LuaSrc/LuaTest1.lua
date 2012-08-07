
local sum=0;

function fun2(i)
	sum=sum+i
end

function fun1()
	for i=1,1000 do
		fun2(i)
	end
end


fun1()
print(sum)