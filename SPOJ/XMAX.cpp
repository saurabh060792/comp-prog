#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	int t,i,j,n;
	vector<long long int> v;
	long long int temp, result = 0;

	scanf("%d",&n);
	for(i=0;i<n;i++) {
			scanf("%lld",&temp);
			v.push_back(temp);
	}
	
	sort(v.rbegin(),v.rend());
	temp = 1;
	while(temp<=v[0]) temp<<=1;
	temp>>=1;
	
	for(t=0;temp>=1;temp>>=1) {
			i=t;
			while( i<n && (v[i]&temp)==0 ) i++;
			if(i>=n) continue;
			swap(v[t],v[i]);
			for(j=0;j<n;++j) {
				if( j!=t && (v[j]&temp)!=0 )
					v[j]=v[j]^v[t];
			}
			t++;
	}
	
	for(i=0;i<n;i++) result=result^v[i];
	printf("%lld\n",result);
	return 0;
}

//http://math.stackexchange.com/questions/48682/maximization-with-xor-operator
/*
 _                                 _   _     _         _   _
| a_(1,1)  a_(1,2) ....... a_(n,1)  | |  x_1  |       |     |
| a_(1,2)  a_(2,2) ....... a_(n,2)  | |  x_2  |       |     |
| a_(1,3)  a_(3,2) ....... a_(n,3)  | |  x_3  |       |     |
|                                   | |       |       |     |
|                                   | |       |   =   | max |
|                                   | |       |       |     |
| a_(1,32)  a_(1,32) ..... a_(n,32) | |  x_n  |       |     |
|_                                 _| |_     _|       |_   _|

x_i = 1 denotes that ith number is included in the formation of max else x_i = 0
that's why we can perform gaussian elimination
*/