#include <iostream>

#define MAXARRAY 1000010
#define MAXTREE 2000020

using namespace std;
 
typedef long long int lli;

struct segment_tree_node {
    lli match, extra_open, extra_close;
};

void build(int n);
segment_tree_node query(int n, int l, int r);
segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node);

segment_tree_node tree[MAXTREE];

// https://codeforces.com/blog/entry/18051
// Solution to 380C SEREJA AND BRACKETS (https://codeforces.com/problemset/problem/380/C)
int main() {
    int n, m, l, r;
    string s;
    cin>>s;
    n = s.size();
    for (int i = 0; i < n; i++) {
        tree[n+i].match = 0;
        if (s[i] == '(') {
            tree[n+i].extra_open = 1;
            tree[n+i].extra_close = 0;
        } else { 
            tree[n+i].extra_open = 0;
            tree[n+i].extra_close = 1;
        }
    }

    build(n);

    cin>>m;
    for (int i = 0; i < m; i++) {
        cin>>l>>r;
        segment_tree_node res = query(n, l-1, r-1);
        cout<<2 * res.match<<endl;
    }

    return 0;
}

void build(int n) {
    for (int i = n - 1; i > 0; i--) tree[i] = combine(tree[i<<1],  tree[i<<1|1]);
}

// Query on interval [l, r]
segment_tree_node query(int n, int l, int r) {
    segment_tree_node resl = {0, 0, 0}, resr = {0, 0, 0};
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
    lli extra_match =  min(left_node.extra_open, right_node.extra_close);
    res.match = left_node.match + right_node.match + extra_match;
    res.extra_open = left_node.extra_open + right_node.extra_open - extra_match;
    res.extra_close = left_node.extra_close + right_node.extra_close - extra_match;
    return res;
}
