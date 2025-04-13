
#include <iostream>

#define MAXARRAY 1000010
#define MAXTREE 4000010

using namespace std;

typedef long long int lli;

struct segment_tree_node {
    lli value;
};

struct fight_log {
    int l, r, winner;
};

segment_tree_node query(int node, int tl, int tr, int p);
void update(int node, int tl, int tr, int l, int r, segment_tree_node value);
void push(int node);

segment_tree_node tree[MAXTREE];
fight_log results[MAXARRAY]; 
bool marked[MAXTREE];

int main() {
    int n, q, l, r;
    cin>>n>>q;
    for (int i = 0; i < q; i++) cin>>results[i].l>>results[i].r>>results[i].winner;
    for (int i = q - 1; i >= 0; i--) {
        update(1, 0, n - 1, results[i].l - 1, results[i].winner - 2, {results[i].winner});
        update(1, 0, n - 1, results[i].winner, results[i].r - 1, {results[i].winner});
    }
    for (int i = 0; i < n; i++) cout<<query(1, 0, n - 1, i).value<<" ";
    cout<<endl;
    return 0;
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
