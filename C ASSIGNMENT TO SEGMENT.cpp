#include <iostream>

#define MAXARRAY 1000010
#define MAXTREE 4000010

using namespace std;

typedef long long int lli;

struct segment_tree_node {
    lli value;
};

void build(int node, int tl, int tr);
segment_tree_node query(int node, int tl, int tr, int p);
void update(int node, int tl, int tr, int l, int r, segment_tree_node value);
void push(int node);

segment_tree_node tree[MAXTREE];
lli arr[MAXARRAY];
bool marked[MAXTREE];  // If true, then this node stores some delayed(lazy) operation.

int main() {
    int n, q, l, r, q_type, pos;
    lli v;
    cin>>n>>q;

    // No need to take input or build segment tree becuase
    // array is initialized to zero.
    // for (int i = 0; i < n; i++) cin>>arr[i];
    // build(1, 0, n - 1);

    for (int i = 0; i < q; i++) {
        cin>>q_type;
        if (q_type == 1) {
            cin>>l>>r>>v;
            update(1, 0, n - 1, l, r - 1, {v});
        } else {
            cin>>pos;
            segment_tree_node res = query(1, 0, n - 1, pos);
            cout<<res.value<<endl;
        }

    } 
    return 0;
}

// Call with node = 1, tl = 0, tr = n - 1
void build(int node, int tl, int tr) {
    if(tl == tr) {
        tree[node].value = arr[tl];
        return;
    }
    int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
    build(left_node, tl, tm); // left node will be 2*node
    build(right_node, tm + 1, tr);  // right node will be 2*node+1
    
    // Tree node values will be used for storing delayed operation information.
    tree[node].value = 0;
    return;
}

// Call with node = 1 as segment tree array starts with 1.
segment_tree_node query(int node, int tl, int tr, int p) {
    if (tl == tr) return tree[node];
    push(node);
    int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
    if (p <= tm) return query(left_node, tl, tm, p);
    else return query(right_node, tm + 1, tr, p);
}

void update(int node, int tl, int tr, int l, int r, segment_tree_node value) {
    if (l > r) return;
    if(l == tl && tr == r) {
        tree[node] = value;
        marked[node] = true;
        return;
    }
    push(node);
    int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
    update(left_node, tl, tm, l, min(r, tm), value);
    update(right_node, tm + 1, tr, max(l, tm + 1), r, value);
}

void push(int node) {
    if (marked[node]) {
        int left_node = node<<1, right_node = node<<1|1;
        tree[left_node] = tree[right_node] = tree[node];
        marked[left_node] = marked[right_node] = true;
        marked[node] = false;
    }
}
