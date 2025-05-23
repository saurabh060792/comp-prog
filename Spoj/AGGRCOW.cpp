#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int arr[100001];
int c,n;

int binSearch();
int f(int x);

int main()
{
	int t;
	scanf("%d",&t);
	
	while(t--) {
		scanf("%d %d",&n,&c);
		for(int i=0;i<n;i++) scanf("%d",&arr[i]);
		sort(arr,arr+n);
		printf("%d\n",binSearch());
	}
}

int f(int x)							//function f(x) return 1 is cows can be place
{										//such that their separation is atleast x
	int cowsplaced=1;
	long long int lastpos=arr[0];
	for(int i=1;i<n;i++) {
		if(arr[i]-lastpos>=x) {
			cowsplaced++;
			if(cowsplaced==c) return 1;
			lastpos=arr[i];
		}
	}
	return 0;
}

int binSearch()
{
	int start=0,end=arr[n-1];
	while(start<end) {
		int mid=(start+end)/2;
		if(f(mid)==1) start=mid+1;
		else end=mid;
	}
	return start-1;
}
