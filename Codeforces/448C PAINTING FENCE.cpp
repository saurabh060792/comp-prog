#include <cstdio>
#include <algorithm>

#define MAX 5003

using namespace std;

int calc(int *A, int left, int right, int h);

int main()
{
	int i, j, k, n, A[MAX];
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%d",&A[i]);
	printf("%d\n",calc(A,0,n-1,0));
	return 0;
}

//calc calculate the ans in the interval left to right such that h height of 
//fence has already been painted
int calc(int *A, int left, int right, int h)
{
	int minIndex;
	if(left>right) return 0;
	minIndex = min_element(A+left, A+right+1) - A;
	return min(right-left+1, A[minIndex] - h + calc(A, left, minIndex-1, A[minIndex]) + calc(A, minIndex+1, right, A[minIndex]));
}