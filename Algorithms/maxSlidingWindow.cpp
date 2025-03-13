#include <iostream>
#include <queue>

using namespace std;

void maxSlidingWindow(int A[], int n, int w, int B[]);

int main()
{
	int i,A[] = {3,4,2,1,6,8,5,7,7,0,4,6},n=12,w=3,B[10];
	maxSlidingWindow(A,n,w,B);
	for(i=0;i<10;i++) cout<<B[i]<<" ";
	cout<<endl;
	return 0;
}


void maxSlidingWindow(int A[], int n, int w, int B[]) 
{  
	deque<int> Q;
	for (int i = 0; i < w; i++) {
		while (!Q.empty() && A[i] >= A[Q.back()]) Q.pop_back();			//Queue front element is always the max element. It is the invariant.
		Q.push_back(i);
	}

	for (int i = w; i < n; i++) {
		B[i-w] = A[Q.front()];
		while (!Q.empty() && A[i] >= A[Q.back()]) Q.pop_back();			//Note that if A[i] is greater than queue's back element then for the subsequent window that queue
		while (!Q.empty() && Q.front() <= i-w) Q.pop_front();			//element cannot be the greater maximum number since we have A[i] hence pop it.
		Q.push_back(i);
	}
	B[n-w] = A[Q.front()];
}