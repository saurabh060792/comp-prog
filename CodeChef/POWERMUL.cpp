#include <cstdio>
#include <algorithm>
#include <cstring>
#include <functional>

#define MAXNUM 100005
#define MAXFACTOR 30
#define MAXQUERY 100005
#define MAXTREE 400000

using namespace std;

typedef long long int lli;

typedef struct query
{
	int idx, r;
	lli ans;
}query;

typedef struct segmentTree
{
	lli value, power;
}segmentTree;


int m, i, prime[MAXNUM], primeFactor[MAXNUM][MAXFACTOR], factorIndex[MAXNUM], primePower[MAXNUM][MAXFACTOR], invPrimeIndex[MAXNUM], pi[MAXNUM];
query qList[MAXQUERY];
segmentTree S[MAXTREE];

int sieve();
lli powMod(lli a, lli b, int mod);
void buildST(lli node, lli low, lli high);
void updateST(lli node, lli low, lli high, lli p, lli incPower);
bool comp1 (query a, query b);
bool comp2 (query a, query b);

int main()
{
	int j,t,n,q, primeCount, counter;
	primeCount = sieve();
	scanf("%d",&t);
	while(t--) {
		counter = 0;
		scanf("%d%d%d",&n,&m,&q);
		for(i=0;i<q;i++) {
			scanf("%d",&qList[i].r);
			if(qList[i].r > n/2) qList[i].r = n - qList[i].r;
			qList[i].idx = i;
		}

		sort(qList, qList+q, comp1);

		buildST(0, 0, pi[n]-1);
		for(i=1;i<n;i++) {
			for(j=0;j<factorIndex[n-i+1];j++)
				updateST(0, 0, pi[n]-1, primeFactor[n-i+1][j], (n-i+1)*primePower[n-i+1][j]);
			for(j=0;j<factorIndex[i];j++)
				updateST(0, 0, pi[n]-1, primeFactor[i][j], (-i)*primePower[i][j]);
			while(counter<q && qList[counter].r == i) {
				qList[counter].ans = S[0].value;
				counter++;
			}
			if(counter>=q) break;
		}
		sort(qList, qList+q, comp2);
		for(i=0;i<q;i++) printf("%lld\n",qList[i].ans);
	}
	return 0;
}

bool comp1(query a, query b)
{
	return a.r<b.r;
}

bool comp2(query a, query b)
{
	return a.idx<b.idx;
}

int sieve()
{
	int i,j,k,count,primeCount=0;
	primeFactor[1][0] = 1;
	for(i=2;i<MAXNUM;i++) prime[i] = 1;
	for(i=2;i<MAXNUM;i++) {
		if(prime[i]) {
			invPrimeIndex[i] = primeCount;
			primeCount++;
			for(j=i;j<MAXNUM;j+=i) {
				primeFactor[j][factorIndex[j]] = i;
				prime[j] = 0;
				k = j;
				count = 0;
				while(k%i==0) {
					count++;
					k /= i;
				}
				primePower[j][factorIndex[j]] = count;
				factorIndex[j]++;
			}
			prime[i] = 1;
		}
		pi[i] = primeCount;
	}
	return primeCount;
}

void buildST(lli node, lli low, lli high)
{
	lli mid,leftNode,rightNode;
	mid = (low+high)/2;
	leftNode = 2*node + 1;
	rightNode = 2*node + 2;

	if(low == high) {
		S[node].power = 0;
		S[node].value = 1%m;
		return;
	}
	buildST(leftNode,low,mid);
	buildST(rightNode,mid+1,high);
	S[node].value = 1%m;
	return;
}

void updateST(lli node, lli low, lli high, lli p, lli incPower)
{
	lli mid,leftNode,rightNode;
	mid = (low+high)/2;
	leftNode = 2*node + 1;
	rightNode = 2*node + 2;

	if(low == high) {
		S[node].power += incPower;
		S[node].value = powMod(p, S[node].power, m);
		return;
	}
	else if(invPrimeIndex[p] <= mid) updateST(leftNode, low, mid, p, incPower);
	else updateST(rightNode, mid+1, high, p, incPower);
	S[node].value = (S[leftNode].value * S[rightNode].value)%m;
}

lli powMod(lli a, lli b, int mod)
{
	lli temp;
	if(b==0) return 1%mod;
	if(b%2) {
		return (a*powMod(a, b-1, mod))%mod;
	}
	else {
		temp = powMod(a, b/2, mod);
		return (temp*temp)%mod;
	}
}