#include <iostream>

#define MAXARRAY 2000010
#define MAXTREE 4000020

using namespace std;
 
typedef long long int lli;

struct segment_tree_node {
    lli sum, left, right;
};

void build(int n);
segment_tree_node query(int n, int l, int r);
void update(int n, int p, lli value);
segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node);

segment_tree_node tree[MAXTREE];

int main() {
    int n, q, l, r, pos, q_type;
    lli val;
    cin>>n>>q;
    // Initialize tree with array elements in Iterative Segment Tree.
    for (int i = 0; i < n; i++) {
        cin>>val;
        tree[n + i] = {val, val > 0 ? val : 0, val > 0 ? val : 0};
    }

    build(n);

    for (int i = 0; i < q; i++) {
        cin>>q_type;
        if (q_type == 1) {
            cin>>pos>>val;
            update(n, pos-1, val);
        } else {
            cin>>l>>r;
            segment_tree_node res = query(n, l-1, r-1);
            cout<<res.left<<endl;
        }
    }

    return 0;
}

void build(int n) {
    for (int i = n - 1; i > 0; i--) tree[i] = combine(tree[i<<1],  tree[i<<1|1]);
}

// Set value at position p and recalculate all O(log n) tree nodes.
void update(int n, int p, lli value) {
    lli left_value, right_value;
    left_value = value > 0 ? value : 0;
    right_value = value > 0 ? value : 0;
    for (tree[p += n] = {value, left_value, right_value}; p >>= 1;)
        tree[p] = combine(tree[p<<1], tree[p<<1|1]);
}

// Query on interval [l, r]
segment_tree_node query(int n, int l, int r) {
    segment_tree_node resl = {0, 0, 0}, resr = {0, 0, 0};
    // r starts at n+1 to make the interval inclusive. If
    // r starts from n then interval will be [l, r).
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if (l&1) resl = combine(resl, tree[l++]);
        if (r&1) resr = combine(tree[--r], resr);
    }
    return combine(resl, resr);
}

segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node) {
    segment_tree_node res;
    res.sum = left_node.sum + right_node.sum;
    res.left = left_node.left;
    res.right = right_node.right;
    if (left_node.sum + right_node.left > res.left) res.left = left_node.sum + right_node.left;
    if (right_node.sum + left_node.right > res.right) res.right = right_node.sum + left_node.right;
    return res;
}
