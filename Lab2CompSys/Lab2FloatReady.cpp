// Lab2Float.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <bitset>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void check_num(float& a, float& b)
{
	if (abs(a) < abs(b))
		swap(a, b);
}
bitset<23> add_bin(bitset<23> a, bitset<23> b, bool substract)//суммируем/отнимаем мантисы
{
	int carry = 0;
	if(substract)
	{
		carry = 1;
		for (int i = 0; i < 23; i++)
		{
			b[i] = !b[i];
		}
	}
	for (int y = 0; y < 23; y++)//adding binaries
	{
		if (carry)// carry = 1
		{
			if (a[y] & b[y])//1+1 +carry
			{
				a[y] = 1;
				carry = 1;
			}
			else if (a[y] | b[y])//1+0 + carry
			{
				a[y] = 0;
				carry = 1;
			}
			else//0+0 + carry
			{
				a[y] = 1;
				carry = 0;
			}
		}
		else// carry = 0
		{
			if (a[y] & b[y])//1+1 + carry
			{
				a[y] = 0;
				carry = 1;
			}
			else if (a[y] | b[y])//1+0+carry
				a[y] = 1;
			else//0+0+carry
				a[y] = 0;
		}
	}


	return a;
}
float add(float a, float b)
{
	float res = 0.0f;
	check_num(a, b);//соглансо алгоритму, abs(a)>abs(b), если не так - поменять местами
	bool asign = 0, bsign = 0, signres = 0;
	bitset<8> aexp(0), bexp(0), resexp(0);
	bitset<23> amantis(0), bmantis(0), resmantis(0);

	long unsigned int temp = 0;

	memcpy(&temp, &a, sizeof(long unsigned int));//копируем из блока памяти флоат 32 бита в блок памяти long unsigned int, чтоб записать представление флоат в битсет
	bitset<32> aset(temp);
	cout <<"Float A dec: "<<a<<endl<<"Bin: "<<aset.to_string() << endl;
	cout<<endl;

	memcpy(&temp, &b, sizeof(long unsigned int));
	bitset<32> bset(temp);
	cout <<"Float B dec: "<<b<<endl<<"Bin: "<<bset.to_string() << endl;

	asign = aset[31];//записываем знаки 0- положительное 1-отрицательное
	bsign = bset[31];

	for (int i = 0; i < 8; i++)//записываем экспоненты
	{
		aexp[i] = aset[23 + i];
		bexp[i] = bset[23 + i];
	}
	for (int i = 0; i < 23; i++)//записываем мантисы
	{
		amantis[i] = aset[i];
		bmantis[i] = bset[i];
	}
	cout<<endl;
	cout<<"Sign A: "<<asign<<endl<<"Exponent A:"<<aexp.to_string()<<endl<<"Mantis A: "<<amantis.to_string()<<endl;
	cout<<"Sign B: "<<bsign<<endl<<"Exponent B:"<<bexp.to_string()<<endl<<"Mantis B: "<<bmantis.to_string()<<endl;
	cout<<endl;

	resexp = aexp;//результат имеет степень равную степени большего числа
	int exp_diff = aexp.to_ulong() - bexp.to_ulong();//разница степеней двух чисел
	cout<<endl;
	cout<<"Exp_diff: "<<exp_diff<<endl;
	cout<<endl;

	bexp = aexp;//добавить можно числа с одинаковой степенью
	amantis >>=1;
	amantis[22] = 1;//подставляем 1 которая есть, но которую не храним :)
	bmantis >>=1;
	bmantis[22] = 1;
	bmantis >>= exp_diff;//сдивагаем на разницу
	
	resmantis = add_bin(amantis,bmantis, asign^bsign);//если знаки разные - отнять, если одинаковые добавлять

	cout <<"ResSign: "<<signres<<endl<<"ResExp: "<<resexp.to_string()<<endl<<"Resmantis: "<<resmantis.to_string()<<endl;
	
	resmantis <<=1;
	stringstream ss;
	ss<<signres<<resexp.to_string()<<resmantis.to_string();
	bitset<32> setres(ss.str());
	temp = setres.to_ulong();
	memcpy(&res,&temp,sizeof(float));
	return res;
}

int _tmain(int argc, _TCHAR* argv[])
{
	float a = 9.75;
	float b = -.005;

	/*cout << a << ":" << b << endl;
	check_num(a, b);
	cout << a << ":" << b << endl;*/
	float result = 0.0f;
	result = add(a, b);
	cout<<"Final Result: "<<result<<endl;
	return 0;
}

