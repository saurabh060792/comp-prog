#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

#define MAX 100005

using namespace std;

int main()
{
	long long int n,k,temp,i,j,limit,m,level;
	scanf("%I64d%I64d",&n,&k);
	limit = k;
	vector<vector<long long int> > treeLevel(n),graph(n);
	for(i=0;i<n;i++) {
		scanf("%I64d",&temp);
		treeLevel[temp].push_back(i);
	}

	if(treeLevel[0].size() != 1) {
		printf("-1\n");
		return 0;
	}
	for(level=1;level<n;level++) {
		if(level > 1 && treeLevel[level-1].size()*(k-1) < treeLevel[level].size()) {
			printf("-1\n");
			return 0;
		}
		if(level == 1 && k < treeLevel[level].size()) {
			printf("-1\n");
			return 0;
		}

		j = 0;
		for(i=0;i<treeLevel[level-1].size();i++) {
			if(level != 1) limit = k-1;
			else limit = k;
			for(;j<treeLevel[level].size() && limit>0;j++) {
				graph[treeLevel[level-1][i]].push_back(treeLevel[level][j]);
				limit--;
			}
		}
	}

	m = 0;
	for(i=0;i<n;i++) {
		m += graph[i].size();
	}
	printf("%I64d\n",m);

	for(i=0;i<n;i++) {
		for(j=0;j<graph[i].size();j++) {
			printf("%I64d %I64d\n",i+1, graph[i][j]+1);
		}
	}


	return 0;
}