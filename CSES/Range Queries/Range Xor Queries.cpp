#include <iostream>

#define MAXARRAY 1000010
#define MAXTREE 2000020

using namespace std;
 
typedef long long int lli;

struct segment_tree_node {
    lli sum;
};

void build_segment_tree(int n);
segment_tree_node query(int n, int l, int r);
segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node);

segment_tree_node tree[MAXTREE];

// Static Range Queries
// Example Query: Sum of elements in range [l, r]
int main() {
    int n, q, l, r;
    cin>>n>>q;
    // Initialize tree with array elements in Iterative Segment Tree.
    for (int i = 0; i < n; i++) cin>>tree[n + i].sum;

    build_segment_tree(n);

    for (int i = 0; i < q; i++) {
        cin>>l>>r;
        segment_tree_node res = query(n, l-1, r-1);
        cout<<res.sum<<endl;
    }

    return 0;
}

void build_segment_tree(int n) {
    for (int i = n - 1; i > 0; i--) tree[i] = combine(tree[i<<1],  tree[i<<1|1]);
}

// Query on interval [l, r]
segment_tree_node query(int n, int l, int r) {
    segment_tree_node resl = {0}, resr = {0};
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
    res.sum = left_node.sum ^ right_node.sum;
    return res;
}
