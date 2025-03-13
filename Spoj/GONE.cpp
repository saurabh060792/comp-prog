#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>

#define MAX 55
#define MAXSUM 1055

using namespace std;

typedef long long int lli;

lli dp[MAXSUM][MAX];
lli prime[26] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101};
bool mem[MAXSUM][MAX];

lli find(lli x);
lli f(lli sum, lli digit);

int main()
{
	lli t,a,b,ans;

	scanf("%lld",&t);
	while(t--) {
		scanf("%lld%lld",&a,&b);
		ans = find(b+1)-find(a);
		printf("%lld\n",ans);
	}
	return 0;
}

// count the number which satisfy certain property
lli find(lli x)
{
	lli d, len, digit, i, j, k, sum, ans=0;
	char a[MAX];

	sprintf(a,"%lld",x);
	len = strlen(a);

	for(k=0;k<26;k++) {
		sum = prime[k];
		digit = len;
		for(i=0;i<len;i++) {
			d = a[i] - '0';
			for(j=0;j<d;j++) {
				if(sum-j>=0) ans += f(sum-j, digit-1);
			}
			sum -= d;
			digit--;
		}
	}
	return ans;
}


lli f(lli sum, lli digit)
{
	lli ans = 0,i;
	if(sum<0) return 0;
	if(digit == 0) return (sum==0);
	if(mem[sum][digit]) return dp[sum][digit];
	for(i=0;i<=9;i++) {
		ans += f(sum-i, digit-1);
	}
	dp[sum][digit] = ans;
	mem[sum][digit] = true;
	return ans;
}
