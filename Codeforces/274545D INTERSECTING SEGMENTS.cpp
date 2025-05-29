#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define MAX 200010

using namespace std;

typedef long long int lli;

lli range_query(lli *bit, int l, int r);
lli prefix_query(lli *bit, int x);
void point_update(lli *bit, int x, lli delta);

map<int, int> l, r, ans;
lli first_occ[MAX], second_occ[MAX], arr[MAX];
int n;

int main() {
    scanf("%d", &n);
    n *= 2;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
        if (l.find(arr[i]) == l.end()) {
            point_update(first_occ, i, 1);
            l[arr[i]] = i;
        } else {
            point_update(second_occ, i, 1);
            r[arr[i]] = i;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (ans.find(arr[i]) != ans.end()) continue;
        lli open = range_query(first_occ, l[arr[i]] + 1, r[arr[i]] - 1);
        lli close = range_query(second_occ, l[arr[i]] + 1, r[arr[i]] - 1);
        point_update(first_occ, l[arr[i]], -1);
        point_update(second_occ, r[arr[i]], -1);
        // Segment can be nested or intersecting. So just subtract 2 * nested
        // segments from the segment length.
        ans[arr[i]] = r[arr[i]] - l[arr[i]] - 1 - (2 * min(open, close));
    }

    for (int i = 1; i <= n/2; i++) printf("%d ", ans[i]);
    printf("\n");

    return 0;
}

lli range_query(lli *bit, int l, int r) {
    return prefix_query(bit, r) - prefix_query(bit, l - 1);
}

lli prefix_query(lli *bit, int x) {
    lli res = 0;
    for (int i = x; i > 0; i -= i & (-i)) res += bit[i];
    return res;
}

void point_update(lli *bit, int x, lli delta) {
    for (int i = x; i <= n; i += i & (-i)) bit[i] += delta;
}
