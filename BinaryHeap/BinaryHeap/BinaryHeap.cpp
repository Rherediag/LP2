
#include <iostream>
#include <algorithm>
#include <math.h>
#include	"binarytree.h"
bool test(int n) {
	binarytree bh;
	int * A = new int[n];
	for (int i = 0; i < n; i++) {
		A[i] = std::rand() % (std::pow(10,9));
		bh.push(A[i]);
	}
	std::sort(A, A + n);
	for (int i = n - 1; i >= 0; i--) {
		if (A[i] = bh.max()) {
			return false;
		}
	}
}
int main()
{
	binarytree tree;
    std::cout << "Hello World!\n"; 
}
