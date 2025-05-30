#include <iostream>

#define MAXARRAY 1000010
#define MAXTREE 2000020

using namespace std;

typedef long long int lli;

struct segment_tree_node {
    lli even_sum, odd_sum;
};

void build(int n);
segment_tree_node query(int n, int l, int r);
void update(int n, int p, lli value);
segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node);

segment_tree_node tree[MAXTREE];

int main() {
    int n, q, l, r, pos, q_type;
    lli val;
    scanf("%d", &n);
    // Initialize tree with array elements in Iterative Segment Tree.
    for (int i = 0; i < n; i++) {
        scanf("%lld", &val);
        if (i % 2) tree[n + i].odd_sum = val;
        else tree[n + i].even_sum = val;
    }

    build(n);
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &q_type);
        if (q_type == 0) {
            scanf("%d%lld", &pos, &val);
            update(n, pos - 1, val);
        } else {
            scanf("%d%d", &l, &r);
            segment_tree_node res = query(n, l - 1, r - 1);
            if (l % 2) printf("%lld\n", res.even_sum - res.odd_sum);
            else printf("%lld\n", res.odd_sum - res.even_sum);
        }
    }

    return 0;
}

void build(int n) {
    for (int i = n - 1; i > 0; i--) tree[i] = combine(tree[i << 1],  tree[i << 1 | 1]);
}

// Set value at position p and recalculate all O(log n) tree nodes.
void update(int n, int p, lli value) {
    segment_tree_node seg_value;
    if (p % 2) seg_value = {0, value};
    else seg_value = {value, 0};
    for (tree[p += n] = seg_value; p > 1; p >>= 1) tree[p >> 1] = combine(tree[p], tree[p ^ 1]);
}

// Query on interval [l, r]
segment_tree_node query(int n, int l, int r) {
    segment_tree_node resl = {0, 0}, resr = {0, 0};
    // r starts at n+1 to make the interval inclusive. If
    // r starts from n then interval will be [l, r).
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) resl = combine(resl, tree[l++]);
        if (r & 1) resr = combine(tree[--r], resr);
    }
    return combine(resl, resr);
}

segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node) {
    segment_tree_node res;
    res.even_sum = left_node.even_sum + right_node.even_sum;
    res.odd_sum = left_node.odd_sum + right_node.odd_sum;
    return res;
}
