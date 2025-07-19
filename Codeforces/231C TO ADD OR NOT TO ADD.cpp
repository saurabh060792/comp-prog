#include <iostream>
#include <algorithm>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

lli const MAX = 1000005, INF = 1000000009;

lli a[MAX];

int main() {
    lli n, i, j, k, op, max_ans = -1, max_ele = -1;
    scanf("%lld%lld", &n, &k);
    for (i = 0; i < n; i++) scanf("%lld", &a[i]);
    sort(a, a + n);

    i = j = op = 0;
    while (i < n) {
        while (op <= k && j < n) {
            op += (j + 1 < n) * (a[j + 1] - a[j]) * (j - i + 1);
            j++;
        }
        if (j - i > max_ans) {
            max_ans = j - i;
            max_ele = a[j - 1];
        }
        i++;
        op -= (a[j] - a[i - 1]);
    }
    printf("%lld %lld\n", max_ans, max_ele);
    return 0;
}
