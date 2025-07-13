#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

lli const MAX = 101, MOD = 1000000007;

void solve();

string mat[MAX];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) solve();
    return 0;
}

void solve() {
    lli n, ans = 1, ones, bad = 1, two_ones;
    scanf("%lld", &n);
    for (int i = 0; i < n; i++) {
        ones = 0;
        cin >> mat[i];
        for (int j = 0; j < n; j++) if (mat[i][j] == '1') ones++;
        ans = (ans * ones) % MOD;
    }

    for (int i = 0; i < n / 2; i++) {
        two_ones = 0;
        for (int j = 0; j < n; j++) if (mat[i][j] == '1' && mat[i + (n / 2)][j] == '1') two_ones++;
        bad = (bad * two_ones) % MOD;
    }
    printf("%lld\n", (ans - bad + MOD) % MOD);

}
