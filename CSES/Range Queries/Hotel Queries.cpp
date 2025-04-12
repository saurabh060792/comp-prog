#include <iostream>
#include<vector>
#include <algorithm>
#include <set>

#define MAXARRAY 200010
#define MAXTREE 800010

using namespace std;

typedef long long int lli;

struct segment_tree_node {
    int maximum;
};

void build(int node, int tl, int tr);
int get_first(int node, int tl, int tr, int l, int r, int x);
void update(int node, int tl, int tr, int pos, int new_val);

int arr[MAXARRAY];
segment_tree_node tree[MAXTREE];

int main() {
    int n, q, k;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    
    build(1, 0, n - 1);

    for (int i = 0; i < q; i++) {
        scanf("%d", &k);
        int first_position = get_first(1, 0, n - 1, 0, n - 1, k);
        if (first_position == -1) printf("0 ");
        else {
            printf("%d ", first_position + 1);
            arr[first_position] -= k;
            update(1, 0, n - 1, first_position, arr[first_position]);
        }
    }
    printf("\n");
    return 0;
}

// Call with node = 1, tl = 0, tr = n - 1
void build(int node, int tl, int tr) {
    if (tl == tr) {
        tree[node].maximum = arr[tl];
        return;
    }
    int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
    build(left_node, tl, tm); // left node will be 2*node
    build(right_node, tm + 1, tr);  // right node will be 2*node+1
    tree[node].maximum = max(tree[left_node].maximum, tree[right_node].maximum);
}

int get_first(int node, int tl, int tr, int l, int r, int x) {
    if(tl > r || tr < l) return -1;
    if(tree[node].maximum < x) return -1;
    if (tl == tr) return tl;
    int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
    int left = get_first(left_node, tl, tm, l, r, x);
    if(left != -1) return left;
    return get_first(right_node, tm + 1, tr, l ,r, x);
}

void update(int node, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        tree[node].maximum = new_val;
        return;
    }
    int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
    if (pos <= tm) update(left_node, tl, tm, pos, new_val);
    else update(right_node, tm + 1, tr, pos, new_val);
    tree[node].maximum = max(tree[left_node].maximum, tree[right_node].maximum);
}
