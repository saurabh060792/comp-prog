#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX 2003
#define MOD 1000000007

using namespace std;

typedef long long int lli;

lli dp[MAX][MAX], h, a[MAX];

lli solve(lli i, lli j);

int main()
{
    lli i,n;
    scanf("%lld%lld",&n,&h);
    for(i=1;i<=n;i++) {
        scanf("%lld",&a[i]);
    }
    memset(dp, -1, sizeof(dp));
    dp[1][0] = (a[1]==h||a[1]+1==h?1:0);
    dp[1][1] = (a[1]+1==h?1:0);
    printf("%lld\n",solve(n,0));
}

lli solve(lli i, lli j)
{
    if(j<0) return 0;
    else if(dp[i][j] != -1) return dp[i][j];
    else if(a[i]+j == h) return dp[i][j] = (solve(i-1, j-1) + solve(i-1, j))%MOD;
    else if(a[i]+j+1 == h) return dp[i][j] = (solve(i-1, j) + (solve(i-1, j)*j)%MOD + (solve(i-1, j+1)*(j+1))%MOD)%MOD;
    else return 0;
}