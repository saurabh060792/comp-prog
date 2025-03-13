#include <iostream>
#include <algorithm>
#include <set>

#define MAX 1000

using namespace std;

int main()
{
	int a[MAX],n,i;
	cin>>n;
	for(i=0;i<n;i++) cin>>a[i];
	set<int> result;  //result[j] = a[k] stores the smallest value a[k] such that there is an increasing subsequence of length j ending at a[k] on the range k ≤ i
	set<int>::iterator it;
	// result.clear();
	for(int i=0; i<n; i++) {
		it = result.lower_bound(a[i]);		//points to the first element which is greater or equal to a[i]
		if (it != result.end()) result.erase(it);
		result.insert(a[i]);
	}
	cout<<result.size()<<endl;
	return 0;
}