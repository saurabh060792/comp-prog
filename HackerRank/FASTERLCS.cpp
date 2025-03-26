#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

#define MAX 100005
#define MAXLCS 502

using namespace std;

int a[MAX], b[MAX], seq[2*MAX], dp[MAXLCS][MAX], lcs[MAXLCS], invcc[2*MAX];
map<int, int> cc;
vector<int> index[2*MAX];

int main()
{
	int i,j,k,n,m,idx;
	vector<int> :: iterator it;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		seq[i] = a[i];
	}
	for(i=1;i<=m;i++) {
		scanf("%d",&b[i]);
		seq[n+i] = b[i];
	}
	sort(seq+1, seq+n+m+1);

	j = 1;
	cc[seq[1]] = j;
	invcc[j] = seq[1];
	for(i=2;i<=n+m;i++) {
		if(seq[i]!=seq[i-1]) {
			cc[seq[i]] = ++j;
			invcc[j] = seq[i];
		}
	}

	for(i=1;i<=n;i++) a[i] = cc[a[i]];
	for(i=1;i<=m;i++) b[i] = cc[b[i]];
	for(i=1;i<=m;i++) index[b[i]].push_back(i);

	for(i=1;i<=min(n,MAXLCS-2);i++) {
		for(j=i;j<=n;j++) {
			if(j==1) dp[i][j] = index[a[j]].size()>0?index[a[j]][0]:m+1;
			else if(j==i) {
				it = upper_bound(index[a[j]].begin(), index[a[j]].end(), dp[i-1][j-1]);
				idx = it==index[a[j]].end()?m+1:*it;
				dp[i][j] = idx;
			}
			else {
				it = upper_bound(index[a[j]].begin(), index[a[j]].end(), dp[i-1][j-1]);
				idx = it==index[a[j]].end()?m+1:*it;
				dp[i][j] = min(dp[i][j-1], idx);
			}
		}
	}

	for(i=min(n,MAXLCS-2);i>=1;i--) {
		if(dp[i][n]<m) break;
	}
	k = 1;
	j = n;
	while(i>=1) {
		if(dp[i][j] != dp[i][j-1]) {
			lcs[k++] = a[j];
			i--;
		}
		j--;
	}

	for(i=k-1;i>=1;i--) printf("%d ",invcc[lcs[i]]);
	printf("\n");

	return 0;
}
