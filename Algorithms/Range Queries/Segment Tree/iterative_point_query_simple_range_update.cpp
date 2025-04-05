#include <iostream>

#define MAXARRAY 1000010
#define MAXTREE 2000020

using namespace std;
 
typedef long long int lli;

struct segment_tree_node {
    lli sum;
};

void build_segment_tree(int n);
segment_tree_node query(int n, int p);
void update(int n, int l, int r, lli value);
segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node);

segment_tree_node tree[MAXTREE];

// **Simple** Range Updates and Point Query
// Simple: This means range update order doesn't matter. That is
// if Range update is adding a value to a range then order of
// U1 & U2 doesn't matter. However if Range update is setting a value
// to a position then the order of U1 & U2 matters.
//
// Example
// Update: Add val to each element in range [l, r]
// Query: Get element at position pos
int main() {
    int n, q, l, r, pos, q_type;
    lli val;
    cin>>n>>q;
    // Initialize tree with array elements in Iterative Segment Tree.
    for (int i = 0; i < n; i++) cin>>tree[n + i].sum;

    // No need to build segment tree. If there are no updates then
    // point query is just asking for array elements. However
    // if there are updates then tree internal nodes (non leaf nodes)
    // will store temporary values which may get propaged to leaf
    // at the time of query.

    // build_segment_tree(n);

    for (int i = 0; i < q; i++) {
        cin>>q_type;
        if (q_type == 1) {
            cin>>l>>r>>val;
            update(n, l - 1, r - 1, val);
        } else {
            cin>>pos;
            segment_tree_node res = query(n, pos - 1);
            cout<<res.sum<<endl;            
        }
    }

    return 0;
}

void build_segment_tree(int n) {
    for (int i = n - 1; i > 0; i--) tree[i] = combine(tree[i<<1],  tree[i<<1|1]);
}

// Range update in [l, r]
void update(int n, int l, int r, lli value) {
  for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
    if (l&1) tree[l] = combine({value}, tree[l]), l++;
    if (r&1) r--, tree[r] = combine(tree[r], {value});
  }
}

segment_tree_node query(int n, int p) {
  segment_tree_node res = {0};
  for (p += n; p > 0; p >>= 1) res = combine(res, tree[p]);
  return res;
}

segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node) {
    segment_tree_node res;
    res.sum = left_node.sum + right_node.sum;
    return res;
}
