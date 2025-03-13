#include <cstdio>
#include <algorithm>

#define MAX 100005

using namespace std;

int a[MAX],pos[MAX],dp[MAX],prefixSum[MAX];

int main()
{
	int i,j,n,m,b,d,flag=0,pre=0,sum,l;
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	prefixSum[0] = a[0];
	for(i=1;i<n;i++) prefixSum[i] = prefixSum[i-1] + a[i];
	scanf("%d",&m);
	for(i=0;i<m;i++) {
		scanf("%d %d",&b,&d);
		pos[b-1]=d;
	}
	for(i=0;i<n;i++) {
		if (pos[i]!=0) {
			l = max(pre, i-pos[i]+1);
			sum = l>0?prefixSum[min(l+pos[i]-1, n-1)] - prefixSum[l-1]:prefixSum[min(l+pos[i]-1, n-1)];
			pre = min(l+pos[i],n);
			if(!flag) {
				dp[min(l+pos[i]-1,n-1)] = sum;
				flag = 1;
			}
			else dp[min(l+pos[i]-1,n-1)] = sum + dp[l-1];
			for(j=min(l+pos[i],n);j<min(n,i+pos[i]);j++) {
				sum += a[j] - a[j-pos[i]];
				dp[j] = max(dp[j-1], dp[j-pos[i]] + sum);
			}
		}
		else if(i>0) dp[i] = max(dp[i], dp[i-1]);
	}
	printf("%d\n",dp[n-1]);
	return 0;
}