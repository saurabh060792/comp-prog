#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAXARRAY 100000
#define MAXTREE 262150

typedef long long int lli;

void buildST(lli *A, lli *segmentTree, lli node, lli low, lli high);
lli queryST(lli *segmentTree, lli node, lli low, lli high, lli a, lli b);
void updateST(lli *segmentTree, lli node, lli low, lli high, lli position, lli newValue);


int main()
{
	lli *A,i,n,*segmentTree,a,b,q,result;
	char queryType[10];

	A = (lli*)malloc(MAXARRAY*sizeof(lli));
	segmentTree = (lli*)malloc(MAXTREE*sizeof(lli));

	scanf("%lld",&n);
	for(i=0;i<n;i++) scanf("%lld",&A[i]);
	scanf("%lld",&q);
	buildST(A, segmentTree, 0, 0, n-1);
	
	while(q--) {
		scanf("%s",queryType);
		if(!strcmp(queryType,"change")) {
			scanf("%lld%lld",&a,&b);
			a--;
			updateST(segmentTree,0,0,n-1,a,b);
		}
		else if(!strcmp(queryType,"query")) {
			scanf("%lld%lld",&a,&b);
			a--;b--;
			result = queryST(segmentTree,0,0,n-1,a,b);
		}
	}


	return 0;
}

void buildST(lli *A, lli *segmentTree, lli node, lli low, lli high)
{
	lli mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2;
	if(low == high) {
		segmentTree[node] = A[low];
		return;
	}
	buildST(A,segmentTree,lNode,low,mid);
	buildST(A,segmentTree,rNode,mid+1,high);
	segmentTree[node] = segmentTree[lNode] + segmentTree[rNode];
	return;
}

lli queryST(lli *segmentTree, lli node, lli low, lli high, lli a, lli b)
{
	lli mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2,r1,r2;
	if(a>high || b<low) return 0;
	if(a<=low && high<=b) return segmentTree[node];

	r1 = queryST(segmentTree, lNode, low, mid, a, b);
	r2 = queryST(segmentTree, rNode, mid + 1, high, a, b);
	return r1 + r2;
}

void updateST(lli *segmentTree, lli node, lli low, lli high, lli position, lli newValue)
{
	lli mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2;
	if(low == high) {
		segmentTree[node] = newValue;
		return;
	}
	else if(position <= mid) updateST(segmentTree, lNode, low, mid, position, newValue);
	else updateST(segmentTree, rNode, mid+1, high, position, newValue);
	segmentTree[node] = segmentTree[lNode] + segmentTree[rNode];
}