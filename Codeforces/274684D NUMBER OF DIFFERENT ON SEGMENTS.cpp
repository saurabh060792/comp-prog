#include <iostream>
#include <map>
#include <bitset>

#define MAXARRAY 1000010
#define MAXTREE 2000020

using namespace std;

typedef long long int lli;

struct segment_tree_node {
    lli freq;
};

void build(int n);
segment_tree_node query(int n, int l, int r);
void update(int n, int p, lli value);
segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node);

segment_tree_node tree[MAXTREE];

int main() {
    int n, q, l, r, pos, q_type;
    lli val;
    scanf("%d%d", &n, &q);
    // Initialize tree with array elements in Iterative Segment Tree.
    for (int i = 0; i < n; i++) {
        scanf("%lld", &val);
        tree[n + i].freq = 1LL << val;
    }

    build(n);

    for (int i = 0; i < q; i++) {
        scanf("%d", &q_type);
        if (q_type == 1) {
            int ans = 0;
            scanf("%d%d", &l, &r);
            segment_tree_node res = query(n, l - 1, r - 1);
            printf("%d\n", __builtin_popcountll(res.freq));
        } else {
            scanf("%d%lld", &pos, &val);
            update(n, pos - 1, val);
        }
    }

    return 0;
}

void build(int n) {
    for (int i = n - 1; i > 0; i--) tree[i] = combine(tree[i << 1],  tree[i << 1 | 1]);
}

// Set value at position p and recalculate all O(log n) tree nodes.
void update(int n, int p, lli value) {
    for (tree[p += n] = {1LL << value}; p > 1; p >>= 1) tree[p >> 1] = combine(tree[p], tree[p ^ 1]);
}

// Query on interval [l, r]
segment_tree_node query(int n, int l, int r) {
    segment_tree_node resl = {0}, resr = {0};
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
    res.freq = left_node.freq | right_node.freq;
    return res;
}
