#include <cstdio>
#include <algorithm>

using namespace std;

int hash[1000005];

int main()
{
	int n,k,i,l,r;
	scanf("%d%d",&n,&k);
	for(i=0;i<k;i++) {
		scanf("%d%d",&l,&r);
		hash[l]++;
		hash[r+1]--;
	}
	for(i=2;i<n;i++) hash[i] += hash[i-1];
	sort(hash, hash+n+1);
	printf("%d\n",hash[(n/2) + 1]); 
	return 0;
}

// 7 4

// 5 5

// 2 4

// 4 6

// 3 5

// 0 1 2 3 3 1 0
// 0 0 1 1 2 3 3		Note that this is equal to hash after line 18

// 0 1 1 1 0 -2 -1
// 0 1 2 3 3 1 0