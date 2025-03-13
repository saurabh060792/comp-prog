#include <cstdio>
#include <algorithm>

#define MAX 5003

using namespace std;

int main()
{
	int n,m,i,x,y;
	scanf("%d%d",&n,&m);
	if(n>m) n ^= m ^= n ^= m;
	printf("%d\n",n+1);
	for(i=0,x=0,y=n;i<=n;i++,x++,y--) printf("%d %d\n",x,y);
	return 0;
}