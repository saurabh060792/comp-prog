#include <cstdio>
#include <algorithm>

#define MAX 500005

using namespace std;

int main()
{
	int j=0,i,n,a[MAX];
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	sort(a, a+n);
	for(i=0;i<n;i++) if(a[i] >= a[j]*2) j++;
	printf("%d\n",n-min(n/2, j));
	return 0;
}