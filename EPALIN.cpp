#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

#define MAX 100005

using namespace std;

char s[MAX], revs[MAX];
int pi[MAX];

void prefixFunction(char* P, int n);

int main()
{
	int i,n,k,j;
	while(scanf("%s",s)>0) {
		n = strlen(s);
		if(n==1) {
			printf("%s\n",s);
			continue;
		}
		k = -1;
		for(i=0;i<n;i++) revs[i] = s[n-i-1];
		prefixFunction(revs, n);
		for(i=0;i<n;i++) {
			while(k>-1 && revs[k+1] != s[i]) k = pi[k];
			if(revs[k+1] == s[i]) k++;
			if(k == n-i-2) {								//two middle element
				k++;
				printf("%s",s);
				for(j=i-k;j>=0;j--) printf("%c",s[j]);
				break;
			}
			else if(k == n-i-3) {							//one middle element
				k++;
				printf("%s",s);
				for(j=i-k;j>=0;j--) printf("%c",s[j]);
				break;
			}
		}
		printf("\n");
	}
	return 0;
}

void prefixFunction(char* P, int n)
{
	int k=-1,i;
	pi[0] = -1;
	for(i=1;i<n;i++) {
		while(k>-1 && P[k+1]!=P[i]) k = pi[k];
		if(P[k+1]==P[i]) k++;
		pi[i] = k;
	}
}