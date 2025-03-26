#include <cstdio>
#include <vector>
#include <algorithm>

#define MAX 500

using namespace std;

typedef long long int lli;

lli strange[MAX];

bool checkDigit(lli n, int d) ;

int main() 
{
	int t, i, size=0, j;
	lli a, b;
	for(i=0;i<10;i++) strange[i] = i;
	size = 10;
	i = 1;
	while(i<size) {
		for(j=2;j<=18;j++) {
			if(checkDigit(strange[i]*j, j)) strange[size++] = strange[i]*j;
		}
		i++;
	}

	sort(strange, strange+size);

	scanf("%d",&t);
	while(t--) {
		scanf("%lld%lld",&a,&b);
		printf("%d\n", upper_bound(strange, strange+size, b) - lower_bound(strange, strange+size, a));
	}
    return 0;
}

bool checkDigit(lli n, int d) 
{
	if(n<0) return 0;
	int count = 0;
	while(n) {
		count++;
		n/=10;
	}
	return count<=18 && count==d;
}