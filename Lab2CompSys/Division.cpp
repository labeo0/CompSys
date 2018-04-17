// ConsoleApplication2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <bitset>
#include <string>
#include <iostream>

using namespace std;

bool Rless(const bitset<64> Remainder, const bitset<64> Divisor)
{
	for (int i = 64 - 1; i >= 0; i--) {
		if (Remainder[i] && !Divisor[i]) return false;
		if (!Remainder[i] && Divisor[i]) return true;
	}
	return false;
}

void substract(bitset<64>& Remainder, bitset<64> Divisor)
{
	int carry = 1;
	for (int i = 0; i < 64; i++)
	{
		Divisor[i] = !Divisor[i];
	}
	for (int y = 0; y < 64; y++)//adding binaries
	{
		if (carry)// carry = 1
		{
			if (Remainder[y] & Divisor[y])//1+1 +carry
			{
				Remainder[y] = 1;
				carry = 1;
			}
			else if (Remainder[y] | Divisor[y])//1+0 + carry
			{
				Remainder[y] = 0;
				carry = 1;
			}
			else//0+0 + carry
			{
				Remainder[y] = 1;
				carry = 0;
			}
		}
		else// carry = 0
		{
			if (Remainder[y] & Divisor[y])//1+1 + carry
			{
				Remainder[y] = 0;
				carry = 1;
			}
			else if (Remainder[y] | Divisor[y])//1+0+carry
				Remainder[y] = 1;
			else//0+0+carry
				Remainder[y] = 0;

		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	bitset<64> Remainder(437);
	bitset<64> Divisor(13);
	bitset<32> Quotient(0);

	cout << "Remainder: " << Remainder.to_string() << endl;
	cout << "Remainder dec: " << Remainder.to_ullong() << endl;

	cout << "Divisor: " << Divisor.to_string() << endl;
	cout << "Divisor dec: " << Divisor.to_ullong() << endl;
	Divisor <<= 32;//переносим делитель в правые 32 бита

	for (int i = 0; i < 32; i++)
	{
		cout<<"Shift Divisor right, Quotient -left"<<endl;
		Divisor >>= 1;
		Quotient <<= 1;
		if (!Rless(Remainder, Divisor))
		{
			cout<<"Remainder - Divisor "<<endl;
			cout<<"Remainder Before "<<Remainder.to_string()<<endl;
			substract(Remainder, Divisor);
			cout<<"Remainder After  "<<Remainder.to_string()<<endl;
			Quotient[0] = 1;
		}
	}
	cout << "Quotient: " << Quotient.to_string() << endl;
	cout << "Quotient dec: " << Quotient.to_ullong() << endl;

    return 0;
}

