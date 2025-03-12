#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef struct trie
{
	int lCount,rCount;
	trie *lChild,*rChild;
	trie()
	{
		lCount = rCount = 0;
		lChild = rChild = NULL;
	}
}trie;

void addBit(trie *root, int n);
int query(trie *root, int n, int k);

int main()
{
	int t,i,n,k,temp,temp1,temp2=0;
	long long int total;
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d",&n,&k);
		temp2 = 0;
		trie *root = new trie();
		addBit(root,0);
		total = 0;
		for(i=0;i<n;i++) {
			scanf("%d",&temp);
			temp1 = temp2^temp;
			total += (long long)query(root,temp1,k);
			addBit(root , temp1);
			temp2 = temp1;
		}
		printf("%lld\n",total);
	}
	return 0;
}


void addBit(trie *root,int n)
{
	int i,x;
	for(i=20;i>=0;i--) {
		x= (n>>i) & 1;
		if(x) {
			root->rCount++;
			if(root->rChild == NULL) root->rChild = new trie();
			root = root->rChild;
		}
		else {
			root->lCount++;
			if(root->lChild == NULL) root->lChild = new trie();
			root = root->lChild;
		}
	}
}

int query(trie *root,int n,int k)
{
	if(root == NULL) return 0;
	int i,res = 0;
	bool ch1, ch2;
	for(i=20;i>=0;i--) {
		ch1=(k>>i) & 1;
		ch2=(n>>i) & 1;
		if(ch1) {
			if(ch2) {
				res += root->rCount;
				if(root->lChild == NULL) return res;
				root = root->lChild;
			}
			else {
				res+=root->lCount;
				if(root->rChild == NULL) return res;
				root = root->rChild;
			}
		}
		else
		{
			if(ch2) {
				if(root->rChild == NULL) return res;
				root= root->rChild;
			}
			else {
				if(root->lChild == NULL) return res;
				root= root->lChild;
			}
		}
	}
	return res;
}


//http://threads-iiith.quora.com/Tutorial-on-Trie-and-example-problems?share=1
