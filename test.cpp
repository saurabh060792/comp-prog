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
            // printf("1nd occ a: %d i: %d\n", a, i);
            point_update(first_occ, i, 1);
            // for (int i = 1; i <= n; i++) printf("%d ", range_query(first_occ, i, i));
            // printf("\n");
            l[arr[i]] = i;
        } else {
            // printf("2nd occ a: %d i: %d\n", a, i);
            point_update(second_occ, i, 1);
            // for (int i = 1; i <= n; i++) printf("%d ", range_query(second_occ, i, i));
            // printf("\n");
            r[arr[i]] = i;
        }
    }

    // for (int i = 1; i <= n; i++) printf("%lld ", range_query(first_occ, i, i));
    // printf("\n");

    // for (int i = 1; i <= n; i++) printf("%lld ", range_query(second_occ, i, i));
    // printf("\n");

    for (int i = 1; i <= n; i++) {
        if (ans.find(arr[i]) != ans.end()) continue;
        lli open = range_query(first_occ, l[arr[i]] + 1, r[arr[i]] - 1);
        lli close = range_query(second_occ, l[arr[i]] + 1, r[arr[i]] - 1);
        point_update(first_occ, l[arr[i]], -1);
        point_update(second_occ, r[arr[i]], -1);
        // printf("i: %d open: %lld close: %lld\n", i, open, close);
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