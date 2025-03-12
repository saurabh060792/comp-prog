#include <cstdio>
#include <cstring>

#define MAX 100005

using namespace std;

char s[MAX];
int pi[MAX];

void prefixFunction(char* P, int n);

int main()
{
	int n;
	while(1) {
		scanf("%s",s);
		if(s[0] == '*') break;
		n = strlen(s);
		prefixFunction(s, n);
		printf("%d\n",n%(n-pi[n-1]-1)?1:n/(n-pi[n-1]-1));
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