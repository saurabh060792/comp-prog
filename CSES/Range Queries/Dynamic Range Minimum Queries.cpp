#include <iostream>

#define MAXARRAY 1000010
#define MAXTREE 2000020
#define INF 1000000001

using namespace std;
 
typedef long long int lli;

struct segment_tree_node {
    lli minimum;
};

void build_segment_tree(int n);
segment_tree_node query(int n, int l, int r);
void modify(int n, int p, lli value);
segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node);

segment_tree_node tree[MAXTREE];

// Dynamic Range Queries
// Example
// Update: a[pos] = val
// Query: Sum of elements in range [l, r]
int main() {
    int n, q, l, r, pos, q_type;
    lli val;
    cin>>n>>q;
    for (int i = 0; i <= 2*n; i++) tree[i].minimum = INF;
    for (int i = 0; i < n; i++) cin>>tree[n + i].minimum;

    build_segment_tree(n);

    for (int i = 0; i < q; i++) {
        cin>>q_type;
        if (q_type == 1) {
            cin>>pos>>val;
            modify(n, pos-1, val);
        } else {
            cin>>l>>r;
            segment_tree_node res = query(n, l-1, r-1);
            cout<<res.minimum<<endl;
        }
    }

    return 0;
}

void build_segment_tree(int n) {
    for (int i = n - 1; i > 0; i--) tree[i] = combine(tree[i<<1],  tree[i<<1|1]);
}

// Set value at position p and recalculate all O(log n) tree nodes.
void modify(int n, int p, lli value) {
  for (tree[p += n] = {value}; p > 1; p >>= 1) tree[p>>1] = combine(tree[p], tree[p^1]);
}

// Query on interval [l, r]
segment_tree_node query(int n, int l, int r) {
    segment_tree_node resl = {INF}, resr = {INF};
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
    res.minimum = min(left_node.minimum, right_node.minimum);
    return res;
}
