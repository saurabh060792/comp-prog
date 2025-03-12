#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>

#define MAXARRAY 100000
#define MAXTREE 262150

using namespace std;

typedef struct segmentTree
{
	pair<int, int> left, right, ans;
}segmentTree;

void buildSegmentTree(int *A, segmentTree *S, int currentNode, int low, int high);
pair<int, int> querySegmentTree(segmentTree *S, int currentNode, int low, int high, int a, int b);
pair<int, int> findMax(pair<int, int> a, pair<int, int> b, pair<int, int> c);

int main()
{
	int *A,i,n,a,b,q;
	pair<int, int> result;
	segmentTree *S;
	A = (int*)malloc(MAXARRAY*sizeof(int));
	S = (segmentTree*)malloc(MAXTREE*sizeof(segmentTree));

	while(true) {
		scanf("%d",&n);
		if(n==0) return 0;
		scanf("%d",&q);
		for(i=0;i<n;i++) scanf("%d",&A[i]);
		buildSegmentTree(A, S, 0, 0, n-1);
		
		// printf("\n");
		// for(i=0;i<16;i++) printf("%d %d\n",S[i].ans.first, S[i].ans.second);

		while(q--) {
			scanf("%d%d",&a,&b);
			a--;b--;
			result = querySegmentTree(S,0,0,n-1,a,b);
			printf("%d\n",result.second);
		}
	}
	return 0;
}

void buildSegmentTree(int *A, segmentTree *S, int currentNode, int low, int high)
{
	int mid = (low+high)/2,leftNode,rightNode;
	mid = (low+high)/2;
	leftNode = 2*currentNode + 1;
	rightNode = 2*currentNode + 2;

	if(low == high) {
		S[currentNode].left = make_pair(A[low], 1);
		S[currentNode].right = make_pair(A[low], 1);
		S[currentNode].ans = make_pair(A[low], 1);
		return;
	}
	buildSegmentTree(A,S,leftNode,low,mid);
	buildSegmentTree(A,S,rightNode,mid+1,high);

	S[currentNode].left = S[leftNode].left;
	S[currentNode].right = S[rightNode].right;
	if(S[leftNode].right.first == S[rightNode].left.first) {
		S[currentNode].ans = findMax(S[leftNode].ans, S[rightNode].ans, make_pair(S[leftNode].right.first, S[leftNode].right.second + S[rightNode].left.second));
		if(S[leftNode].left.first == S[leftNode].right.first) S[currentNode].left = make_pair(S[leftNode].left.first, S[leftNode].left.second + S[rightNode].left.second);
		if(S[rightNode].right.first == S[rightNode].left.first) S[currentNode].right = make_pair(S[rightNode].right.first, S[rightNode].left.second + S[leftNode].right.second);
		// printf("%d %d\n",S[currentNode].ans.first, S[currentNode].ans.second);
	}
	else {
		S[currentNode].ans = S[leftNode].ans.second > S[rightNode].ans.second ? S[leftNode].ans : S[rightNode].ans;
	}
	return;
}

pair<int, int> querySegmentTree(segmentTree *S, int currentNode, int low, int high, int a, int b)
{
	pair<int, int> r1, r2, r;
	int mid = (low+high)/2,leftNode,rightNode;
	mid = (low+high)/2;
	leftNode = 2*currentNode + 1;
	rightNode = 2*currentNode + 2;

	if(a>high || b<low) return make_pair(-1,-1);
	if(a<=low && high<=b) return S[currentNode].ans;

	r1 = querySegmentTree(S, leftNode, low, mid, a, b);
	r2 = querySegmentTree(S, rightNode, mid + 1, high, a, b);
	
	if(S[leftNode].right.first == S[rightNode].left.first) {
		r = findMax(r1, r2, make_pair(r1.first, (mid - a + 1 > S[leftNode].right.second ? S[leftNode].right.second : mid - a + 1) + (b - mid > S[rightNode].left.second ? S[rightNode].left.second : b - mid)));
	}
	else {
		r = r1.second > r2.second ? r1 : r2;
	}
	return r;
}

pair<int, int> findMax(pair<int, int> a, pair<int, int> b, pair<int, int> c)
{
	pair<int, int> ans;
	ans = a.second > b.second ? (a.second > c.second ? a : c) : (b.second > c.second ? b : c);
	return ans;
}