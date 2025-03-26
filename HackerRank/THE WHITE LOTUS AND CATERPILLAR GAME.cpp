#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
	int n,m,i,j;
	long long int sum=0;
	scanf("%d %d",&n,&m);
	for(i=1;i<=m;i++)
		for(j=1;j<=m;j++)
		{
			sum+=n-1;
			if (abs(i-j)<=1)
				continue;
			else if (i<j)
				sum+=max(0,m-(i+n-1));
			else
				sum+=max(0,i-n);
		}
	printf("%.10lf\n",((double)sum)/((double)(m*m)));
	return 0;
}

//https://www.hackerrank.com/contests/101sep14/challenges/the-white-lotus-and-caterpillar-game/editorial