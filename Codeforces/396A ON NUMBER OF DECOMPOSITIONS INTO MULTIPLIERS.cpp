#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int mod=1000000007;

long long Pow(long long x,long long y);

int n,m=0,p[1000000],x,i,j;
long long Fac[100000],Rev[100000],ans=1;

int main()
{
	scanf("%d",&n);

	Fac[0]=1;
	for(i=1;i<100000;i++)
	Fac[i]=Fac[i-1]*i%mod;
	for(i=0;i<100000;i++)
	Rev[i]=Pow(Fac[i],mod-2);

	for(i=0;i<n;i++) {
		scanf("%d",&x);
		for(j=2;j*j<=x;j++)
			while(!(x%j)) {
				x/=j;
				p[m++]=j;
			}
		if(x>1) p[m++]=x;
	}
	sort(p,p+m);

	for(i=0,j=0;i<m;i=j) {
		while(j<m&&p[i]==p[j]) j++;
		ans=ans*Fac[j-i+n-1]%mod*Rev[n-1]%mod*Rev[j-i]%mod;
	}
	printf("%I64d\n",ans);
	return 0;
}

long long Pow(long long x, long long y)
{
	if(!y) return 1;
	long long t=Pow(x*x%mod,y/2);
	if(y&1) t=t*x%mod;
	return t;
}