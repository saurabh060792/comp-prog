#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX 12
#define MAXSET (1<<12)
#define INF (1<<30)

using namespace std;

typedef long long int lli;

int A[MAX][MAX];
lli dp[MAXSET];

int bitcount(int value);
lli bitmask(int size);

int main()
{
	int t,n,i,j,temp;
	scanf("%d",&t);
	while(t--) {
		memset(A,0,sizeof(A));
		memset(dp,-INF,sizeof(dp));
		// scanf("%d",&n);
		n = 11;
		for(i=0;i<n;i++)
			for(j=0;j<n;j++) {
				scanf("%d",&temp);
				if(temp) A[i][j] = temp;
				else A[i][j] = -INF;
			}
		printf("%lld\n",bitmask(n));
	}
	return 0;
}

lli bitmask(int size)
{
	int setbit ,val = 1 << size, i, j;
	dp[0] = 0;
	for(i=1;i<val;i++) {
		dp[i] = -INF;
		setbit = bitcount(i);
		for(j=0;j<size;j++)
			if( ( i & (1<<j) )!=0) {
				dp[i] = max(dp[i ^ (1<<j)] + A[setbit-1][j], dp[i]);
			}
	}
	return dp[val-1];
}

int bitcount(int i)
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

// int bitcount(lli value)
// {
// 	int count =0;
// 	while(value) {
// 		if(value%2==1) count++;
// 		value /= 2;
// 	}
// 	return count;
// }
