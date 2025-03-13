#include <cstdio>
#include <algorithm>
#include <string>
#include <set>
#include <iostream>
#include <cstring>

#define MAX 33

using namespace std;

int dp[MAX][MAX];

int main()
{
	int t,n,l,i,j,k1,k2;
	string S,T;
	set<string> dictionary;
	set<int> mex;
	scanf("%d",&t);
	while(t--) {
		memset(dp, 0, sizeof(dp));
		dictionary.clear();
		cin>>S;
		scanf("%d",&n);
		for(i=0;i<n;i++) {
			cin>>T;
			dictionary.insert(T);
		}
		for(i=0;i<S.length();i++) {
			if(dictionary.find(S.substr(i,1)) == dictionary.end()) dp[i][i] = 0;
			else dp[i][i] = 1;
		}

		// cout<<S<<endl;
		// for(set<string>::iterator it = dictionary.begin();it != dictionary.end();it++)
		// 	cout<<*it<<endl;

		for(l=2;l<=S.length();l++) {
			for(i=0;i<=S.length()-l;i++) {
				j = i+l-1;
				mex.clear();
				for(k1=i;k1<=j;k1++) {
					for(k2=k1;k2<=j;k2++) {
						if(dictionary.find(S.substr(k1,k2-k1+1)) != dictionary.end()) {
							if(k1-1<i && k2+1>j) mex.insert(0);
							else if(k1-1<i) mex.insert(dp[k2+1][j]);
							else if(k2+1>j) mex.insert(dp[i][k1-1]);
							else mex.insert(dp[i][k1-1]^dp[k2+1][j]);
						}
					}
				}
				while(mex.count(dp[i][j]))
					dp[i][j]++;
			}
		}

		// for(i=0;i<S.length();i++){
		// 	for(j=0;j<S.length();j++) printf("%d ",dp[i][j]);
		// 	printf("\n");
		// }

		printf("%s\n",dp[0][S.length()-1]?"Teddy":"Tracy");
	}
	return 0;
}