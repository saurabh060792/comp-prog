#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <iostream>

#define MAX 2000006

using namespace std;

typedef long long int lli;

char s[MAX];
int pi[MAX];
map<string, int> hash;

void prefixFunction(char* P, int n);

int main()
{
	int n,t;
	lli ans=0;
	string base;
	scanf("%d",&t);
	while(t--) {
		scanf("%d %s",&n,s);
		prefixFunction(s, n);
		if(n%(n-pi[n-1]-1) || n==1) base.assign(s,n);
		else base.assign(s, n-pi[n-1]-1);
		if(hash.count(base)) hash[base]++;
		else hash[base] = 1;
	}
	for(map<string, int>::iterator it = hash.begin();it!=hash.end();it++) ans += it->second*it->second;
	printf("%lld\n",ans);
	return 0;
}

void prefixFunction(char* P, int n)
{
	int k=-1,i;
	pi[0] = -1;
	for(i=1;i<n;i++) {
		while(k>-1 && P[k+1]!=P[i]) k = pi[k];
		if(P[k+1]==P[i]) k++;
		pi[i] = k;
	}
}

/*
If two palindrom's base is same then the concatination of those tow palindrome
will also be a palindrom
base(S) = A if A^m = S where m is maximum 
*/