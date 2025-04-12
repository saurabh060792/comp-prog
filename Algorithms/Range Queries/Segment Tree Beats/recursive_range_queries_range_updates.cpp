#include <iostream>

#define MAXARRAY 1000010
#define MAXTREE 4000010

using namespace std;

typedef long long int lli;

struct segment_tree_node {
    lli maximum, sum;
};

void build(int node, int tl, int tr);
void update_mod_equal(int node, int tl, int tr, int l, int r, int mod);
void update_equal(int node, int tl, int tr, int pos, lli val);
lli query(int node, int tl, int tr, int l, int r);

segment_tree_node tree[MAXTREE];
lli arr[MAXARRAY];

// Update: %= (mod equals), := (assigment)
// Query: + (sum)
// Example:
// Update a_i in range [l, r] with (a_i % x)
// Update a_i in range [l, r] with a_i = x
// Query sum in range [l, r]
int main() {
    int n, q, q_type, l, r, x, k;
    cin>>n>>q;
    for (int i = 0; i < n; i++) cin>>arr[i];

    build(1, 0, n - 1);

    for (int i = 0; i < q; i++) {
        cin>>q_type;
        if (q_type == 1) {
            cin>>l>>r;
            l--;
            r--;
            cout<<query(1, 0, n - 1, l, r)<<endl;
        } else if (q_type == 2) {
            cin>>l>>r>>x;
            l--;
            r--;
            update_mod_equal(1, 0, n - 1, l, r, x);
        } else {
            cin>>k>>x;
            k--;
            update_equal(1, 0, n - 1, k, x);
        }
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

void update_mod_equal(int node, int tl, int tr, int l, int r, int mod) {
    // This break condition is enough to achieve low time complexity.
    if (l > r || tree[node].maximum < mod) return;
    
    // In Segment tree beats, update can some time go the leaf
    // node instead of normal node in case of normal segment tree
    // update.
    //
    // Tag Condition is just the same as normal segemnt tree since
    // Break Condition is enough to achieve low time complexity.
    if (tl == tr) {
        tree[node].maximum %= mod;
        tree[node].sum = tree[node].maximum;
        return;
    }
    int mid = (r + l) / 2;
    int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
    update_mod_equal(left_node, tl, tm, l, min(r, tm), mod);
    update_mod_equal(right_node, tm + 1, tr, max(l, tm + 1), r, mod);
    tree[node].sum = tree[left_node].sum + tree[right_node].sum;
    tree[node].maximum = max(tree[left_node].maximum, tree[right_node].maximum);
}

void update_equal(int node, int tl, int tr, int pos, lli val) {
    if (tl == tr) {
        tree[node].maximum = tree[node].sum = val;
        return;
    }
    int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
    if (pos <= tm) update_equal(left_node, tl, tm, pos, val);
    else update_equal(right_node, tm + 1, tr, pos, val);
    tree[node].sum = tree[left_node].sum + tree[right_node].sum;
    tree[node].maximum = max(tree[left_node].maximum, tree[right_node].maximum);

}

lli query(int node, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (l == tl && r == tr) return tree[node].sum;
    int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
    return query(left_node, tl, tm, l, min(r, tm)) + query(right_node, tm + 1, tr, max(l, tm + 1), r);
}
