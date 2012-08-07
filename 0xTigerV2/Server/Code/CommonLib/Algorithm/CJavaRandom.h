/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/07/13                                                         
    ����˵����  һ��java���������
*/

#pragma once
#include <time.h>
#include <assert.h>

class CJavaRandom
{
public:
	CJavaRandom()
	{
		seed = clock();
	}

    int next(int bits)
    {
        unsigned __int64 oldseed, nextseed;

        oldseed = seed;
        nextseed = (oldseed * multiplier + addend) & mask;
        seed = nextseed;

		/*
			��java�����������ƣ���λ�������
			��C++��޷�����Ĭ�����Ϊ0
		*/
        return (int) (nextseed >> (48 - bits));
    }
	int nextInt(int n) 
	{
		assert(n>0);

        if ((n & -n) == n)  // i.e., n is a power of 2
            return (int)((n * (long)next(31)) >> 31);

        int bits, val;
        do 
		{
            bits = next(31);
            val = bits % n;
        } while (bits - val + (n-1) < 0);
        return val;
    } 

private:

public:


private:
	unsigned __int64 seed;
	static unsigned __int64 multiplier;
	static unsigned __int64 addend;
	static unsigned __int64 mask;

};

