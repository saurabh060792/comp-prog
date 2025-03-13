#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int matrix[50004][6],finihTable[50004][6];

int main()
{
	int m,n,i,j;
	scanf("%d%d",&m,&n);
	for(i=0;i<m;i++)
		for(j=0;j<n;j++) scanf("%d",&matrix[i][j]);



	finihTable[0][0] = matrix[0][0];
	for(i=1;i<m;i++) finihTable[i][0] = finihTable[i-1][0] + matrix[i][0];
	for(i=1;i<n;i++) finihTable[0][i] = finihTable[0][i-1] + matrix[0][i];

	// for(i=0;i<m;i++) {
	// 	for(j=0;j<n;j++) printf("%d ",matrix[i][j]);
	// 	printf("\n");
	// }

	for(i=1;i<n;i++) {
		for(j=1;j<m;j++) {
			if(finihTable[j][i-1] < finihTable[j-1][i])
				finihTable[j][i] = finihTable[j-1][i] + matrix[j][i];
			else
				finihTable[j][i] = finihTable[j][i-1] + matrix[j][i];
		}
	}

	for(i=0;i<m;i++) printf("%d ",finihTable[i][n-1]);
	printf("\n");
	return 0;
}