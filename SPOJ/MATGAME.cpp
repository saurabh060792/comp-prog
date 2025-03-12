#include <cstdio>
#include <algorithm>

#define MAX 51

using namespace std;

int mat[MAX][MAX],grundy[MAX][MAX];

int main()
{
	int ans,t,n,m,i,j;
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d",&n,&m);
		for(i=0;i<n;i++)
			for(j=0;j<m;j++) scanf("%d",&mat[i][j]);
		for(i=0;i<n;i++) {
			for(j=m-1;j>=0;j--) {
				if(j==m-1) grundy[i][j] = mat[i][j];
				else {
					grundy[i][j] = mat[i][j]<=grundy[i][j+1]?mat[i][j]-1:mat[i][j];
				}
			}
		}
		ans = 0;
		for(i=0;i<n;i++) ans ^= grundy[i][0];
		if(ans) printf("FIRST\n");
		else printf("SECOND\n");
	}
	return 0;
}