#include <iostream>
#include <cstdio>
#include <algorithm>

#define MAXK 400
#define MOD 1234567891

using namespace std;

typedef long long int lli;

lli comb[MAXK][MAXK], coeff[MAXK][MAXK+3];

lli mulInverse(lli a, lli b);
void computeCombinatorics();
void findCoefficients();
lli evaluate(lli n, lli k);

int main()
{
    int t;
    lli ans, n, k;
    computeCombinatorics();
    findCoefficients();
    scanf("%d", &t);
    while(t--){
        scanf("%lld %lld", &n, &k);
        ans = ((n+1)*evaluate(n,k))%MOD - evaluate(n, k+1);
        ans = ans<0?ans+MOD:ans;
        printf("%lld\n", ans);
    }
}

void findCoefficients()
{
    int k, i, j;
    lli inv;
    coeff[0][1] = 1;
    for(k=1;k<=322;k++){
        for(i=0;i<=k+1;i++) coeff[k][i] = comb[k+1][i];
        coeff[k][0] = coeff[k][0]>=1?coeff[k][0]-1:coeff[k][0]-1+MOD;
        inv = mulInverse(k+1, MOD);
        for(i=0;i<=k;i++){
            for(j=0;j<=k-1;j++){
                coeff[k][i] = coeff[k][i] - (comb[k+1][j] * coeff[j][i])%MOD;
                coeff[k][i] = coeff[k][i]>=0?coeff[k][i]:coeff[k][i]+MOD;
            }
            coeff[k][i] = (coeff[k][i] * inv)%MOD;
        }
        coeff[k][k+1] = (coeff[k][k+1] * inv)%MOD;
    }
}

lli evaluate(lli n, lli k)
{
    int i;
    lli sum = 0, ni = 1;
    for(i=0; i<=k+1; i++){
        sum = (sum + ni*coeff[k][i])%MOD;
        ni = (ni*n)%MOD;
    }
    return sum;
}

// returns x where (a * x) % b == 1
lli mulInverse(lli a, lli b)
{
    lli b0 = b, t, q, x0 = 0, x1 = 1;
    if(b==1) return 1;
    while(a>1) {
        q = a / b;
        t = b, b = a % b, a = t;
        t = x0, x0 = x1 - q * x0, x1 = t;
    }
    if(x1<0) x1 += b0;
    return x1;
}

void computeCombinatorics()
{
    int i,j;
    for(i=0;i<MAXK;i++) for(j=0;j<MAXK;j++) comb[i][j]=0;
    for(i=0;i<MAXK;i++) comb[i][0]=comb[i][i]=1;
    for(i=0;i<MAXK;i++){
        for(j=1;j<i;j++){
            comb[i][j]=(comb[i-1][j]+comb[i-1][j-1])%MOD;
        }
    }
}
