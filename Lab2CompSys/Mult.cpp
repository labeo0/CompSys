// ConsoleApplication3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <bitset>

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	bool carry = 0;
	bitset<32> Mcand(30);
	bitset<64> Register(3);

	cout << "Register: " + Register.to_string()<< endl;
	cout << "Register decimal: "<< Register.to_ulong() << endl;
	cout << "Mcand: " + Mcand.to_string()<< endl;
	cout << "Multiplicand decimal: " << Mcand.to_ulong() <<endl;

	cout << ":Multiplying:"<<endl;
	
	for (int i = 0; i < 31; i++)
	{
		if (Register[0])
		{
			for (int y = 0; y < 32; y++)//adding binaries
			{
				if (carry)// carry = 1
				{
					if (Register[y + 31] & Mcand[y])//1+1 +carry
					{
						Register[y + 31] = 1;
						carry = 1;
					}
					else if(Register[y + 31] | Mcand[y])//1+0 + carry
					{
						Register[y + 31] = 0;
						carry = 1;
					}
					else//0+0 + carry
					{
						Register[y + 31] = 1;
						carry = 0;
					}
				}
				else// carry = 0
				{
					if (Register[y + 31] & Mcand[y])//1+1 + carry
					{
						Register[y + 31] = 0;
						carry = 1;
					}
					else if(Register[y + 31] | Mcand[y])//1+0+carry
						Register[y + 31] = 1;
					else//0+0+carry
						Register[y + 31] = 0;

				}
			}
			cout << "Adding Miltiplicand to register: " + Register.to_string() << endl;
		}
		cout << "Shift Register: "+ Register.to_string()<< endl;
		Register >>= 1;
	}
	cout <<"Result Binary: " + Register.to_string()<<endl;
	cout <<"Result decimal: "<<Register.to_ulong() <<endl;

    return 0;
}

