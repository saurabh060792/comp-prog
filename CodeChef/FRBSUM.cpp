#include <iostream>
#include <vector>
#include <algorithm>

#define MAXARRAY 100005
#define MAXTREE 400005

using namespace std;

typedef long long int lli;

typedef struct segmentTree
{
	vector<lli> data, prefixSum;
}segmentTree;

void buildSegmentTree(int currentNode, int low, int high);
lli querySegmentTree(int currentNode, int low, int high, int a, int b, int sum);

segmentTree S[MAXTREE];
lli arr[MAXARRAY];

int main()
{
	lli n,i,q,l,r,sum,newSum;
	cin>>n;
	for(i=0;i<n;i++) cin>>arr[i];
	// sort(arr, arr+n);
	buildSegmentTree(0, 0, n-1);
	cin>>q;
	for(i=0;i<q;i++) {
		cin>>l>>r;
		l--,r--;
		sum = 0;
		while(true) {
			newSum = querySegmentTree(0, 0, n-1, l, r, sum+1);
			if(newSum == sum) {
				cout<<sum+1<<endl;
				break;
			}
			sum = newSum;
		}
	}
	return 0;
}

void buildSegmentTree(int currentNode, int low, int high)
{
	int i,leftNode, rightNode, mid;
	leftNode = 2*currentNode + 1;
	rightNode = 2*currentNode +2;
	mid = (low+high)/2;

	for(i=low;i<=high;i++) {
		S[currentNode].data.push_back(arr[i]);
		S[currentNode].prefixSum.push_back(arr[i]);
	}
	sort(S[currentNode].data.begin(), S[currentNode].data.end());
	sort(S[currentNode].prefixSum.begin(), S[currentNode].prefixSum.end());
	for(i=1;i<S[currentNode].prefixSum.size();i++) S[currentNode].prefixSum[i] += S[currentNode].prefixSum[i-1]; 
	if(low != high) {
		buildSegmentTree(leftNode, low, mid);
		buildSegmentTree(rightNode, mid+1, high);
	}
}

lli querySegmentTree(int currentNode, int low, int high, int a, int b, int sum)
{
	int leftNode, rightNode, mid,it;
	leftNode = 2*currentNode + 1;
	rightNode = 2*currentNode +2;
	mid = (low+high)/2;

	if(a>high || b<low) return 0;
	else if(a<=low && b>=high) {
		it = upper_bound(S[currentNode].data.begin(), S[currentNode].data.end(), sum) - S[currentNode].data.begin();
		if(it == 0) return 0;
		return S[currentNode].prefixSum[it-1];
	}
	return querySegmentTree(leftNode, low, mid, a, b, sum) + querySegmentTree(rightNode, mid+1, high, a, b, sum);
}

