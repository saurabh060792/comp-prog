#include <cstdio>
#include <algorithm>
#include <cmath>

#define MAX 100005
#define SQRTMAX 350
#define MAXTREE 100005

using namespace std;

typedef unsigned long long int lli;

int n, sqrtn, a[MAX], freq[SQRTMAX][MAX];
lli bit[MAXTREE], D[SQRTMAX];
pair<int, int> func[MAX];

void calcFreq();
void buildBIT();
lli queryBIT(int idx);
void updateBIT(int idx ,lli val);
void buildSDT();
lli querySDT(int l, int r);
void updateSDT(int bucket, lli newValue);

int main()
{
	int i,q,qT,j,x,y;
	lli p;
	scanf("%d",&n);
	sqrtn = ((int)sqrt(n))+1;
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	for(i=0;i<n;i++) {
		scanf("%d%d",&x, &y);
		func[i].first = x-1;
		func[i].second = y-1;
	}
	calcFreq();
	buildBIT();
	buildSDT();
	scanf("%d",&q);
	for(i=0;i<q;i++) {
		scanf("%d",&qT);
		if(qT == 1) {
			scanf("%d%d",&x,&y);
			p = queryBIT(x) - queryBIT(x-1);
			updateBIT(x, y-p);
			for(j=0;j<sqrtn;j++) updateSDT(j, freq[j][x-1]*(y-p));
		}
		else {
			scanf("%d%d",&x,&y);
			x--,y--;
			printf("%llu\n",querySDT(x, y));
		}
	}
	return 0;
}

void calcFreq()
{
	int i,j;
	for(i=0;i<sqrtn;i++) {
		for(j=0;j<sqrtn && i*sqrtn+j<n;j++) {
			freq[i][func[i*sqrtn+j].first]++;
			freq[i][func[i*sqrtn+j].second + 1]--;
		}
	}
	for(i=0;i<sqrtn;i++) {
		for(j=1;j<n;j++) {
			freq[i][j] += freq[i][j-1]; 
		}
	}
	return;
}

void buildBIT()
{
	int i;
	for(i=0;i<n;i++) updateBIT(i+1, a[i]);
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

void updateBIT(int idx ,lli val)
{
	while(idx <= MAXTREE){
		bit[idx] += val;
		idx += (idx & -idx);
	}
}

void buildSDT()
{
	int i,j;
	lli ans;
	for(i=0;i<sqrtn;i++) {
		ans = 0;
		for(j=0;j<sqrtn && i*sqrtn+j<n;j++) {
			ans +=  queryBIT(func[i*sqrtn+j].second+1) - queryBIT(func[i*sqrtn+j].first);
		}
		D[i] = ans;
	}
	return;
}

lli querySDT(int l, int r)
{
	int i=l;
	lli ans=0;
	while(i%sqrtn != 0 && i<=r) {
		ans += queryBIT(func[i].second+1) - queryBIT(func[i].first);
		i++;
	}
	while(i + sqrtn <= r) {
		ans += D[i/sqrtn];
		i += sqrtn;
	}
	while(i<=r) {
		ans += queryBIT(func[i].second+1) - queryBIT(func[i].first);
		i++;
	}
	return ans;
}

void updateSDT(int bucket, lli newValue)
{
	D[bucket] += newValue;
	return;
}