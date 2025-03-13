#include <cstdio>
#include <algorithm>
#include <cmath>

#define MAX 250005
#define SQRTMAX 501
#define MAXBIT 16
#define INF 65535

using namespace std;

typedef struct trie
{
	int count;
	struct trie *next[2];
}trie;

int n, sqrtn, a[MAX], pending[SQRTMAX];
trie *T[SQRTMAX];

trie* newTrieNode();
void initializeTrie();
void insertTrie(trie *T, int x);
void deleteTrie(trie *T, int x);				//Assuming x is present in trie. If not, it will throw segFault
void updateSDT(int l, int r, int k);
pair<int, int> querySDT(int l, int r);

int main()
{
	int q,qt,i,l,r,k;
	pair<int, int> ans;
	scanf("%d%d",&n,&q);
	sqrtn = (int)sqrt(n) + 1;
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	initializeTrie();

	while(q--) {
		scanf("%d",&qt);
		if(qt == 1)	{
			scanf("%d%d",&l,&r);
			ans = querySDT(l-1, r-1);
			printf("%d %d\n", ans.first, ans.second);
		}
		else {
			scanf("%d%d%d",&l,&r,&k);
			updateSDT(l-1, r-1, k);
		}
	}
	return 0;
}

trie* newTrieNode()
{
	trie *temp = new trie;
	temp->count = 0;
	temp->next[0] = temp->next[1] = NULL;
	return temp;
}

void initializeTrie()
{
	int i,j;
	for(i=0;i<sqrtn;i++) T[i] = newTrieNode();
	for(i=0;i<sqrtn;i++) T[i]->count = 0, T[i]->next[0] = T[i]->next[1] = NULL;
	for(i=0;i<sqrtn;i++) {
		for(j=0;j<sqrtn && i*sqrtn+j < n;j++) {
			insertTrie(T[i], a[i*sqrtn+j]);
		}
	}
}

void insertTrie(trie *T, int x)
{
	int i,bit;
	trie *temp = T;
	for(i=MAXBIT-1;i>=0;i--) {
		temp->count++;
		bit = min(x&(1<<i), 1);
		if(temp->next[bit] == NULL) temp->next[bit] = newTrieNode();
		temp = temp->next[bit];
	}
	temp->count++;
}

void deleteTrie(trie *T, int x)
{
	int i,bit;
	trie *temp = T;
	for(i=MAXBIT-1;i>=0;i--) {
		temp->count--;
		bit = min(x&(1<<i), 1);
		temp = temp->next[bit];
	}
	temp->count--;
}

void updateSDT(int l, int r, int k)
{
	int i=l;
	while(i%sqrtn != 0 && i<=r) {
		deleteTrie(T[i/sqrtn], a[i]);
		insertTrie(T[i/sqrtn], a[i]^k);
		a[i++] ^= k;
	}
	while(i + sqrtn <= r) {
		pending[i/sqrtn] ^= k;
		i += sqrtn;
	}
	while(i<=r) {
		deleteTrie(T[i/sqrtn], a[i]);
		insertTrie(T[i/sqrtn], a[i]^k);
		a[i++] ^= k;
	}
}

pair<int, int> querySDT(int l, int r)
{
	int i=l,j,bit,minimum,count=0,k;
	trie *temp;
	pair<int, int> ans(INF, 0);
	while(i%sqrtn != 0 && i<=r) {
		if((a[i]^pending[i/sqrtn]) < ans.first) {
			ans.first = a[i]^pending[i/sqrtn];
			ans.second = 1;
		}
		else if((a[i]^pending[i/sqrtn]) == ans.first) ans.second++;
		i++;
	}
	while(i + sqrtn <= r) {
		temp = T[i/sqrtn];
		k = pending[i/sqrtn];
		minimum = INF;
		for(j=MAXBIT-1;j>=0;j--) {
			bit = min((1<<j)&k, 1);
			if(temp->next[bit] != NULL && temp->next[bit]->count) {
				if(!bit) minimum -= (1<<j);
				temp = temp->next[bit];
			}
			else {
				if(bit) minimum -= (1<<j);
				temp = temp->next[!bit];
			}
		}
		minimum ^= k;
		count = temp->count;
		if(minimum < ans.first) {
			ans.first = minimum;
			ans.second = count;
		}
		else if(minimum == ans.first) ans.second += count;
		i += sqrtn;
	}
	while(i<=r) {
		if((a[i]^pending[i/sqrtn]) < ans.first) {
			ans.first = a[i]^pending[i/sqrtn];
			ans.second = 1;
		}
		else if((a[i]^pending[i/sqrtn]) == ans.first) ans.second++;
		i++;
	}
	return ans;
}