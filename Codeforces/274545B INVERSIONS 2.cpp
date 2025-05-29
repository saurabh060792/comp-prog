#include <iostream>

#define MAXARRAY 1000010
#define MAXTREE 4000010
#define INF 1000000

using namespace std;

typedef long long int lli;

struct segment_tree_node {
    lli minimum, lazy_sum;
};

void build(int node, int tl, int tr);
int get_first_from_right(int node, int tl, int tr, int l, int r, int x);
void update(int node, int tl, int tr, int l, int r, lli value);
void push(int node);

segment_tree_node tree[MAXTREE];
lli arr[MAXARRAY], restored[MAXARRAY];

int main() {
    int n, pos;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) scanf("%lld", &arr[i]);
    build(1, 0, n - 1);

    for (int i = n; i >= 1; i--) {
        // Find first 0 from the right and decrement everything
        // to the right of first 0 index. And make first zero
        // INF to disregard it from future calculations.
        pos = get_first_from_right(1, 0, n - 1, 0, n - 1, 0);
        restored[pos] = i;
        update(1, 0, n - 1, pos + 1, n - 1, -1);
        update(1, 0, n - 1, pos, pos, INF);
    }

    for (int i = 0; i < n; i++) printf("%d ", restored[i]);
    printf("\n");
    return 0;
}

// Call with node = 1, tl = 0, tr = n - 1
void build(int node, int tl, int tr) {
    if (tl == tr) {
        tree[node].minimum = arr[tl];
        return;
    }
    int tm = (tl + tr) >> 1, left_node = node << 1, right_node = node << 1 | 1;
    build(left_node, tl, tm); // left node will be 2*node
    build(right_node, tm + 1, tr);  // right node will be 2*node+1

    tree[node].minimum = min(tree[left_node].minimum, tree[right_node].minimum);
    return;
}

// Call with node = 1 as segment tree array starts with 1.
int get_first_from_right(int node, int tl, int tr, int l, int r, int x) {
    if (tl > r || tr < l) return -1;
    if (tree[node].minimum > x) return -1;
    if (tl == tr) return tl;
    int tm = (tl + tr) >> 1, left_node = node << 1, right_node = node << 1 | 1;
    push(node);
    int right = get_first_from_right(right_node, tm + 1, tr, l , r, x);
    if (right != -1) return right;
    return get_first_from_right(left_node, tl, tm, l, r, x);
}

void update(int node, int tl, int tr, int l, int r, lli value) {
    if (l > r) return;
    if (l == tl && tr == r) {
        tree[node].minimum += value;
        tree[node].lazy_sum += value;
        return;
    }
    push(node);
    int tm = (tl + tr) >> 1, left_node = node << 1, right_node = node << 1 | 1;
    update(left_node, tl, tm, l, min(r, tm), value);
    update(right_node, tm + 1, tr, max(l, tm + 1), r, value);
    tree[node].minimum = min(tree[left_node].minimum, tree[right_node].minimum);
}

void push(int node) {
    int left_node = node << 1, right_node = node << 1 | 1;
    tree[left_node].minimum += tree[node].lazy_sum;
    tree[left_node].lazy_sum += tree[node].lazy_sum;
    tree[right_node].minimum += tree[node].lazy_sum;
    tree[right_node].lazy_sum += tree[node].lazy_sum;
    tree[node].lazy_sum = 0;
}
