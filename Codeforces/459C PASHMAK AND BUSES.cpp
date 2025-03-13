#include <cstdio>
#include <algorithm>

#define MAX 1003

using namespace std;

int mat[MAX][MAX];

bool isGreater(int n, int k, int d);
void arrangement(int *A, int n, int k, int d, int currDay);

int main()
{
	int n, k, d, A[MAX], i, j;
	scanf("%d%d%d",&n,&k,&d);
	if(!isGreater(n,k,d)) {
		printf("-1\n");
	}
	else {
		arrangement(A, n, k, d, 0);
		for(i=0;i<d;i++) {
			for(j=0;j<n;j++) printf("%d ",mat[i][j]);
			printf("\n");
		}
	}
	return 0;
}

void arrangement(int *A, int n, int k, int d, int currDay)
{
	int i,j;
	static int student=0;
	if(currDay == d) {
		for(i=0;i<d;i++) mat[i][student] = A[i];
		student++;
		return;
	}
	for(i=0;i<k;i++) {
		if(student == n) return;
		A[currDay] = i+1;
		arrangement(A, n, k, d, currDay+1);
	}
}

bool isGreater(int n, int k, int d) //return 1 is k^d > n
{
	int i,ans=1;
	for(i=0;i<d;i++) {
		ans *= k;
		if(ans>=n) return true;
	}
	return false;
}