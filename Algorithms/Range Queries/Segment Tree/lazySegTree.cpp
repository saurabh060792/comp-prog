#include <iostream>

#define MAXARRAY 100000
#define MAXTREE 262150

using namespace std;

typedef struct segmentTree
{
	int data, lazy;					//lazy denotes that this node is already updated
}segmentTree;						//but its children are not

void buildSegmentTree(int *A, segmentTree *S, int node, int low, int high);
void updateSegmentTree(int *A, segmentTree *S, int node, int low, int high, int a, int b, int value);
int querySegmentTree(int *A, segmentTree *S, int node, int low, int high, int a, int b);


int main()
{
	int n,*A,i;
	segmentTree *S;
	
	A = new int[MAXARRAY];
	S = new segmentTree[MAXTREE];

	cin>>n;
	for(i=0;i<n;i++) cin>>A[i];

	buildSegmentTree(A, S, 0, 0, n-1);

	return 0;
}

void buildSegmentTree(int *A, segmentTree *S, int node, int low, int high)
{
	int lNode = 2*node + 1, rNode = 2*node + 2, mid = (low + high)/2;
	if(low == high) {
		S[node].data = A[low];
		S[node].lazy = -1;
		return;
	}
	buildSegmentTree(A, S, lNode, low, mid);
	buildSegmentTree(A, S, rNode, mid + 1, high);
	S[node].data = S[lNode].data + S[rNode].data;
	S[node].lazy = -1;
	return;
}

void updateSegmentTree(int *A, segmentTree *S, int node, int low, int high, int a, int b, int value)
{
	int lNode = 2*node + 1, rNode = 2*node + 2, mid = (low + high)/2;
	if(S[node].lazy != -1) {						//lazy field is set so we need to update this node and push laziness to its children
		S[lNode].lazy += S[node].lazy;
		S[rNode].lazy += S[node].lazy;
		S[lNode].data += S[node].lazy;
		S[rNode].data += S[node].lazy;
		S[node].lazy = 0;		
	}
	if(a > high || b < low) return;
	else if(a <= low && b >= high) {
		S[node].data += value;
		S[node].lazy += value;
		return;
	}
	updateSegmentTree(A, S, lNode, low, mid, a, b, value);
	updateSegmentTree(A, S, rNode, mid + 1, high, a, b, value);
	S[node].data = S[lNode].data + S[rNode].data;
	return;
}

int querySegmentTree(int *A, segmentTree *S, int node, int low, int high, int a, int b)
{
	int lNode = 2*node + 1, rNode = 2*node + 2, mid = (low + high)/2, r1, r2;
	if(S[node].lazy != -1) {
		S[lNode].lazy += S[node].lazy;
		S[rNode].lazy += S[node].lazy;
		S[lNode].data += S[node].lazy;
		S[rNode].data += S[node].lazy;
		S[node].lazy = 0;
	}
	if(a > high || b < low) return 0;
	else if(a <= low && b >= high) return S[node].data;
	r1 = querySegmentTree(A, S, lNode, low, mid, a, b);
	r2 = querySegmentTree(A, S, rNode, mid + 1, high, a, b);
	return r1 + r2;
}