#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long int lli;

lli deg[501];

int main()
{
	lli t,n,m,i,j,a,b,sum;
	cin>>t;
	while(t--) 	{
		cin>>n>>m;
		for(i=0;i<n;i++) deg[i] = 0;
		for(i=0;i<m;i++) {
			cin>>a>>b;
			deg[a-1]++;
			deg[b-1]++;
		}
		sort(deg,deg+n,std::greater<int>());
		for(i=0;i<n;i++)
			if(deg[i] <  i)
				break;
		sum = 0;
		for(j=0;j<i;j++) sum+=deg[j];
		for(j=i;j<n;j++) sum-=deg[j];
		sum-=(i)*(i-1);
		cout<<((sum==0)?"YES":"NO")<<endl;
	}
	return 0;
}

//Note that the degree of all the vertices in clique will be
//greater than or equal to that of all the vertices in 
//independent set. So we put all the vertices for which
//deg[i]>=i in clique(deg[i] is degree sequence) and others in
//independent set.Then we just count the edges and see if they are
//consistent with the required condition.