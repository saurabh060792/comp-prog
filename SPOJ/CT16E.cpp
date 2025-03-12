#include <cstdio>
#include <algorithm>

#define MAX 20
#define MAXSET (1<<20)

using namespace std;

double dp[MAXSET][MAX], p[MAX][MAX];

int bitcount(int i);

int main()
{
	int n,i,j,s,size;
	double sum;
	scanf("%d",&n);
	for(i=0;i<n;i++) for(j=0;j<n;j++) scanf("%lf",&p[i][j]);
	for(i=0;i<n;i++) dp[1<<i][i] = 1.0;
	for(i=0;i<n;i++) for(j=0;j<n;j++) if(i!=j) dp[(1<<i)^(1<<j)][i] = p[i][j];
	for(s=1;s<(1<<n);s++) {
		size = bitcount(s);
		if(size>2) {
			for(j=0;j<n;j++) {
				sum = 0;
				if(s&(1<<j)) {
					for(i=0;i<n;i++) if(s&(1<<i)) sum += p[i][j];
					for(i=0;i<n;i++) if(s&(1<<i)) dp[s][i] += sum*dp[s^(1<<j)][i];
				}
			}
			for(i=0;i<n;i++) dp[s][i] /= (size*(size-1))/2.0; 
		}
	}
	for(i=0;i<n;i++) printf("%.6lf ",dp[(1<<n)-1][i]);
	printf("\n");
	return 0;
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