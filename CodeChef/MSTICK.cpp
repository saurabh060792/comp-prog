#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

#define MAX 100010
#define MAXLOG 17

using namespace std;

typedef long long int lli;

void buildSparseTable(lli *a, lli n);
lli log2_floor(lli i);

lli maximum[MAXLOG][MAX], minimum[MAXLOG][MAX];

int main() {
    lli n, q, l, r, k, arr[MAX], max1, max2, max3, min2, max13;
    double queryMatchStick, result;
    cin>>n;
    for (int i = 0; i < n; i++) cin>>arr[i];
    buildSparseTable(arr, n);
    cin>>q;
    for (int i = 0; i < q; i++) {
        max1 = max3 = 0;
        cin>>l>>r;
        k = log2_floor(r - l + 1);
        min2 = min(minimum[k][l], minimum[k][r - (1<<k) + 1]);
        max2 = max(maximum[k][l], maximum[k][r - (1<<k) + 1]);
        if (l > 0) {
            k = log2_floor(l);
            max1 = max(maximum[k][0], maximum[k][l - (1<<k)]);
        }
        if (r < n-1) {
            k = log2_floor(n - 1 - r);
            max3 = max(maximum[k][r+1], maximum[k][n - (1<<k)]);
        }
        queryMatchStick = (double)((max2 - min2)/2.0);
        max13 = max(max1, max3);
        result = max(queryMatchStick, (double) max13);
        cout<<setprecision(1)<<fixed<<result + (double) min2<<endl;
    }
    return 0;
}

lli log2_floor(lli i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

void buildSparseTable(lli *arr, lli n) {
    lli k = log2_floor(n);
    for (int i = 0; i < n; i++) maximum[0][i] = arr[i];
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= n - (1 << i); j++) {
            maximum[i][j] = max(maximum[i-1][j], maximum[i-1][j + (1<<(i-1))]);
        }
    }

    for (int i = 0; i < n; i++) minimum[0][i] = arr[i];
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= n - (1 << i); j++) {
            minimum[i][j] = min(minimum[i-1][j], minimum[i-1][j + (1<<(i-1))]);
        }
    }
}
