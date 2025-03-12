#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX 10000001

using namespace std;

int a[MAX], b[MAX], c[MAX];

int main()
{
	int t,i,j,n,mx;
	scanf("%d",&t);
	while(t--) {
		mx=1;
		scanf("%d",&n);
		fill(c, c+n, 1);
		for(i=0;i<n;++i) {
			scanf("%d",a+i);
			b[a[i]]=i;
		}
		sort(a,a+n);
		for(i=1;i<n;i++) {
			if(b[a[i-1]]<b[a[i]]) {
				c[i]=c[i-1]+1;
				if(c[i]>mx) mx=c[i];
			}
		}
		printf("%d\n",n-mx);
	}
	return 0;
}