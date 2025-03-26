#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

#define MAXX 10004
#define MAXY 1003

using namespace std;

int bit[MAXX][MAXY];
int a[MAXX];

int read(int x, int y);
void update(int x , int y , int val);

int main()
{
	int t,n,q,i,x,y,qT,k,low,high,mid;
	scanf("%d",&t);
	while(t--)
	{
		memset(bit, 0, sizeof bit);
		scanf("%d",&n);
		for(i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			update(i, a[i], 1);
		}
		scanf("%d",&q);
		while(q--) {
			scanf("%d",&qT);
			if(qT==0) {
				scanf("%d%d%d",&x,&y,&k);
				low = 1;
				high = MAXY;
				while(low<high) {
					mid = (low+high)/2;
					if(read(y, mid) - read(x-1,mid) >=k ) high = mid;
					else low = mid+1;
				}
				printf("%d\n",high);
			}
			else {
				scanf("%d%d",&x,&k);
				update(x, a[x], -1);
				a[x] = k;
				update(x, a[x], 1);
			}
		}
	}
	return 0;
}

void update(int x , int y , int val)
{
	int y1;
	while (x <= MAXX){
		y1 = y;
		while (y1 <= MAXY){
			bit[x][y1] += val;
			y1 += (y1 & -y1); 
		}
		x += (x & -x); 
	}
}

int read(int x, int y)
{
	int sum = 0, y1;
	while (x > 0){
		y1 = y;
		while(y1 > 0)
		{
			sum += bit[x][y1];
			y1 -= (y1 & -y1);
		}
		x -= (x & -x);
	}
	return sum;
}