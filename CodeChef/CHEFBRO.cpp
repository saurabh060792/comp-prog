#include <cstdio>
#include <cstring>

#define MAX 1003

using namespace std;

int grundy[MAX][MAX];

void solve();

int main() 
{
	int t,m,n,c,temp,i;
	scanf("%d",&t);
	solve();
	while(t--) {
		scanf("%d",&c);
		temp = 0;
		for(i=0;i<c;i++) {
			scanf("%d%d",&n,&m);
			temp ^= grundy[n][m];
		}
		if(temp) printf("MasterChef\n");
		else printf("Football\n");
	}
	return 0;
}

void solve()
{
	int cnt,i,j,mex[10];
	for(i=1;i<=1000;i++) 
		for(j=1;j<=1000;j++) {
			memset(mex, 0, sizeof(mex));
			cnt = 0;
			if(i-1>0) mex[grundy[i-1][j]]=1;
			if(i-2>0) mex[grundy[i-2][j]]=1;
			if(i-1>0 && j-1>0) mex[grundy[i-1][j-1]]=1;
			if(i-2>0 && j-2>0) mex[grundy[i-2][j-2]]=1;
			if(j-1>0) mex[grundy[i][j-1]]=1;
			if(j-2>0) mex[grundy[i][j-2]]=1;
			while(mex[cnt]) cnt++;
			grundy[i][j]=cnt;
		}
}