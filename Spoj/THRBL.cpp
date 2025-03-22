#include <iostream>
#include <algorithm>
#include <vector>

#define MAX 50010
#define MAXLOG 16

using namespace std;

typedef long long int lli;

void buildSparseTable(lli *a, lli n);
lli log2_floor(lli i);

lli maximum[MAXLOG][MAX];

int main() {
    lli n, m, l, r, k, a[MAX], maxInInterval, result = 0;
    cin>>n>>m;
    for (int i = 0; i < n; i++) cin>>a[i];
    buildSparseTable(a, n);

    for (int i = 0; i < m; i++) {
        cin>>l>>r;
        if (l > r) swap(l, r);
        if(r - l <= 1)  { // No Hill
            result++;
            continue;
        }
        k = log2_floor(r - l - 1);
        maxInInterval = max(maximum[k][l], maximum[k][r - (1<<k) - 1]);
        if (maxInInterval <= a[l - 1]) result++;
    }
    cout<<result<<endl;
    return 0;
}

lli log2_floor(lli i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

void buildSparseTable(lli *a, lli n) {
    lli k = log2_floor(n);
    for (int i = 0; i < n; i++) maximum[0][i] = a[i];
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= n - (1 << i); j++) {
            maximum[i][j] = max(maximum[i-1][j], maximum[i-1][j + (1<<(i-1))]);
        }
    }
}
