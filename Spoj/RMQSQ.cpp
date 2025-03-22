#include <iostream>
#include <algorithm>
#include <vector>

#define MAX 100010
#define MAXLOG 17

using namespace std;

typedef long long int lli;

void precomputeMinimum(lli *a, lli n);
lli log2_floor(lli i);

lli minimum[MAXLOG][MAX];

int main() {
    lli n, q, l, r, k, a[MAX];
    cin>>n;
    for (int i = 0; i < n; i++) cin>>a[i];
    precomputeMinimum(a, n);

    cin>>q;
    for (int i = 0; i < q; i++) {
        cin>>l>>r;
        k = log2_floor(r-l+1);
        cout<<min(minimum[k][l], minimum[k][r - (1<<k) + 1])<<endl;
    }
    return 0;
}

lli log2_floor(lli i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

void precomputeMinimum(lli *a, lli n) {
    lli k = log2_floor(n);
    for (int i = 0; i < n; i++) minimum[0][i] = a[i];
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= n - (1 << i); j++) {
            minimum[i][j] = min(minimum[i-1][j], minimum[i-1][j + (1<<(i-1))]);
        }
    }
}
