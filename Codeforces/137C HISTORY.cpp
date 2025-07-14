#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

lli const MAX = 200005;

pii events[MAX];

int main() {
    int n, re, ans = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d%d", &events[i].first, &events[i].second);
    sort(events, events + n);
    re = events[0].second;
    for (int i = 1; i < n; i++) {
        if (events[i].second > re) re = events[i].second;
        else ans++;
    }
    printf("%d\n", ans);
    return 0;
}
