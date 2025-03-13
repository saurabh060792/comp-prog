#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

#define MAX 500005

typedef long long int lli;

lli a[MAX];

int main()
{
	bool f;
	lli i,n,k,t,chance;
	lli asum, sum;
	cin >> t;
	while(t--){
		asum=0;
		f = true;
		cin >> n >> k;
		for(i=0;i<k;i++) cin >> a[i];
		sort(a, a+k);
		for(i=0;i<k;i++){
			sum = ((a[i]-1)*(a[i]))/2 - asum;
			asum += a[i];
			if(a[i] > sum){
				f = false;
				chance = a[i];
				break;	
			} 
		}
		if(f==false){
			if(chance%2) cout << "Chef" << endl;
			else cout << "Mom" << endl;
		}
		else{
			chance = (n*(n+1))/2 - asum + 1;
			if(chance%2) cout << "Chef" << endl;
			else cout << "Mom" << endl;
		}
	}
	return 0;
}