#include <iostream>

using namespace std;

int A[200200], zero[200200];

int main() {
	int i,n;
	long long int res;
	cin>>n;
	for(i=0;i<n;i++) cin>>A[i];
	zero[n-1] = 1 - A[n-1];
	for (i=n-2;i>=0;i--) zero[i] = zero[i + 1] + 1 - A[i];

	res = 0;
	for(i=0;i<n;i++)
		if(A[i] == 1) res += zero[i];
	cout<<res;
	return 0;
}