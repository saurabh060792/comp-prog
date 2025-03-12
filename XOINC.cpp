#include <iostream>

using namespace std;

#define MAX 2005

long long int a[MAX], dp[MAX][MAX];

int main()
{
	int n,i,j;
	cin>>n;
	for(i=0;i<n;i++) cin>>a[n-i];
	for(i=1;i<=n;i++) a[i] += a[i - 1];
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(j<=i) dp[i][j] = max(dp[i][j-1], a[i] - dp[i-j][2*j]);
			else dp[i][j] = dp[i][i];
	cout<<dp[n][2]<<endl;
	return 0;
}

/*
Let ar[i] be the value of the ith coin from the bottom.
Define DP(i,j) = best sum that the next player can get
out of the bottom i coins if they are allowed to take
upto j coins in their next move.

Obviously, DP(N,2) is what we have been asked to find.
Also define sum(i) = the sum of the bottom i coins.
Now, if j=1, the next player has to take exactly one
coin. Then the opposing player is left with i-1 coins
out of which they can make DP(i-1,2) sum in the best
case. Thus the best total sum for the current player is
ar[i]+sum(i-1)-DP(i-1,2) = sum(i)-DP(i-1,2).

Otherwise the next player has to take either j coins in
the next move or some number of coins less than j. In the
first case, the best total sum for the current player is
sum(i)-sum(i-j)+sum(i-j)-DP(i-j,2j) = sum(i)-DP(i-j,2j).
In the second case, the best sum is just DP(i,j-1).

Combining these and looking at the boundary conditions,
we obtain the recurrence relations and base cases:

DP(0,j) = 0
DP(i>0,1) = sum(i)-DP(i-1,2)
DP(i>0,1<j<=i) = max(DP(i,j-1),sum(i)-DP(i-j,2j))
DP(i>0,j>i) = DP(i,i)

*/