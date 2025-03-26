#include <iostream>

#define MAXARRAY 1000010
#define MAXTREE 4000010

using namespace std;

typedef long long int lli;

struct segment_tree_node {
    lli zeros = 0;
};

segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node);
void buildST(int node, int tl, int tr);
segment_tree_node queryST(int node, int tl, int tr, int l, int r);
int findKthZero(int node, int l, int r, int k);
void updateST(int node, int tl, int tr, int position, segment_tree_node value);

int n;
segment_tree_node tree[MAXTREE], arr[MAXARRAY];

int main() {
    int m, l, r, temp, query_type, k, p, x;
    cin>>n>>m;
    for (int i = 0; i < n; i++) {
        cin>>temp;
        if (temp == 0) arr[i].zeros = 1;
    }
 
    buildST(1, 0, n - 1);

    for (int i = 0; i < m; i++) {
        cin>>query_type;
        if (query_type == 1) {
            cin>>k;
            int kthZeroIndex = findKthZero(1, 0, n - 1, k);
            if (kthZeroIndex == -1) cout<<"NO"<<endl;
            else cout<<kthZeroIndex<<endl;
        } else {
            cin>>p>>x;
            segment_tree_node x_node = {};
            x_node.zeros = x == 0 ? 1 : 0;
            updateST(1, 0, n - 1, p, x_node);
        }
    }
 
    return 0;
}

segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node) {
    segment_tree_node res;
    res.zeros = left_node.zeros + right_node.zeros;
    return res;
}

// Call with node = 1, tl = 0, tr = n - 1
void buildST(int node, int tl, int tr) {
    if(tl == tr) {
        tree[node] = arr[tl];
        return;
    }
    int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
    buildST(left_node, tl, tm); // left node will be 2*node
    buildST(right_node, tm + 1, tr);  // right node will be 2*node+1
    tree[node] = combine(tree[left_node], tree[right_node]);
    return;
}

// Call with node = 1 as segment tree array starts with 1.
// Query in interval [l, r] inclusive.
segment_tree_node queryST(int node, int tl, int tr, int l, int r) {
    if(l > tr || r < tl) return segment_tree_node();
    if(l <= tl && r >= tr) return tree[node];
    int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
    segment_tree_node resl, resr;
    resl = queryST(left_node, tl, tm, l, r);
    resr = queryST(right_node, tm + 1, tr, l, r);
    return combine(resl, resr);
}

int findKthZero(int node, int l, int r, int k) {
    if (tree[node].zeros < k) return -1;
    if (l == r) return l;
    int m = (l + r)>>1, left_node = node<<1, right_node = node<<1|1;
    if (tree[left_node].zeros >= k) return findKthZero(left_node, l, m, k);
    else return findKthZero(right_node, m + 1, r, k - tree[left_node].zeros);
}

void updateST(int node, int tl, int tr, int position, segment_tree_node value) {
    if(tl == tr) {
        tree[node] = value;
        return;
    }
    int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
    if(position <= tm) updateST(left_node, tl, tm, position, value);
    else updateST(right_node, tm + 1, tr, position, value);
    tree[node] = combine(tree[left_node], tree[right_node]);
}
