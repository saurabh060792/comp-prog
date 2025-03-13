#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define MAXARRAY 100005
#define MAXTREE 262150

typedef long long int lli;
typedef struct segmentTree
{
	lli ans, sum, prefix[3], suffix[3];
}segmentTree;

void buildST(int node, int low, int high);
segmentTree queryST(int node, int low, int high, int a, int b);
void updateST(int node, int low, int high, int position, int newValue);

char s[MAXARRAY];
int A[MAXARRAY];
segmentTree S[MAXTREE];

int main()
{
	int i,n,a,b,q,qT;
	scanf("%d%d",&n,&q);
	scanf("%s",s);
	for(i=0;i<n;i++) A[i] = s[i] - '0';
	buildST(0, 0, n-1);
	while(q--) {
		scanf("%d",&qT);
		if(qT == 1) {
			scanf("%d%d",&a,&b);
			updateST(0, 0, n-1, a-1, b);
		}
		else {
			scanf("%d%d",&a,&b);
			printf("%lld\n",queryST(0, 0, n-1, a-1, b-1).ans);
		}
	}
	return 0;
}

void buildST(int node, int low, int high)
{
	int i,mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2;
	if(low == high) {
		S[node].sum = A[low];
		if(A[low]%3) S[node].ans = 0;
		else S[node].ans = 1;
		S[node].prefix[A[low]%3]++;
		S[node].suffix[A[low]%3]++;
		return;
	}
	buildST(lNode,low,mid);
	buildST(rNode,mid+1,high);
	S[node].sum = S[lNode].sum + S[rNode].sum;
	S[node].ans = S[lNode].ans + S[rNode].ans + S[lNode].suffix[0]*S[rNode].prefix[0] + S[lNode].suffix[1]*S[rNode].prefix[2] + S[lNode].suffix[2]*S[rNode].prefix[1];
	for(i=0;i<3;i++) S[node].prefix[i] = S[lNode].prefix[i] + S[rNode].prefix[((i-S[lNode].sum)%3>=0?(i-S[lNode].sum)%3:(i-S[lNode].sum)%3 + 3)];
	for(i=0;i<3;i++) S[node].suffix[i] = S[rNode].suffix[i] + S[lNode].suffix[((i-S[rNode].sum)%3>=0?(i-S[rNode].sum)%3:(i-S[rNode].sum)%3 + 3)];
	return;
}

segmentTree queryST(int node, int low, int high, int a, int b)
{
	segmentTree r1, r2, r;
	int i,mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2;
	if(a<=low && high<=b) return S[node];
	if(b<=mid) return queryST(lNode, low, mid, a, b);
	if(a>mid) return queryST(rNode, mid + 1, high, a, b);
	r1 = queryST(lNode, low, mid, a, b);
	r2 = queryST(rNode, mid + 1, high, a, b);
	r.sum = r1.sum + r2.sum;
	r.ans = r1.ans + r2.ans + r1.suffix[0]*r2.prefix[0] + r1.suffix[1]*r2.prefix[2] + r1.suffix[2]*r2.prefix[1];
	for(i=0;i<3;i++) r.prefix[i] = r1.prefix[i] + r2.prefix[((i-r1.sum)%3>=0?(i-r1.sum)%3:(i-r1.sum)%3 + 3)];
	for(i=0;i<3;i++) r.suffix[i] = r2.suffix[i] + r1.suffix[((i-r2.sum)%3>=0?(i-r2.sum)%3:(i-r2.sum)%3 + 3)];
	return r;
}


void updateST(int node, int low, int high, int position, int newValue)
{
	int i,mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2;
	if(low == high) {
		A[low] = newValue;
		S[node].sum = A[low];
		if(A[low]%3) S[node].ans = 0;
		else S[node].ans = 1;
		memset(S[node].prefix, 0, sizeof(S[node].prefix));
		memset(S[node].suffix, 0, sizeof(S[node].suffix));
		S[node].prefix[A[low]%3]++;
		S[node].suffix[A[low]%3]++;
		return;
	}
	else if(position <= mid) updateST(lNode, low, mid, position, newValue);
	else updateST(rNode, mid+1, high, position, newValue);
	S[node].sum = S[lNode].sum + S[rNode].sum;
	S[node].ans = S[lNode].ans + S[rNode].ans + S[lNode].suffix[0]*S[rNode].prefix[0] + S[lNode].suffix[1]*S[rNode].prefix[2] + S[lNode].suffix[2]*S[rNode].prefix[1];
	for(i=0;i<3;i++) S[node].prefix[i] = S[lNode].prefix[i] + S[rNode].prefix[((i-S[lNode].sum)%3>=0?(i-S[lNode].sum)%3:(i-S[lNode].sum)%3 + 3)];
	for(i=0;i<3;i++) S[node].suffix[i] = S[rNode].suffix[i] + S[lNode].suffix[((i-S[rNode].sum)%3>=0?(i-S[rNode].sum)%3:(i-S[rNode].sum)%3 + 3)];
}