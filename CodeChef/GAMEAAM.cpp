#include <iostream>
#include <cstdio>
#include <algorithm>

#define MAX 3003

using namespace std;

typedef long long int lli;

int grundy(int a, int b);

int main()
{
	int t,n,a,b,i,x;
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		x = 0;
		for(i=0;i<n;i++) {
			scanf("%d%d",&a,&b);
			x ^= grundy(a,b);
		}
		printf("%s\n",x?"YES":"NO");
	}
	return 0;
}

int grundy(int a, int b)
{
	int g;
	if(a<b) return grundy(b,a);
	if(a%b==0) return (a/b) - 1;
	g = grundy(b, a%b);
	if(!g) return (a/b);
	else {
		if(((a/b)-1) >= g) return (a/b);
		else return (a/b) - 1;
	}
}

/*
Let the pair be (a, b) such that a>=b

1. Case 1:
If a is a multiple of b i.e. a = bq then
grundy(a, b) = (a/b) - 1

2. Case 2:
Else if a = bq + r
then (a, b) can go to
(a-b, b)
(a-2b, b)
.
.
.
(a-(b-1)q, b)
(a-bq, b)

Now grundy(a-(b-1)q, b) = MEX(grundy(a-bq, b)) = 0
similarly grundy(a-(b-2)q, b) = MEX(grundy(a-bq, b), grundy(a-(b-1)q, b)) = 1
and so on.

Now we have to compare q and g, because if q>=g then grundy(a,b) = (a/b) else (a/b)-1

*/