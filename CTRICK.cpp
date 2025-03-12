#include <cstdio>
#include <iostream>
#include <algorithm>

#define MAX 20004
#define MAXTREE 100005

using namespace std;

int readBIT(int idx);
void updateBIT(int idx ,int val);

int bit[MAXTREE], A[MAX];

int main()
{
	int t,n,i,j,rot,index,temp1,temp2,high,low,mid,moveBack;
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		bit[0] = 0;
		for(i=1;i<=n;i++) updateBIT(i, 1);
		rot = 0;
		for(i=1;i<=n;i++) {
			temp1 = readBIT(n);
			temp2 = readBIT(rot);
			if( (temp1 - temp2) > i ) {
				moveBack = i;
				low = rot+1;
				high = n;
				while(high - low >= 1) {
					mid = (low + high)/2;
					if(moveBack < readBIT(mid) - readBIT(low-1)) high = mid;
					else moveBack -= (readBIT(mid) - readBIT(low-1)), low = mid + 1 ;
				}
				rot = low;
				A[rot] = i;
			}
			else {
				moveBack = (i - temp1 + temp2) % temp1;
				low = 1;
				high = n;
				while(high - low >= 1) {
					mid = (low + high)/2;
					if(moveBack < readBIT(mid) - readBIT(low-1)) high = mid;
					else moveBack -= (readBIT(mid) - readBIT(low-1)), low = mid + 1 ;
				}
				rot = low;
				A[rot] = i;
			}
			updateBIT(rot, -1);
		}
		for(i=1;i<=n;i++) printf("%d ",A[i]);
		printf("\n");
	}
	return 0;
}

int readBIT(int idx)
{
	int sum = 0;
	while (idx > 0) {
		sum += bit[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

void updateBIT(int idx ,int val)
{
	while (idx <= MAXTREE){
		bit[idx] += val;
		idx += (idx & -idx);
	}
}