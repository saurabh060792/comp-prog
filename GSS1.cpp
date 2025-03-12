#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define MAXARRAY 100000
#define MAXTREE 262150
#define INF 1000000000

using namespace std;

typedef struct segmentTree
{
	int lSum, rSum, maxSum, sum;
}segmentTree;

void buildSegmentTree(int *A, int currentNode, int low, int high);
segmentTree querySegmentTree(int currentNode, int low, int high, int a, int b);

segmentTree S[MAXTREE];
int A[MAXARRAY];

int main()
{
	int i,n,a,b,q;
	segmentTree result;
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%lld",&A[i]);
	scanf("%lld",&q);
	buildSegmentTree(A, 0, 0, n-1);	
	while(q--) {
		scanf("%d%d",&a,&b);
		a--;b--;
		result = querySegmentTree(0,0,n-1,a,b);
		printf("%d\n",result.maxSum);
	}
	return 0;
}

void buildSegmentTree(int *A, int currentNode, int low, int high)
{
	int mid = (low+high)/2,leftNode,rightNode;
	mid = (low+high)/2;
	leftNode = 2*currentNode + 1;
	rightNode = 2*currentNode + 2;

	if(low == high) {
		S[currentNode].sum = A[low];
		S[currentNode].maxSum = A[low];
		S[currentNode].rSum = A[low];
		S[currentNode].lSum = A[low];
		return;
	}
	buildSegmentTree(A,leftNode,low,mid);
	buildSegmentTree(A,rightNode,mid+1,high);
	S[currentNode].sum = S[leftNode].sum + S[rightNode].sum;
	S[currentNode].lSum = max(S[leftNode].lSum, S[leftNode].sum+S[rightNode].lSum);
	S[currentNode].rSum = max(S[rightNode].rSum, S[rightNode].sum+S[leftNode].rSum);
	S[currentNode].maxSum = max(max(S[leftNode].maxSum, S[rightNode].maxSum), S[leftNode].rSum+S[rightNode].lSum);
	return;
}

segmentTree querySegmentTree(int currentNode, int low, int high, int a, int b)
{
	int mid = (low+high)/2,leftNode,rightNode;
	segmentTree r1, r2, r;
	mid = (low+high)/2;
	leftNode = 2*currentNode + 1;
	rightNode = 2*currentNode + 2;

	if(a>high || b<low) {
		r.sum = 0;
		r.lSum = r.rSum = r.maxSum = -INF;
		return r;
	}
	if(a<=low && high<=b) {
		return S[currentNode];
	}

	r1 = querySegmentTree(leftNode, low, mid, a, b);
	r2 = querySegmentTree(rightNode, mid + 1, high, a, b);

	r.sum = r1.sum + r2.sum;
	r.lSum = max(r1.lSum, r1.sum+r2.lSum);
	r.rSum = max(r2.rSum, r2.sum+r1.rSum);
	r.maxSum = max(max(r1.maxSum, r2.maxSum), r1.rSum+r2.lSum);
	return r;
}
