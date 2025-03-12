#include <algorithm>
#include <cstdio>

#define MAX 32768
#define MAXTREE 65536

using namespace std;

char seq[MAX];

//Replace ( and ) with 1 and -1 then by taking cumulative sum
//we note that if the string is balanced no cell is negetive
//and the last index should be zero. So,
//For a string to be balanced its sum and minimum prefix sum == 0
//sum==0 takes care of the string like ((())
//and minimum prefix sum takes care of the sting like )(
typedef struct segmentTree
{
	int sum, minPrefixSum;
}segmentTree;

segmentTree S[MAXTREE];

void buildST(int node, int i, int j);
void updateST(int node, int i, int j, int idx);

int main()
{
	int len, q, i, idx, t = 1;
	while(scanf("%d", &len)==1) {
		scanf("%s", seq);
		buildST(1, 0, len-1);
		printf("Test %d:\n", t++);
		scanf("%d", &q);
		for(i=0; i<q; i++) {
			scanf("%d", &idx);
			if(!idx) {
				if(!S[1].sum && !S[1].minPrefixSum) printf("YES\n");
				else printf("NO\n");
			}
			else updateST(1, 0, len-1, idx-1);
		}
	}
	return 0;
}

void buildST(int node, int i, int j)
{
	int m = (i+j)/2;
	if(i==j) {
		S[node].sum = S[node].minPrefixSum = (seq[i]=='(' ? 1 : -1);
		return;
	}
	buildST(2*node, i, m);
	buildST(2*node+1, m+1, j);
	S[node].sum = S[2*node].sum + S[2*node+1].sum;
	S[node].minPrefixSum = min(S[2*node].minPrefixSum, S[2*node].sum + S[2*node+1].minPrefixSum);
}

void updateST(int node, int i, int j, int idx)
{
	int m = (i+j)/2;
	if(i==j) {
		S[node].sum = S[node].minPrefixSum = -S[node].sum;
		return;
	}
	if(idx<=m) updateST(2*node, i, m, idx);
	else updateST(2*node+1, m+1, j, idx);
	S[node].sum = S[2*node].sum + S[2*node+1].sum;
	S[node].minPrefixSum = min(S[2*node].minPrefixSum, S[2*node].sum + S[2*node+1].minPrefixSum);
}