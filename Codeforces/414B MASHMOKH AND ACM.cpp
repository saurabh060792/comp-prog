#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

#define MAX 2003
#define MOD 1000000007

using namespace std;

typedef long long int lli;

lli dp[MAX][MAX];
vector<lli> divisor[MAX];

void findDivisor();

int main()
{
	lli n,k,sum=0,i,j,m;
	cin>>n>>k;
	findDivisor();

	for(i=1;i<=k;i++) {
		for(j=1;j<=n;j++) {
			dp[i][j] = 0;
			if(i==1 || j==1) dp[i][j] = 1;
			else {
				for(m=0;m<divisor[j].size();m++)
					dp[i][j] = (dp[i][j] + dp[i-1][divisor[j][m]])%MOD;
			}
		}
	}

	for(i=1;i<=n;i++) sum = (sum + dp[k][i])%MOD;
	cout<<sum<<endl;
	return 0;
}

void findDivisor()
{
	lli i,j;
	for(i=1;i<MAX;i++) {
		for(j=1;j<=i;j++)
			if(!(i%j)) divisor[i].push_back(j);
	}
}