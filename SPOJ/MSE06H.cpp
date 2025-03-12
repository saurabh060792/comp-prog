#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>

#define MAXARRAY 1005
#define MAXTREE 1005

using namespace std;

int readBIT(int idx);
void updateBIT(int idx ,int val);

int bit[MAXTREE];
pair<int, int> highway[MAXARRAY*MAXARRAY];

int main()
{
	int i,t,m,n,k,noOfTestCase=1;
	long long int ans;
	scanf("%d",&t);
	while(t--) {
		ans = 0;
		memset(bit, 0, sizeof(bit));
		scanf("%d%d%d",&n,&m,&k);
		for(i=0;i<k;i++) scanf("%d%d",&highway[i].first, &highway[i].second);
		sort(highway, highway+k);
		for(i=0;i<k;i++) {
			ans += readBIT(m - highway[i].second + 1);
			updateBIT(m - highway[i].second + 2, 1);
		}
		printf("Test case %d: %lld\n",noOfTestCase,ans);
		noOfTestCase++;
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