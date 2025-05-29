#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define MAX 200010

using namespace std;

typedef long long int lli;

lli range_query(int l, int r);
lli prefix_query(int x);
void point_update(int x, lli delta);

lli bit[MAX], arr[MAX], inv_l[MAX], inv_r[MAX], pos[MAX];
int n;

// Case 1: i < j, Ai < Aj
// If Ai, Aj pair doens't form an inversion then correspoinding Bi, Bj will
// also not form an inversion.
//
// Case 2: i < j, Ai > Aj
// In case of inversion there are 6 possiblities for Ai, Aj, L, R
//
// Subcase 1: Aj < Ai <= L < R
// In this case both Ai and Aj will become L. So an inversion pair in A doesn't
// become an inversion pair in B
//
// Subcase 2: Aj < L < Ai < R
// Subcase 3: Aj < L < R < Ai
// Subcase 4: L < Aj < Ai < R
// Subcase 5: L < Aj < R < Ai
// In all of these cases, inversion pair in A converts to inversion pair in B
//
// Subcase 6: L < R <= Aj < Ai
// In this case both Ai and Aj will become R. So again inversion pair to non
// inversion pair conversion.
//
// We only have to calculate # inversion in subcase 1 & 6
// Subcase 1: For all L in [1, n], calculate # inversion pair formed by numbers
// less than L.
// Subcase 6: For all R in [1, n], calculate # inversion pair formed by numbers
// greater than R. 
int main() {
    int t, q, l, r;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &arr[i]);
            pos[arr[i]] = i;
        }

        for (int i = 0; i <= n + 1; i++) bit[i] = inv_l[i] = inv_r[i] = 0;

        // Subcase 1:
        // For i, we have already added 1 to pos[j] for j < i. So we need to query
        // [pos[i], n] to count all the 1's that are on the right of pos[i] and are
        // less that i.
        for (int i = 1; i <= n; i++) {
            inv_l[i] = range_query(pos[i], n) + inv_l[i - 1];
            point_update(pos[i], 1);
        }
        for (int i = 0; i <= n; i++) bit[i] = 0;

        // Subcase 6:
        // For i, we have already added 1 to pos[j] for n > j > i. So we need to query
        // [1, pos[i]] to count all the 1's that are on the left of pos[i] and are
        // greater that i.
        for (int i = n; i >= 1; i--) {
            inv_r[i] = range_query(1, pos[i]) + inv_r[i + 1];
            point_update(pos[i], 1);
        }

        while (q--) {
            scanf("%d%d", &l, &r);
            if (l == r) printf("0\n");
            else printf("%lld\n", inv_l[n] - inv_l[l] - inv_r[r]);
        }

    }
    return 0;
}

lli range_query(int l, int r) {
    return prefix_query(r) - prefix_query(l - 1);
}

lli prefix_query(int x) {
    lli res = 0;
    for (int i = x; i > 0; i -= i & (-i)) res += bit[i];
    return res;
}

void point_update(int x, lli delta) {
    for (int i = x; i <= n; i += i & (-i)) bit[i] += delta;
}
