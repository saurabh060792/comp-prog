#include <iostream>
#include <algorithm>
#include <cstdio>

#define ROW 1005
#define COL 1005


int up[ROW][COL], left[ROW][COL], right[ROW][COL], c[ROW][COL], d[ROW][COL];

int main()
{
	int n,m,k,q,l,r,i,j;
	scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			up[i][j] = 1;

	for(i=0;i<k;i++) {
		scanf("%d%d",&l,&r);
		up[l][r] = 0;
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

//c[l][r] contains the value of largest width such that its height is r-l+1.
//It is computed by using the recurrence written in line 43 but there might be
//some rectangle which has height > r-l+1 but width more than that c actually
//contain presently. Hence to compute that we have code from line 45 to 50
//which essentially calculates c[i][j] = max(c[i][j], c[i-1][j], c[i][j+1])
//after that we calculate the final ans d[l][r] which can be the rectangle
//which has the height r-l+1 or some rectangle with height < r-l+1 for that
// we have d[l][r] = max(d[l][r], d[i+1][j], d[i][j-1])