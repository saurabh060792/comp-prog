#include <cstdio>
#include <iostream>
#include <algorithm>

#define MAX 10004

using namespace std;

int a[MAX];

int main()
{
	int t,n,x,i,d,k;
	bool f;
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		a[0] = 0;
		for(i=1;i<=n;i++) scanf("%d",&a[i]);
		
		x = 0;
		for(i=(n&1)?1:2;i<=n;i+=2) x^=(a[i]-a[i-1]-1);
		
		f= false;
		if(x>0) {
			for(i=(n&1)?1:2;i<=n && (!f);i+=2) {
				d = a[i]-a[i-1]-1;
				k = d-(x^d);
				if(k==0) continue;
				else if(k<0 && i!=1 && a[i-1]+k>a[i-2]){
					printf("Mary wins\nMove %d to %d\n\n",a[i-1], a[i-1]+k);
					f = true;
				}
				else if(k>0 && a[i]-k>a[i-1]){
					printf("Mary wins\nMove %d to %d\n\n",a[i],a[i]-k);
					f = true;
				}
			}
		}
		else printf("Johnny wins\n\n");
	}
	return 0;
}

//http://www.codechef.com/wiki/tutorial-coin-game