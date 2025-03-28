#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 200010

using namespace std;

typedef long long int lli;


int main() {
    int n, k, q, l, r, a, b, arr[MAX], result[MAX];
    pair<int, int> temp[MAX];
    memset(arr, 0, sizeof(arr));
    memset(result, 0, sizeof(result));
    cin>>n>>k>>q;
    for (int i = 0; i < n; i++) {
        cin>>l>>r;
        temp[i].first = l;
        temp[i].second = r;
    }

    for (int i = 0; i < n; i++) {
        arr[temp[i].first]++;
        arr[temp[i].second + 1]--;
    }
    for (int i = 1; i < MAX; i++) arr[i] += arr[i-1];
    for (int i = 0; i < MAX; i++) if (arr[i] >= k) result[i]++;
    for (int i = 1; i < MAX; i++) result[i] += result[i-1];

    for (int i = 0; i < q; i++) {
        cin>>a>>b;
        cout<<(result[b] - result[a-1])<<endl;
    }
 
    return 0;
}
