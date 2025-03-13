#include <cstdio>
#include <cmath>
#include <cstring>

#define MAX 1000000000

using namespace std;

typedef long long int lli;

bool isPrime(lli n);

int main()
{
    int t;
	scanf("%d",&t);
	
	while(t--) {
    	lli a, b;
    	scanf("%lld%lld", &a, &b);
    	for (lli i = a; i <= b; i++) {
    		if (isPrime(i)) printf("%lld\n", i);
    	}
    	printf("\n");
    }
	return 0;
}

bool isPrime(lli n) {
	if (n == 0 || n == 1) return false;
	for (lli i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) return false;
	}
	return true;
}
