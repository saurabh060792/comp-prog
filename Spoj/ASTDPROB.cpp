#include <iostream>
#include <algorithm>
#include <cstdio>

#define ROW 1005
#define COL 1005


int up[ROW][COL], left[ROW][COL], right[ROW][COL], c[ROW][COL], d[ROW][COL];

int main()
{
	int n,m,q,l,r,i,j,temp;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++) {
			scanf("%d",&temp);
			up[i][j] = temp==1?0:1;
		}

	for(i=2;i<=n;i++)
		for(j=1;j<=m;j++)
			if(up[i][j]) up[i][j] = up[i-1][j] + 1;

	for(i=1;i<=n;i++)				//matrix is 1-indexed so that width = r-l-1 is
		for(j=1;j<=m;j++) {			//true for boundary cases also	
			left[i][j] = j-1;
			while(left[i][j] > 0 && up[i][left[i][j]] >= up[i][j]) left[i][j] = left[i][left[i][j]];
		}

	for(i=1;i<=n;i++)
		for(j=m;j>=1;j--) {
			right[i][j] = j+1;
			while(right[i][j] <= m && up[i][right[i][j]] >= up[i][j]) right[i][j] = right[i][right[i][j]];
		}

	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(up[i][j])
				c[i-up[i][j]+1][i] = std::max(c[i-up[i][j]+1][i], right[i][j] - left[i][j] - 1);

	for(int len = n;len>=2;len--)
		for(i=1;i<=n-len+1;i++) {
			j = i + len - 1;
			c[i+1][j] = std::max(c[i+1][j], c[i][j]);
			c[i][j-1] = std::max(c[i][j-1], c[i][j]);
		}

	// for(int len = n;len>=1;len--)
	// 	for(i=1;i<=n-len+1;i++) {
	// 		j = i + len - 1;
	// 		if(i==1 && j==m) continue;
	// 		else if(i==1 && j<m) c[i][j] = std::max(c[i][j+1], c[i][j]);
	// 		else if(i>1 && j==m) c[i][j] = std::max(c[i-1][j], c[i][j]);
	// 		else {
	// 			c[i][j] = std::max(c[i][j+1], c[i][j]);
	// 			c[i][j] = std::max(c[i-1][j], c[i][j]);
	// 		}
	// 	}

	for(int len = 1;len<=n;len++)
		for(i=1;i<=n-len+1;i++) {
			j = i + len - 1;
			d[i][j] = c[i][j]*len;
			d[i][j] = std::max(d[i+1][j], d[i][j]);
			d[i][j] = std::max(d[i][j-1], d[i][j]);
		}

	scanf("%d",&q);
	for(i=0;i<q;i++) {
		scanf("%d%d",&l,&r);
		printf("%d\n",d[l][r]);
	}
	return 0;
}
