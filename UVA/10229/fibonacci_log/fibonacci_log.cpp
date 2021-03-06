#include "stdafx.h"
#include <iostream>
#include <stdio.h>
using namespace std;

const int MAX = 1000;

int f[MAX] = { 0 };



int fib(int n, int m)
{	
	
	//Casos base
	if (n == 0)
		return 0;
	if (n == 1 || n == 2)
		return (f[n] = 1);

	// Ya se ejecuto
	if (f[n])
		return f[n];

	int k = (n & 1) ? (n + 1) / 2 : n / 2;

// si N es impar o par

	/* 
	Funciona!!!!!!!
	if (n & 1) {
		f[n]= (fib(k,m)*fib(k, m) + fib((k-1),m)*fib((k-1),m))%m;
	}
	else {
		f[n] =  ((2 * fib((k-1),m) + fib(k,m))*fib(k,m))%m;
	}
	*/
	f[n] = (n & 1) ? (fib(k, m)*fib(k, m) + fib((k - 1), m)*fib((k - 1), m)) % m :
		((2 * fib((k - 1), m) + fib(k, m))*fib(k, m)) % m;

	

	return f[n];
}

int main()
{
	
	int n, m;

	while (cin >> n >> m) {
		// potencia por bits 1<<m = pow(2,m)
		m = 1 << m;
		cout <<fib(n, m) << endl;
		//printf("%d ", fib(n,m));
	}
		
	return 0;
}

