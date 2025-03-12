#include <iostream>
#include <cstdio>
#include <string.h>
#include <utility>
#include <map>
#include <algorithm>

#define MAX 100005
#define MAXTREE 500005

using namespace std;

typedef long long int lli;

void updateBIT(lli idx ,lli val);
lli readBIT(lli idx);
lli strtoint(char *s);
lli pown(lli n);

pair<lli, lli> p[MAX];
map<lli, lli> m;
lli combine[MAX*2], bit[MAXTREE];

int main()
{
	lli n,i;
	lli x,ans=0;
	char temp[20];
	scanf("%lld",&n);
	for(i=0;i<n;i++) {
		scanf("%s",temp);
		p[i].first = strtoint(temp);
		reverse(temp, temp+strlen(temp));
		p[i].second = strtoint(temp);
		// cout<<p[i].first<<"  "<<p[i].second<<endl;
	}

	for(i=0;i<n;i++) {
		combine[i] = p[i].first;
		combine[i+n] = p[i].second;
	}
	sort(combine, combine+2*n);
	// for(i=0;i<2*n;i++) cout<<combine[i]<<endl;
	// cout<<endl;
	for(i=0;i<2*n;i++) m[combine[i]] = 2*n - i;
	sort(p, p+n);
	for(i=0;i<n;i++) {
		updateBIT(x = m[p[i].second], 1);
		// cout<<m[p[i].second]<<endl;

		ans += readBIT(x - 1);
		// cout<<readBIT(x-1)<<endl;
		// for(int j=0;j<=20;j++) cout<<readBIT(j)<<" ";
		// cout<<endl;
	}
	printf("%lld\n",ans);
}

lli pown(lli n)
{
	lli i;
	lli result=1;
	for(i=0;i<n;i++) result *= 29;
	return result;
}

lli strtoint(char *s)
{
	lli x=0;
	lli i,n=strlen(s);
	for(i=0;i<n;i++) x = (s[i]-'a'+1) + x*29;
	return x*(pown(10-n));
}

lli readBIT(lli idx)
{
	lli sum = 0;
	while (idx > 0) {
		sum += bit[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

void updateBIT(lli idx ,lli val)
{
	while (idx <= MAXTREE){
		bit[idx] += val;
		idx += (idx & -idx);
	}
}