#include <iostream>
#include <cmath>
#include <cstring>

#define MAXARRAY 1000010
#define MAXTREE 4000010

using namespace std;

typedef long long int lli;

struct segment_tree_node {
    lli maximum, sum;
};

void build(int node, int tl, int tr);
void updateSquareRoot(int node, int tl, int tr, int l, int r);
lli query(int node, int tl, int tr, int l, int r);

segment_tree_node tree[MAXTREE];
lli arr[MAXARRAY];

// Segment tree beat.
int main() {
    int n, test_case = 0, q, q_type, l, r, x, k;
    while (scanf("%d", &n) != EOF) {
        memset(tree, 0, sizeof(tree));
        memset(arr, 0, sizeof(arr));
        test_case++;
        printf("Case #%d:\n", test_case);
        for (int i = 0; i < n; i++) scanf("%lld", &arr[i]);

        build(1, 0, n - 1);

        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            scanf("%d%d%d", &q_type, &l, &r);
            if(l > r) swap(l, r);
            l--;
            r--;
            if (q_type == 1) printf("%lld\n", query(1, 0, n - 1, l, r));
            else updateSquareRoot(1, 0, n - 1, l, r);
        }
        printf("\n");
    }
    return 0;
}

// Call with node = 1 as segment tree array starts with 1.
void build(int node, int tl, int tr) {
    if (tl == tr) {
        tree[node].maximum = tree[node].sum = arr[tl];
        return;
    }
    int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
    build(left_node, tl, tm);
    build(right_node, tm + 1, tr);
    tree[node].sum = tree[left_node].sum + tree[right_node].sum;
    tree[node].maximum = max(tree[left_node].maximum, tree[right_node].maximum);
}

void updateSquareRoot(int node, int tl, int tr, int l, int r) {
    // Squar root doesn't change if segment only has 1's and 0's.
    // And every time we take floor of square root of n, it goes down by
    // at least half if n > 1.
    if (l > r || tree[node].maximum <= 1) return;
    // In Segment tree beats, update can some time go the leaf
    // node instead of normal node in case of normal segment tree
    // update.
    if (tl == tr) {
        tree[node].maximum = floor(sqrt(tree[node].maximum));
        tree[node].sum = tree[node].maximum;
        return;
    }
    int mid = (r + l) / 2;
    int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
    updateSquareRoot(left_node, tl, tm, l, min(r, tm));
    updateSquareRoot(right_node, tm + 1, tr, max(l, tm + 1), r);
    tree[node].sum = tree[left_node].sum + tree[right_node].sum;
    tree[node].maximum = max(tree[left_node].maximum, tree[right_node].maximum);
}

lli query(int node, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (l == tl && r == tr) return tree[node].sum;
    int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
    return query(left_node, tl, tm, l, min(r, tm)) + query(right_node, tm + 1, tr, max(l, tm + 1), r);
}
