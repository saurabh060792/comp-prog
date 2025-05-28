#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <functional>

#define MAX 200010

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;

void solve();

pair<pll, int> thief[MAX];
lli a[MAX], b[MAX], ans[MAX], sum, n, k;

int main() {
    lli t;
    scanf("%lld", &t);
    while (t--) solve();
    return 0;
}

void solve() {
    priority_queue<lli, vector<lli>, greater<lli>> top_k;
    sum = 0;
    scanf("%lld%lld", &n, &k);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++) scanf("%lld", &b[i]);
    for (int i = 0; i < n; i++) thief[i] = {{a[i], b[i]}, i};
    sort(thief, thief + n);

    for (int i = 0; i < n; i++) {
        lli level = thief[i].first.first;
        lli coin = thief[i].first.second;
        if (i < k) {
            ans[thief[i].second] = sum;
            top_k.push(coin);
            sum += coin;
        } else {
            ans[thief[i].second] = sum;
            lli min_coin = top_k.top();
            if (coin > min_coin) {
                top_k.pop();
                top_k.push(coin);
                sum += coin - min_coin;
            }
        }
    }

    for (int i = 0; i < n; i++) printf("%lld ", ans[i]);
    printf("\n");
}
