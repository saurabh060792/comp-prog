#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

#define MAX 20
#define MAXSET (1<<20)

using namespace std;

typedef long long int lli;

lli dp[MAXSET][MAX];
vector<lli> graph[MAX];

lli bitcount(lli i);
lli first(lli mask);
lli bit(lli i, lli mask);


int main()
{
	lli i,j,n,m,u,v,ans,mask;
	cin>>n>>m;
	for(i=0;i<m;i++) {
		cin>>u>>v;
		u--,v--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	for(mask=0;mask<(1<<n);mask++) {
		for(i=0;i<n;i++) {
			dp[mask][i] = 0;
			if(bitcount(mask) == 1 && bit(i, mask) == 1) dp[mask][i] = 1;
			else if(bitcount(mask) > 1 && bit(i, mask) == 1 && first(mask) != i) {
				for(j=0;j<graph[i].size();j++) {
					dp[mask][i] += dp[mask^(1<<i)][graph[i][j]]; 
				}
			}
		}
	}

	ans = 0;
	for(mask=1;mask<(1<<n);mask++) {
		for(i=0;i<n;i++) {
			if(bitcount(mask)>2 && find(graph[i].begin(), graph[i].end(), first(mask))!= graph[i].end())
				ans += dp[mask][i];
		}
	}
	cout<<ans/2<<endl;
	return 0;
}

lli bit(lli i, lli mask)
{
	return (mask & (1<<i))>0?1:0;
}

lli first(lli mask)
{
	if(!mask) return -1;
	int i=0;
	while(mask) {
		if(mask%2) return i;
		else {
			mask/=2;
			i++;
		}
	}
	return -1;
}

lli bitcount(lli i)
{
	const unsigned MASK1  = 0x55555555;
	const unsigned MASK2  = 0x33333333;
	const unsigned MASK4  = 0x0f0f0f0f;
	const unsigned MASK8  = 0x00ff00ff;
	const unsigned MASK16 = 0x0000ffff;

	i = (i&MASK1 ) + (i>>1 &MASK1 );
	i = (i&MASK2 ) + (i>>2 &MASK2 );
	i = (i&MASK4 ) + (i>>4 &MASK4 );
	i = (i&MASK8 ) + (i>>8 &MASK8 );
	i = (i&MASK16) + (i>>16&MASK16);

	return i;
}