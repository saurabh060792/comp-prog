#include <iostream>
#include <cstring>

#define MAXARRAY 1000010
#define MAXTREE 2000020
#define INF_MEMSET 0x3f
#define INF 1000000009

using namespace std;

typedef long long int lli;

struct segment_tree_node {
    lli minimum, count;
};

void build(int n);
segment_tree_node query(int n, int l, int r);
void update(int n, int p, lli value);
segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node);

segment_tree_node tree[MAXTREE];

// Example
// Update: a[pos] = val
// Query: Minum element & count in range [l, r]
int main() {
    memset(tree, INF_MEMSET, sizeof(tree));
    int n, q, l, r, pos, q_type;
    lli val;
    cin >> n >> q;
    // Initialize tree with array elements in Iterative Segment Tree.
    for (int i = 0; i < n; i++) {
        cin >> tree[n + i].minimum;
        tree[n + i].count = 1;
    }

    build(n);

    for (int i = 0; i < q; i++) {
        cin >> q_type;
        if (q_type == 1) {
            cin >> pos >> val;
            update(n, pos, val);
        } else {
            cin >> l >> r;
            segment_tree_node res = query(n, l, r - 1);
            cout << res.minimum << " " << res.count << "\n";
        }
    }

    return 0;
}

void build(int n) {
    for (int i = n - 1; i > 0; i--) tree[i] = combine(tree[i << 1],  tree[i << 1 | 1]);
}

// Set value at position p and recalculate all O(log n) tree nodes.
void update(int n, int p, lli value) {
    for (tree[p += n] = {value, 1}; p > 1; p >>= 1) tree[p >> 1] = combine(tree[p], tree[p ^ 1]);
}

// Query on interval [l, r]
segment_tree_node query(int n, int l, int r) {
    segment_tree_node resl = {INF}, resr = {INF};
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
    if (left_node.minimum < right_node.minimum) res = left_node;
    else if (left_node.minimum > right_node.minimum) res = right_node;
    else {
        res.minimum = left_node.minimum;
        res.count = left_node.count + right_node.count;
    }
    return res;
}
