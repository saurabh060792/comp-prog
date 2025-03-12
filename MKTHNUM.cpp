#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX 100005

typedef struct node
{
	int count;
	node *left, *right;
	node(int count, node *left, node *right): count(count), left(left), right(right) {}
}node;

int a[MAX], seq[MAX], invcc[MAX];
node *root[MAX], *zero = new node(0, NULL, NULL);
map<int, int> cc;

int query(node *a, node *b, int left, int right, int k);
node* insert(node *curr, int left, int right, int val);

int main()
{
	int n,i,m,index=0,l,r,k,ans;
	scanf("%d%d", &n, &m);
	for(i=0;i<n;i++) {
		scanf("%d", &a[i]);
		seq[i] = a[i];
	}
	//coordinate compression
	sort(seq, seq+n);
	cc[seq[0]] = 0;
	invcc[0] = seq[0];
	for(i=1;i<n;i++) 
		if(seq[i] != seq[i-1]) {
			cc[seq[i]] = ++index;
			invcc[index] = seq[i];
		}
	
	zero->left = zero->right = zero;
	for(i=0;i<n;i++) root[i] = insert(i == 0 ? zero : root[i-1], 0, index, cc[a[i]]);
	while(m--) {
		scanf("%d%d%d",&l,&r,&k);
		ans = query(root[r-1], (l-1==0?zero:root[l-2]), 0, index, k);
		printf("%d\n", invcc[ans]);
	}
}

int query(node *a, node *b, int left, int right, int k)
{
	if(left==right) return left;
	int mid = (left+right)/2, count = a->left->count - b->left->count;
	if(count >= k) return query(a->left, b->left, left, mid, k);
	return query(a->right, b->right, mid+1, right, k-count);
}

node* insert(node *curr, int left, int right, int val)
{
	int mid = (left+right)/2;
	if(left <= val && val <= right) {
		if(left==right) return new node(curr->count+1, NULL, NULL);
		return new node(curr->count+1, insert(curr->left, left, mid, val), insert(curr->right, mid+1, right, val));
	}
	return curr;
}


/*
Visualize a base array of size n on which segment tree is build (i.e. the leaf are nothing but some array positon in base array).
Initially the base array is all zeros (because of coordination compression) because the first element is already inserted(which is zero).
Now as the elements are entered the old segment tree is retained and the node which are supposed to be updated are duplicated, so as
the base array(note that there is no actual base array just a visual representation).
The count at the root[i] stores the frequency of a[i] (coordinate compressed value) in the base array ba[0..n], root[i]->left stores
the frequency of a[i] in base array ba[0..n/2] and root[i]->right stores the frequency of a[i] in base array ba[n/2+1..n] and so on.

So in insert when we take a left turn in perfect binary segment tree we dont change the count of right child because the frequency is
not increasing in the right half but it is increased in the left half so we duplicate and put the incremented count in new left node.
Same thing happens while inserting in the right child. Also note that the path traversed while inserting any number is such that the
new value is always entered in sorted order. 

After inserting all the a[i]'s we have effectively build all the prefix segment trees such that root[i][L..R segment] segment of
segement tree root[i] stores the count of element L<=x<=R in base array corresponding to that prefix(upto i'th index). 
*/