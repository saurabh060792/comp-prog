#include <iostream>

using namespace std;

void permutation(int*, int*, int, int, int);
void printK(int *A, int n);
void swap(int *A, int i, int j);

int main()
{
	int A[] = {1,2,3,4,5};
	permutation(A,A,3,3,5);
	return 0;
}

void permutation(int *A, int *B, int k, int l, int n)
{
	if(k==0){
		printK(B,l);
		return;
	}
	if(k==n) {
		printK(B,l);
		return;
	}
	permutation(A+1, B, k-1, l, n-1);
	swap(A, 0, n-1);
	permutation(A, B, k, l, n-1);
	swap(A, 0, n-1);
}

void swap(int *A, int i, int j)
{
	int temp;
	temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

void printK(int *A, int n)
{
	for(int i=0;i<n;i++) cout<<A[i]<<" ";
	cout<<endl;
}
