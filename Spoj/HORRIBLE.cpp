#include <iostream>
#include <cstring>

#define MAX 100010

using namespace std;

typedef long long int lli;

lli range_query(int l, int r);
lli prefix_query(int x);
lli internal_query(lli *bit, int x);
void range_update(int l, int r, lli delta);
void point_update(lli *bit, int x, lli delta);

lli b1[MAX], b2[MAX];

// 1 based indexing.
int main() {
    int t, n, q, l, r, q_type;
    lli num;
    char cmd[10];
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &q);
        memset(b1, 0, sizeof(b1));
        memset(b2, 0, sizeof(b2));
        while(q--) {
            scanf("%d", &q_type);
            if (q_type == 0) {
                scanf("%d%d%lld", &l, &r, &num);
                range_update(l, r, num);
            } else {
                scanf("%d%d", &l, &r);
                printf("%lld\n", range_query(l, r));
            }
        }
    }
    return 0;
}

lli range_query(int l, int r) {
    return prefix_query(r) - prefix_query(l - 1);
}

lli prefix_query(int x) {
    return internal_query(b1, x) * x - internal_query(b2, x);
}

lli internal_query(lli *bit, int x) {
    lli res = 0;
    for (int i = x; i > 0; i -= i&(-i)) res += bit[i];
    return res;
}

void range_update(int l, int r, lli delta) {
    point_update(b1, l, delta);
    point_update(b1, r + 1, -delta);
    point_update(b2, l, delta * (l - 1));
    point_update(b2, r + 1, -delta * r);
}

void point_update(lli *bit, int x, lli delta) {
    for (int i = x; i <= MAX; i += i&(-i)) bit[i] += delta;
}