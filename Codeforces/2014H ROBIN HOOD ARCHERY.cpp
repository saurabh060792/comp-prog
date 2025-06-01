#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <random>
#include <chrono>
#include <climits>
#include <vector>
#include <bitset>

using namespace std;

#define MAX 200005

typedef long long int lli;

vector<lli> prefix_xor;
map<int, lli> assigned_value;

// https://codeforces.com/blog/entry/85900
int main() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    int t, n, q, l, r, x;
    scanf("%d", &t);
    while (t--) {
        prefix_xor.clear();
        scanf("%d%d", &n, &q);
        prefix_xor.resize(n + 2);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &x);
            if (!assigned_value.count(x))
                assigned_value[x] = uniform_int_distribution<lli>(1, LLONG_MAX)(rng);
            prefix_xor[i] = prefix_xor[i - 1] ^ assigned_value[x];
        }

        while (q--) {
            scanf("%d%d", &l, &r);
            printf("%s\n", prefix_xor[l - 1] == prefix_xor[r] ? "YES" : "NO");
        }
    }
    return 0;
}
