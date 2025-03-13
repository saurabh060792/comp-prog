#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>

#define MAX 102
#define MAXSET (1<<11)
#define INF (1<<30)

using namespace std;

typedef long long int lli;

lli dp[MAX][MAXSET], cardinality[MAX][MAXSET], digit[MAX];

void findDigit(lli *A, lli n);

int main()
{
	lli i,j,s,x,n,A[MAX],maxSum,maxCardinality;
	while(1) {
		memset(dp, 0, sizeof(dp));
		memset(cardinality, 0, sizeof(cardinality));
		memset(digit, 0, sizeof(digit));
		if(scanf("%lld",&n) == EOF) break;
		for(i=1;i<=n;i++) scanf("%lld",&A[i]);
		findDigit(A, n);

		for(i=1;i<=n;i++)
			for(j=0;j<(1<<10);j++) dp[i][j] = -INF;
	
		for(i=1;i<=n;i++) {
			for(j=0;j<(1<<10);j++) {
				dp[i][j] = dp[i-1][j];
				cardinality[i][j] = cardinality[i-1][j];
			}
			x = (~digit[i]) & ((1<<10)-1);
			for(s=x;;s=(s-1)&x) {
				if(dp[i][s|digit[i]] < dp[i-1][s] + A[i]) {
					dp[i][s|digit[i]] = dp[i-1][s] + A[i];
					cardinality[i][s|digit[i]] = cardinality[i-1][s] + 1;
				}
				else if(dp[i][s|digit[i]] == dp[i-1][s] + A[i]) 
					cardinality[i][s|digit[i]] = max(cardinality[i-1][s]+1, cardinality[i][s|digit[i]]);

				/*
				We have to write these two conditions separately because when we copy in line 33-36 it may happen
				that until i-1th number cardinality is high but sum is low (eg [1 2] 12) so we copy high
				cardinality in cardinality[i][s|digit[i]] (in line 33 - 36)but infact sum is low so we have to
				decrease it value to cardinality[i-1][s](=0) + 1. Hence we cannot write the same statement as in line 44.
				
				But when the sum are same then we take max(eg 1 12 10)
				These example can be tested easily by taking mask of 3 bits only as digits are only 0,1,2. Print the dp
				and cardinality matrix to debug.

				And above is the reason the code below will give worng answer
				if(dp[i][s|digit[i]] <= dp[i-1][s] + A[i]) {
					dp[i][s|digit[i]] = dp[i-1][s] + A[i];
					cardinality[i][s|digit[i]] = max(cardinality[i-1][s]+1, cardinality[i][s|digit[i]]);
				}				
				*/
				if(s==0) break;
			}
		}
		printf("%lld\n",cardinality[n][(1<<10)-1]);
	}
	return 0;
}

void findDigit(lli *A, lli n)
{
	lli i, num;
	for(i=1;i<=n;i++) {
		num = A[i];
		while(num) {
			digit[i] |= (1<<(num%10));
			num /= 10;
		}
	}
}