#include <cstdio>
#include <algorithm>

#define MAXARRAY 50004
#define MAXTREE 200005

using namespace std;
 
typedef struct segmentTree {
	int sum, best, left, right;
}segmentTree;
 
int n, a[MAXARRAY];
segmentTree S[MAXTREE];

segmentTree makeNode(int sum, int best, int left, int right);
segmentTree combine(segmentTree l, segmentTree r);
void buildST(int node, int low, int high);
segmentTree queryST(int node, int low, int high, int a, int b);
void updateST(int node, int low, int high, int position);

int main()
{
	int i,q,qt,l,r;
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	buildST(0, 0, n-1);
	scanf("%d",&q);
	while(q--) {
		scanf("%d%d%d",&qt,&l,&r);
		if(qt==0) {
			a[l-1] = r;
			updateST(0, 0, n-1, l-1);
		}
		else printf("%d\n", queryST(0, 0, n-1, l-1, r-1).best);
	}
	return 0;
}

segmentTree makeNode(int sum, int best, int left, int right)
{
	segmentTree tmp;
	tmp.sum = sum;
	tmp.best = best;
	tmp.left = left;
	tmp.right = right;
	return tmp;
}
 
segmentTree combine(segmentTree l, segmentTree r)
{
	int left = l.left, right = r.right, best = max(l.right + r.left, max(l.best, r.best));
	if (l.sum + r.left>left) left =l.sum + r.left;
	if (r.sum + l.right > right) right = r.sum + l.right;
	return makeNode(l.sum+r.sum,best, left, right);
}

void buildST(int node, int low, int high)
{
	int mid = (low+high)/2, lNode = 2*node+1, rNode = 2*node+2;
	if(low == high) {
		S[node] = makeNode(a[low], a[low], a[low], a[low]);
		return;
	}
	buildST(lNode, low, mid);
	buildST(rNode, mid+1, high);
	S[node] = combine(S[lNode], S[rNode]);
}
 
segmentTree queryST(int node, int low, int high, int a, int b)
{
	int mid = (low+high)/2, lNode = 2*node+1, rNode = 2*node+2;
	if(low == a && high == b) return S[node];
	if(b <= mid) return queryST(lNode, low, mid, a, b);
	if(a > mid) return queryST(rNode, mid+1,high,a,b);
	segmentTree l = queryST(lNode, low, mid, a, mid);
	segmentTree r = queryST(rNode, mid+1,high,mid+1,b);
	return combine(l,r);
}
 
void updateST(int node, int low, int high, int position)
{
	int mid = (low+high)/2, lNode = 2*node+1, rNode = 2*node+2;
	if(low == high && low == position) {
		S[node] = makeNode(a[low], a[low], a[low], a[low]);
		return;
	}
	if(position <= mid) updateST(lNode, low, mid, position);
	else updateST(rNode, mid+1, high, position);
	S[node] = combine(S[lNode],S[rNode]);
}