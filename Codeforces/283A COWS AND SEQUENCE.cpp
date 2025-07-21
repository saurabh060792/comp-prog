#include <iostream>
#include <cstring>
#include <iomanip>

#define MAX 200010

using namespace std;

typedef long long int lli;

lli range_query(int l, int r);
lli prefix_query(int x);
lli internal_query(lli *bit, int x);
void range_update(int l, int r, lli delta);
void point_update(lli *bit, int x, lli delta);

lli b1[MAX], b2[MAX];

int main() {
    int n = 1, q, r, q_type;
    lli x;
    scanf("%d", &q);
    while (q--) {
        scanf("%d", &q_type);
        if (q_type == 1) {
            scanf("%d%lld", &r, &x);
            range_update(1, r, x);
            cout << setprecision(10) << fixed << ((long double) range_query(1, n)) / n << "\n";
        } else if (q_type == 2) {
            scanf("%lld", &x);
            n++;
            range_update(n, n, x);
            cout << setprecision(10) << fixed << ((long double) range_query(1, n)) / n << "\n";
        } else {
            x = range_query(n, n);
            range_update(n, n, -x);
            n--;
            cout << setprecision(10) << fixed << ((long double) range_query(1, n)) / n << "\n";
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
    for (int i = x; i > 0; i -= i & (-i)) res += bit[i];
    return res;
}

void range_update(int l, int r, lli delta) {
    point_update(b1, l, delta);
    point_update(b1, r + 1, -delta);
    point_update(b2, l, delta * (l - 1));
    point_update(b2, r + 1, -delta * r);
}

void point_update(lli *bit, int x, lli delta) {
    for (int i = x; i <= MAX; i += i & (-i)) bit[i] += delta;
}
