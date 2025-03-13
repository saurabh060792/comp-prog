#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
	int t,i,j,mat[510][510],r,c; 			// mat[i][j] stores the minimum health that is
	scanf("%d",&t);							//requried starting from i,j to R,C			
	while(t--) {
		scanf("%d%d",&r,&c);
		for(i=0;i<r;i++) mat[i][0] = 0;
		for(j=0;j<c;j++) mat[0][j] = 0;
		for(i=1;i<=r;i++)
			for(j=1;j<=c;j++)
				scanf("%d",&mat[i][j]);

		mat[r][c] = 1;
		for(i=r-1;i>0;i--) {
			mat[i][c] = mat[i+1][c] - mat[i][c];
			if(mat[i][c] < 1) mat[i][c] = 1;
		}
		for(j=c-1;j>0;j--) {
			mat[r][j] = mat[r][j+1] - mat[r][j];
			if(mat[r][j] < 1) mat[r][j] = 1;
		}
		for(i=r-1;i>0;i--)
			for(j=c-1;j>0;j--) {
				if(mat[i+1][j] < mat[i][j+1]) mat[i][j] = mat[i+1][j] - mat[i][j];
				else mat[i][j] = mat[i][j+1] - mat[i][j];
				if(mat[i][j] < 1) mat[i][j] = 1;
			}
		printf("%d\n",mat[1][1]);
	}
	return 0;
}