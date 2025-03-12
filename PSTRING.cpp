#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXX 10004
#define MAXY 1003

using namespace std;

char x[MAXX], y[MAXY], z[MAXY];
int F[MAXY], dp[MAXX][MAXY], nextMatch[MAXY][26];

int computeFailure(char P[], int m);

int main()
{
	int xlen,ylen,i,j,match,ans;
	while(scanf("%s%s", x, y) == 2) {
		xlen = strlen(x);
		ylen = strlen(y);

		// nextMatch[i][j] :
		// consider the string of length i + 1, whose first i characters are prefix of y and the last character is j
		// nextMatch[i][j] denotes max length of suffix of that string which is a prefix of y, that is basicalylen failure function
		// for the last index of the new string
		for(i=0;i<ylen;i++) {
			for(j=0;j<26;j++) {
				z[i] = 'a' + j;
				z[i + 1] = 0;
				nextMatch[i][j] = computeFailure(z, i+1);
			}
			z[i] = y[i];
		}

		memset(dp, 0, sizeof(dp));

		if(x[0] == y[0]) dp[0][1] = 1;
		else dp[0][0] = 1;

		for(i=1;i<xlen;i++) {
			for(j=0;j<ylen;j++) dp[i][j] = dp[i - 1][j];		//donot take the ith character
			for(j=0;j<ylen;j++) {								//take ith character
				if(x[i] == y[j]) {
					if(j != ylen - 1) dp[i][j + 1] = max(dp[i][j + 1], dp[i - 1][j] + 1);
				}
				else {
					match = nextMatch[j][x[i] - 'a'];
					dp[i][match] = max(dp[i][match], dp[i - 1][j] + 1);
				}
			}
		}
		ans = 0;
		for(i=0;i<ylen;i++) ans = max(ans, dp[xlen - 1][i]);
		printf("%d\n", xlen - ans);
	}
    return 0;
}

int computeFailure(char P[], int m)
{
	int i,k=0;
	F[0] = 0;
	for(i=1;i<m;i++) {
		while(k>0 && P[k]!=P[i]) k = F[k-1];
		if(P[k] == P[i]) k++;
		F[i] = k;
	}
	return F[m - 1];
}