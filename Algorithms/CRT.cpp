#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int CRT(int *n, int *a, int n);
int mulInverse(int a, int b);

int main()
{
	int n[] = { 3, 5, 7 }, a[] = { 2, 3, 2 };
	printf("%d\n", CRT(n, a, sizeof(n)/sizeof(n[0])));
	return 0;
}

 
// returns x where (a * x) % b == 1
int mulInverse(int a, int b)
{
	int b0 = b, t, q, x0 = 0, x1 = 1;
	if(b==1) return 1;
	while(a>1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if(x1<0) x1 += b0;
	return x1;
}

int CRT(int *n, int *a, int n)
{
	int p, i, prod = 1, sum = 0;
	for(i=0;i<n;i++) prod *= n[i];
	for(i=0;i<n;i++) {
		p = prod / n[i];
		sum += a[i] * mulInverse(p, n[i]) * p;
	}
	return sum % prod;
}