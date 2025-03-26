#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>

#define MAX 100010
#define MAXLOG 17

using namespace std;

typedef long long int lli;

void buildSparseTable(lli *a, lli n);
lli log2_floor(lli i);

lli gcd[MAXLOG][MAX], a[MAX];

int main() {
    lli n, q, logn, x;
    map<lli, lli> result;
    scanf("%lld", &n);
    for(int i = 0; i < n; i++) scanf("%lld", a+i);
    buildSparseTable(a, n);
    logn = log2_floor(n);

    // Kind of Brute force approach.
    for(int i = 0; i < n; i++) {
        lli g = a[i];
        int j = i;
        // For every i find farthest j (by jumping 2^k steps) where
        // gcd remains the same.
        while(j < n) {
            g = __gcd(g, a[j]);
            int k;
            for(k = 0; k <= logn; k++)
                if(!gcd[k][j] || __gcd(g, gcd[k][j]) != g)
                    break;
            --k;
            result[g] += (1<<k);
            j += (1<<k);
        }
    }
    scanf("%lld", &q);
    for(int i = 0; i < q; i++) {
        scanf("%lld", &x);
        printf("%lld\n", result[x]);
    }
}

lli log2_floor(lli i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

void buildSparseTable(lli *a, lli n) {
    lli k = log2_floor(n);
    for (int i = 0; i < n; i++) gcd[0][i] = a[i];
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= n - (1 << i); j++) {
            gcd[i][j] = __gcd(gcd[i-1][j], gcd[i-1][j + (1<<(i-1))]);
        }
    }
}
