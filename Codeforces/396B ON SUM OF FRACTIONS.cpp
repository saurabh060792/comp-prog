#include <iostream>
#include <cstdio>

using namespace std;

long long gcd(long long a,long long b);
bool prime(int n);

int main()
{
	int t,n;
	long long p,q,num,dem,k;
	cin>>t;
	while(t--) {
		cin>>n;
		p = n, q = n+1;
		while(!prime(p)) p--;
		while(!prime(q)) q++;
		num = (n+1-p-q)*2+p*q, dem = p*q*2;				//ans = (1/2) - (1/p) + (n-p+1/pq)
		k = gcd(num,dem);
		num /= k, dem /= k;
		cout<<num<<'/'<<dem<<endl;
	}
	return 0;
}

bool prime(int n)
{
	for(int i=2;i*i<=n;i++)
		if(!(n%i)) return false;
	return true;
}

long long gcd(long long a,long long b)
{
	return b?gcd(b,a%b):a;
}

//http://codeforces.com/blog/entry/10961