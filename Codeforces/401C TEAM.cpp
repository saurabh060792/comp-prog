#include <cstdio>
#include <algorithm>

#define MAX 5000006

using namespace std;

int number[MAX];

int main()
{
	int i,j,n,m;
	scanf("%d%d",&n,&m);
	if(m<n-1 || m>2*(n+1)) {
		printf("-1\n");
		return 0;
	}
	for(i=0;i<MAX;i++) number[i] = -1;
	for(i=2,j=0;j<n;i+=3,j++) number[i] = 0;
	for(i=3,j=0;j<min(n,m);i+=3,j++) number[i] = 1;
	m -= min(m,n);
	if(m) number[0] = 1,m--;
	for(i=1,j=0;j<m;i+=3,j++) number[i] = 1;
	for(i=0;i<MAX;i++) if(number[i] != -1) printf("%d",number[i]);
	printf("\n");
	return 0;
}