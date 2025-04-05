#include <iostream>

#define MAXARRAY 1010
#define MAXTREE 4010

using namespace std;

typedef long long int lli;

struct segment_tree_node {
    lli value;
};

void build_x(int m, int nodex, int lx, int rx);
void build_y(int nodex, int lx, int rx, int nodey, int ly, int ry);
segment_tree_node query_x(int m, int nodex, int tlx, int trx, int lx, int rx, int ly, int ry);
segment_tree_node query_y(int nodex, int nodey, int tly, int try_, int ly, int ry);
void update_x(int m, int nodex, int lx, int rx, int x, int y, lli new_val);
void update_y(int nodex, int lx, int rx, int nodey, int ly, int ry, int x, int y, lli new_val);
segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node);

segment_tree_node tree[MAXTREE][MAXTREE];
lli arr[MAXARRAY][MAXARRAY];

int main() {
    int n, q, x1, x2, y1, y2, q_type;
    string s;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
        cin>>s;
        for (int j = 0; j < n; j++) {
            if (s[j] == '.') arr[i][j] = 0;
            else arr[i][j] = 1;
        }
    }

    build_x(n, 1, 0, n - 1);

    for (int i = 0; i < q; i++) {
        scanf("%d", &q_type);
        if (q_type == 1) {
            scanf("%d%d", &y1, &x1);
            y1--;
            x1--;
            lli new_val = arr[y1][x1] == 0 ? 1 : 0;
            arr[y1][x1] = new_val;
            update_x(n, 1, 0, n - 1, y1, x1, new_val);
        } else {
            scanf("%d%d%d%d", &y1, &x1, &y2, &x2);
            segment_tree_node res = query_x(n, 1, 0, n - 1, y1 - 1, y2 - 1, x1 - 1, x2 - 1);
            printf("%lld\n", res.value);
        }
    }

    return 0;
}

// Call with node = 1, tl = 0, tr = n - 1
void build_x(int m, int nodex, int lx, int rx) {
    if (lx != rx) {
        int mx = (lx + rx)>>1, left_nodex = nodex<<1, right_nodex = nodex<<1|1;
        build_x(m, left_nodex, lx, mx);
        build_x(m, right_nodex, mx+1, rx);
    }
    build_y(nodex, lx, rx, 1, 0, m-1);
}

void build_y(int nodex, int lx, int rx, int nodey, int ly, int ry) {
    if (ly == ry) {
        int left_nodex = nodex<<1, right_nodex = nodex<<1|1;
        if (lx == rx) tree[nodex][nodey].value = arr[lx][ly];
        else tree[nodex][nodey].value = tree[left_nodex][nodey].value + tree[right_nodex][nodey].value;
        return;
    }
    int my = (ly + ry)>>1, left_nodey = nodey<<1, right_nodey = nodey<<1|1;
    build_y(nodex, lx, rx, left_nodey, ly, my);
    build_y(nodex, lx, rx, right_nodey, my + 1, ry);
    tree[nodex][nodey] = combine(tree[nodex][left_nodey], tree[nodex][right_nodey]);
}

segment_tree_node query_x(int m, int nodex, int tlx, int trx, int lx, int rx, int ly, int ry) {
    if (lx > rx) return {0};
    if (lx == tlx && trx == rx) return query_y(nodex, 1, 0, m-1, ly, ry);
    int tmx = (tlx + trx)>>1, left_nodex = nodex<<1, right_nodex = nodex<<1|1;
    segment_tree_node resl = query_x(m, left_nodex, tlx, tmx, lx, min(rx, tmx), ly, ry);
    segment_tree_node resr = query_x(m, right_nodex, tmx + 1, trx, max(lx, tmx + 1), rx, ly, ry);
    return combine(resl, resr);
}

segment_tree_node query_y(int nodex, int nodey, int tly, int try_, int ly, int ry) {
    if (ly > ry) return {0};
    if (ly == tly && try_ == ry) return tree[nodex][nodey];
    int tmy = (tly + try_)>>1, left_nodey = nodey<<1, right_nodey = nodey<<1|1;
    segment_tree_node resl = query_y(nodex, left_nodey, tly, tmy, ly, min(ry, tmy));
    segment_tree_node resr = query_y(nodex, right_nodey, tmy + 1, try_, max(ly, tmy + 1), ry);
    return combine(resl, resr);
}

void update_x(int m, int nodex, int lx, int rx, int x, int y, lli new_val) {
    if (lx != rx) {
        int mx = (lx + rx)>>1, left_nodex = nodex<<1, right_nodex = nodex<<1|1;
        if (x <= mx) update_x(m, left_nodex, lx, mx, x, y, new_val);
        else update_x(m, right_nodex, mx + 1, rx, x, y, new_val);
    }
    update_y(nodex, lx, rx, 1, 0, m - 1, x, y, new_val);
}

void update_y(int nodex, int lx, int rx, int nodey, int ly, int ry, int x, int y, lli new_val) {
    if (ly == ry) {
        int left_nodex = nodex<<1, right_nodex = nodex<<1|1;
        if (lx == rx) tree[nodex][nodey].value = new_val;
        else tree[nodex][nodey] = combine(tree[left_nodex][nodey], tree[right_nodex][nodey]);
        return;
    }
    int my = (ly + ry)>>1, left_nodey = nodey<<1, right_nodey = nodey<<1|1;
    if (y <= my) update_y(nodex, lx, rx, left_nodey, ly, my, x, y, new_val);
    else update_y(nodex, lx, rx, right_nodey, my + 1, ry, x, y, new_val);
    tree[nodex][nodey] = combine(tree[nodex][left_nodey], tree[nodex][right_nodey]);
}

segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node) {
    segment_tree_node res;
    res.value = left_node.value + right_node.value;
    return res;
}