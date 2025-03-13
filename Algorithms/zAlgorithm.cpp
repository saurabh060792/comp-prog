#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>

#define MAX 100005

using namespace std;

void zAlgorithm(int *Z, char *S);

int main()
{
	int *Z,i;
	char *S;
	Z = (int*)malloc(MAX*sizeof(int));
	S = (char*)malloc(MAX*sizeof(char));

	scanf("%s",S);
	zAlgorithm(Z,S);
	for(i=0;i<strlen(S);i++) printf("%d  ",Z[i]);
	printf("\n");

	return 0;
}

void zAlgorithm(int *Z, char *S)
{
	int l = 0, r = 0, i, k, n = strlen(S);

	for (i=1;i<n;i++) {
		if(i > r) {
			l = r = i;
			while(r < n && S[r-l] == S[r]) r++;
			Z[i] = r-l;
			r--;
		}
		else {
			k = i-l;
			if (Z[k] < r-i+1) Z[i] = Z[k];
			else {
				l = i;
				while(r < n && S[r-l] == S[r]) r++;
				Z[i] = r-l; r--;
			}
		}
	}
	Z[0] = n;
}


//Nice Tutorial http://codeforces.com/blog/entry/3107