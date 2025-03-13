#include <cstdio>
#include <algorithm>
#include <map>
#include <cstring>

#define MAXARRAY 50004
#define MAXTREE 100010

using namespace std;

typedef long long int lli;

lli queryBIT(int idx);
void updateBIT(int idx ,int val);

int bit[MAXTREE], b[MAXARRAY], p[MAXARRAY], seq[MAXARRAY*2];
map<int, int> cc;

int main()
{
	int t,i,j,n,d,index;
	lli ans;
	scanf("%d",&t);
	while(t--) {
		memset(seq, 0, sizeof(seq));
		memset(bit, 0, sizeof(bit));
		cc.clear();
		ans = 0;
		scanf("%d%d",&n,&d);
		seq[0] = d;
		index = 1;
		for(i=0;i<n;i++) {
			scanf("%d",&b[i]);
			seq[index++] = b[i];
			seq[index++] = b[i] + d;
		}
		sort(seq, seq+index);
		cc[seq[0]] = 1;
		for(i=1,j=2;i<index;i++) if(!cc.count(seq[i])) cc[seq[i]] = j++;
		for(i=0;i<n;i++) scanf("%d",&p[i]);
		for(i=0;i<n;i++) {
			ans += p[i]*(queryBIT(MAXTREE-1) - queryBIT(cc[b[i] + d])) + (100-p[i])*(queryBIT(MAXTREE-1) - queryBIT(cc[b[i]]));
			updateBIT(cc[b[i] + d], p[i]);
			updateBIT(cc[b[i]], 100 - p[i]);
		}
		printf("%.4lf\n",((double)ans)/10000.0);
	}
	return 0;
}

lli queryBIT(int idx)
{
	lli sum = 0;
	while(idx > 0) {
		sum += bit[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

void updateBIT(int idx ,int val)
{
	while(idx <= MAXTREE){
		bit[idx] += val;
		idx += (idx & -idx);
	}
}