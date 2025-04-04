#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <set>
#include <map>

#define MAX 1010

using namespace std;

typedef long long int lli;

int main() {
    freopen("diamond.in", "r", stdin);
    freopen("diamond.out", "w", stdout);

    int n, k, arr[MAX], count, max_count = 0;
    cin>>n>>k;
    for (int i = 0; i < n; i++) cin>>arr[i];
    sort(arr, arr + n);

    if (n == 0 || n == 1) count = n;

    for (int i = 0; i < n; i++) {
        count = 1;
        for (int j = i+1; j < n; j++)
            if (arr[i] + k >= arr[j]) count++;
        max_count = max(max_count, count);     
    }
    cout<<max_count<<endl;
    return 0;
}
