#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

#define MAXARRAY 100005
#define MAXTREE 262160
#define MAXQUERY 100005
#define INF 1000000000

using namespace std;

typedef long long int lli;

typedef struct query
{
	int idx, l, r;
	lli ans;
}query;

class segmentTree
{
public:
	lli lazy, bestLazy, mx, evermx;
	/*
	mx 		 = maximum among the current values of the segment
	evermx	 = the maximum value ever taken by the variable mx
	lazy 	 = the summation of all the updates i.e. the value to be added to mx
	bestLazy = the maximum prefixed accumulated values in lazy
			   i.e. same as the best value lazy has seen
	*/

	void updateChild(int l, int r);
	
	void setNode(int value);
	void clearNode();
	void updateNode(int l, int r);

	void updateST(int node, int low, int high, int a, int b, int value);
	lli queryST(int node, int low, int high, int a, int b);
};

bool comp1(query a, query b);
bool comp2(query a, query b);

segmentTree S[MAXTREE];
int A[MAXARRAY], p[MAXARRAY];
query qList[MAXQUERY];

int main()
{
	int n,i,q,a,b,curr,*h;
	h = new int[2*MAXARRAY + 10];
	h += MAXARRAY+3;
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%d",&A[i]);
		p[i] = h[A[i]];
		h[A[i]] = i;
	}
	scanf("%d",&q);
	for(i=1;i<=q;i++) {
		scanf("%d%d",&a,&b);
		qList[i].idx = i;
		qList[i].l = a;
		qList[i].r = b;
	}
	sort(qList+1, qList+q+1, comp1);
	curr = 1;
	for(i=1;i<=n;i++) {
		S[1].updateST(1, 1, n, p[i]+1, i, A[i]);
		while(qList[curr].r == i) {
			qList[curr].ans = S[1].queryST(1, 1, n, qList[curr].l, i);
			curr++;
		}
	}
	sort(qList+1, qList+q+1, comp2);
	for(i=1;i<=q;i++) printf("%lld\n",qList[i].ans);
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

void segmentTree::updateNode(int l, int r)
{
	mx = max(S[l].mx + S[l].lazy, S[r].mx + S[r].lazy);
	/*
	best value that the mx can have (among the accumulated updates in lazy
	is the maximum prefix of the update which is bestlazy) is l.mx +
	l.bestLazy(because mx is the present max and bestLazy is the best prefix
	among all the updates) that's why here we are taking max between l.evermx
	and l.mx+l.bestLazy
	*/
	evermx = max(max(S[l].evermx, S[l].mx + S[l].bestLazy), max(S[r].evermx, S[r].mx + S[r].bestLazy));
}

void segmentTree::clearNode()
{
	lazy = 0;
	bestLazy = -INF;
}

void segmentTree::setNode(int value)
{
	lazy += value;
	bestLazy = max(bestLazy, lazy);
}

void segmentTree::updateChild(int l, int r)
{
	/*
	When we discharge lazy and bestLazy from parent node, the
	l.bestLazy will be max of prefix of l.lazy ( that is the
	old value ) or l.lazy ( whole update on this node ) + 
	bestLazy ( best prefix of the parent node which was not
	propagated below before)
	*/
	S[l].bestLazy = max(S[l].bestLazy, bestLazy + S[l].lazy);
	S[l].lazy += lazy;
	S[r].bestLazy = max(S[r].bestLazy, bestLazy + S[r].lazy);
	S[r].lazy += lazy;
}

void segmentTree::updateST(int node, int low, int high, int a, int b, int value)
{
	if(a <= low && high <= b) S[node].setNode(value);
	else {
		int mid = (low + high)/2;
		S[node].updateChild(2*node, 2*node+1);
		S[node].clearNode();
		if(a <= mid) updateST(2*node, low, mid, a, b, value);
		if(mid < b) updateST(2*node+1, mid+1, high, a, b, value);
		S[node].updateNode(2*node, 2*node+1);
	}
}

lli segmentTree::queryST(int node, int low, int high, int a, int b)
{
	if(a <= low && high <= b) return max(S[node].evermx, S[node].mx + S[node].bestLazy);
	else {
		int mid = (low + high)/2;
		S[node].updateChild(2*node, 2*node+1);
		S[node].clearNode();
		S[node].updateNode(2*node, 2*node+1);
		return max((a <= mid ? queryST(2*node, low, mid, a, b) : -INF), (mid < b ? queryST(2*node+1, mid+1, high, a, b) : -INF));
	}
}