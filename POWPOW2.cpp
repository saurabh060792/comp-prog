#include <cstdio>
#include <iostream>
#include <algorithm>

#define MAX 100005
#define MOD1 1000000007
#define MOD2 500000003

using namespace std;

typedef long long int lli;

lli CRT(lli *n, lli *a, lli size);
lli mulInverse(lli a, lli b);
lli powMod(lli a, lli b, lli m);
void f1(lli C[2*MAX][2], lli m);
void f(lli *C, lli m);

lli C1[MAX],C2[2*MAX][2],C3[MAX];

int main()
{
	lli i,t,a,b,n,prime1[] = {2, MOD2}, coef1[2], prime2[] = {2, 1681, 148721}, coef2[3];
	scanf("%lld",&t);
	C1[0] = 1;
	for(i=1;i<MAX;i++) C1[i] = 0;
	f1(C2, 1681);
	f(C3, 148721);

	while(t--) {
		scanf("%lld%lld%lld",&a,&b,&n);
		if(b==0){
			printf("1\n");
			continue;
		}
		coef2[0] = C1[n];
		coef2[2] = C3[n];


		coef2[1] = (C2[2*n][0]*mulInverse(C2[n][0],1681))%1681;
		coef2[1] = (coef2[1]*mulInverse(C2[n][0],1681))%1681;
		coef2[1] = (coef2[1]*powMod(41, C2[2*n][1]-2*C2[n][1], 1681))%1681;

		// printf("%lld %lld %lld %lld\n",coef2[0],coef2[1],coef2[2],CRT(prime2, coef2, 3));
		coef1[0] = b%2?1:0;
		coef1[1] = powMod(b, CRT(prime2, coef2, 3), MOD2);
		// printf("%lld %lld %lld\n",coef1[0],coef1[1],CRT(prime1, coef1, 2));

		printf("%lld\n",powMod(a,CRT(prime1, coef1, 2),MOD1));
	}
	return 0;
}


void f1(lli C[2*MAX][2], lli m)
{
	lli i,t;
	C[0][0]=1;
	C[0][1]=0;
	for(i=1;i<2*MAX;i++){
		t=i;
		C[i][1]=C[i-1][1];
		while(t%41 == 0) {
			t=t/41;
			C[i][1]++;
		}
		C[i][0] = (t*C[i-1][0])%1681;
	}
}

void f(lli *C, lli m)
{
	int i;
	C[0] = 1;
	for(i=1;i<MAX;i++) C[i] = ((((C[i-1]*2)*(2*i-1))%m) * mulInverse(i%m, m))%m;
}

lli powMod(lli a, lli b, lli m)
{
	lli temp;
	if(b==0) return 1;
	if(b==1) return a%m;
	if(b%2) return (a*powMod(a,b-1,m))%m;
	else {
		temp = powMod(a,b/2,m);
		return (temp * temp)%m;
	}
}

// returns x where (a * x) % b == 1
lli mulInverse(lli a, lli b)
{
	lli b0 = b, t, q, x0 = 0, x1 = 1;
	if(b==1) return 1;
	while(a>1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if(x1<0) x1 += b0;
	return x1;
}

lli CRT(lli *n, lli *a, lli size)
{
	lli p, i, prod = 1, sum = 0;
	for(i=0;i<size;i++) prod *= n[i];
	for(i=0;i<size;i++) {
		p = prod / n[i];
		sum += a[i] * mulInverse(p, n[i]) * p;
	}
	return sum % prod;
}
 

