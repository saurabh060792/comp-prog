#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#define MAX 1000001

using namespace std;

typedef long long int lli;

int pointer, x[MAX];
lli sum[MAX], dp[MAX];
vector<lli> M, B;

bool bad(int l1, int l2, int l3);
void add(lli m, lli b);
lli query(lli x);

int main()
{
	int n , a , b , c, i, t;
	scanf("%d",&t);
	while(t--) {
		M.clear();
		B.clear();
		scanf("%d",&n);
		scanf("%d%d%d",&a,&b,&c);

		for(i=1;i<=n;i++){
			scanf("%d",&x[i]);
			sum[i] = sum[i-1] + x[i];
		}

		dp[1] = a*x[1]*x[1] + b*x[1] + c;
		add(-2*a*x[1], dp[1] + a*x[1]*x[1] - b*x[1]);

		for(i=2;i<=n;i++){
			dp[i] = a*sum[i]*sum[i] + b*sum[i] + c;
			dp[i] = max(dp[i], b*sum[i] + a*sum[i]*sum[i] + c + query(sum[i]));
			add(-2*a*sum[i], dp[i] + a*sum[i]*sum[i] - b*sum[i]);
		}
		printf("%lld\n",dp[n]);
	}
	return 0;
}

bool bad(int l1, int l2, int l3)
{
	return (B[l3]-B[l1])*(M[l1]-M[l2])<(B[l2]-B[l1])*(M[l1]-M[l3]);
}

void add(lli m, lli b)
{
	M.push_back(m);
	B.push_back(b);
	while (M.size()>=3&&bad(M.size()-3,M.size()-2,M.size()-1))
	{
			M.erase(M.end()-2);
			B.erase(B.end()-2);
	}
}

lli query(lli x)
{
	if (pointer >=M.size()) pointer=M.size()-1;
	while (pointer < M.size()-1 && M[pointer+1]*x + B[pointer+1] > M[pointer]*x + B[pointer]) pointer++;
	return M[pointer]*x + B[pointer];
}