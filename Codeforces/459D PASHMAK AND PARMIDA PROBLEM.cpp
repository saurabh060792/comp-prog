#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>

#define MAXARRAY 1000006
#define MAXTREE 1000006

using namespace std;

typedef long long int lli;

lli readBIT(lli idx);
void updateBIT(lli idx ,lli val);

lli bit[MAXTREE], a[MAXARRAY], x[MAXARRAY], y[MAXARRAY];
map<lli, lli> c1,c2;


int main()
{
	lli n,i, ans=0;
	cin>>n;
	for(i=0;i<n;i++) cin>>a[i];

	for(i=0;i<n;i++) {
		c1[a[i]]++;
		x[i] = c1[a[i]];
	}
	for(i=n-1;i>=0;i--) {
		c2[a[i]]++;
		y[i] = c2[a[i]];
	}

	for(i=n-1;i>=0;i--) {
		ans += readBIT(x[i]-1);
		updateBIT(y[i], 1);
	}
	cout<<ans<<endl;
	return 0;
}

lli readBIT(lli idx)
{
	lli sum = 0;
	while (idx > 0) {
		sum += bit[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

void updateBIT(lli idx ,lli val)
{
	while (idx <= MAXTREE){
		bit[idx] += val;
		idx += (idx & -idx);
	}
}