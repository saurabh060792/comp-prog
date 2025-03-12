#include <iostream>
#include <cstdio>

#define MAX 100000

using namespace std;

long long int l,r,q,n,i,arr[MAX],sum[MAX],sq[MAX],temp;


int main()
{
	scanf("%lld",&n);
	for(i=0;i<n;i++) {
		scanf("%lld",&arr[i]);
		sum[i] = 0;
		sq[i] = arr[i]*arr[i];
	}

	sum[0] = arr[0];
	for(i=1;i<n;i++) {
		sum[i] = sum[i-1] + arr[i];
		sq[i] = sq[i-1] + sq[i];
	}

	scanf("%lld",&q);
	for(i=0;i<q;i++) {
		scanf("%lld%lld",&l,&r);
		if(l!=0) {
			temp = (sum[l-1]-sum[r])*(sum[l-1]-sum[r]) + (sq[r]-sq[l-1]);
			printf("%lld\n", temp/2);
		}
		else {
			temp = (sum[r]*sum[r]) + sq[r];
			printf("%lld\n", temp/2);
		}
	}

	return 0;
}