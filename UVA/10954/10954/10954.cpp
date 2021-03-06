#include <queue>
#include<algorithm>
#include <iostream>

int main()
{
	int n, a;
	//Lee el input
	while (scanf("%d", &n))
	{ //si es 0 termina el programa
		if (n == 0)
			break;
		//crea el priority
		std::priority_queue<int>pq;
		//sum guarda la suma c se usa como buffer de la suma
		int sum = 0, c = 0;
		//Lee lo que venga despues de ingresar el tamaño y arma el queue
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &a);
			// el -a es para ordenarlo teniendo el "mayor" al ultimo
			pq.push(-a);
		}
		for (int i = 0; i < n - 1; i++)
		{
			int d = -pq.top();
			pq.pop();
			int b = -pq.top();
			pq.pop();
			c = d + b;
			sum += c;
			pq.push(-c);
		}
		printf("%d\n", sum);
	}


	return 0;
}