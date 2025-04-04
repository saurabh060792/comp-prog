#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX 100005

using namespace std;

typedef long long int lli;

bool done[MAX], dp[MAX];
int a[MAX];

int main()
{
	int n, x, y, A, diff, s, i, j;

	scanf("%d%d%d", &n, &x, &y);
	diff = y - x;
	s = 0;
	for(i=0;i<n;i++){
		scanf("%d", &A);
		A--;
		//only relevent multipliers are considered
		if(A > 0 && A <= diff && !done[A]){
			a[s++] = A;
			done[A] = true;
		}
	}
	
	sort(a, a + s);

	dp[0] = true;
	for(i=0;i<s;i++){
		if(!dp[a[i]]){
			for(j=a[i];j<=diff;j++){
				if(!dp[j] && dp[j-a[i]])
					dp[j] = true;
			}
		}
	}

	if(dp[diff]) printf("POSSIBLE\n");
	else printf("IMPOSSIBLE\n");
	return 0;
}