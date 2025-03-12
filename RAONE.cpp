#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>

#define MAX 55
#define MAXSUM 1055

using namespace std;

typedef long long int lli;

lli **dp;
bool **mem;

lli find(lli x);
lli f(int sum, int digit);

int main()
{
	int t,i;
	lli a,b,ans;

	dp = (lli**)malloc(sizeof(lli*)*2*MAXSUM);
	mem = (bool**)malloc(sizeof(lli*)*2*MAXSUM);

	for(i=0;i<2*MAXSUM;i++) {
		dp[i] = (lli*)malloc(sizeof(lli)*MAX);
		mem[i] = (bool*)malloc(sizeof(lli)*MAX);
	}
	dp += MAXSUM;
	mem += MAXSUM;

	scanf("%d",&t);
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
	int d, len, digit, i, j, sum=1;
	lli ans = 0;
	char a[MAX];

	sprintf(a,"%lld",x);
	len = strlen(a);
	digit = len;

	for(i=0;i<len;i++) {
		d = a[i] - '0';
		for(j=0;j<d;j++) {  
			if(digit%2) ans += f(sum+j, digit-1);
			else ans += f(sum-j, digit-1);
		}
		sum += digit%2?d:(-d);
		digit--;
	}
	return ans;
}


lli f(int sum, int digit)
{
	int i;
	lli ans = 0;

	if(digit == 0) return (sum==0);
	if(digit == 1) {
		if(sum<1 && sum>-10) return 1;
		else return 0;
	}
	if(mem[sum][digit]) return dp[sum][digit];
	for(i=0;i<=9;i++) {
		if(digit%2) ans += f(sum + i, digit - 1);
		else ans += f(sum - i, digit - 1);
	}
	dp[sum][digit] = ans;
	mem[sum][digit] = true;
	return ans;
}
