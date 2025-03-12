#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX 100005

using namespace std;

int Z[MAX];
char s[MAX];

void zAlgorithm(char *S);

int main()
{
	int i,t;
	long long int sum;
	scanf("%d",&t);
	while(t--) {
		scanf("%s",s);
		zAlgorithm(s);
		sum = 0;
		for(i=0;i<strlen(s);i++) sum += i+Z[i]; 
		printf("%lld\n",sum);
	}
	return 0;
}

void zAlgorithm(char *S)
{
	int l = 0, r = 0, i, k, n = strlen(S);
	for (i=1;i<n;i++) {
		if(i > r) {
			l = r = i;
			while(r < n && S[r-l] == S[r]) r++;
			Z[i] = r-l;
			r--;
		}
		else {
			k = i-l;
			if (Z[k] < r-i+1) Z[i] = Z[k];
			else {
				l = i;
				while(r < n && S[r-l] == S[r]) r++;
				Z[i] = r-l; r--;
			}
		}
	}
	Z[0] = n;
}