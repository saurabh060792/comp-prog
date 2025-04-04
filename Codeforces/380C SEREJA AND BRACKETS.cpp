#include <iostream>

#define MAXARRAY 1000010
#define MAXTREE 2000020

using namespace std;
 
typedef long long int lli;

struct segment_tree_node {
    lli match, extra_open, extra_close;
};

void build_segment_tree();
segment_tree_node query(int l, int r);
segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node);

int n;
segment_tree_node tree[MAXTREE];

// https://codeforces.com/blog/entry/18051
int main() {
    int m, l, r;
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

    build_segment_tree();

    cin>>m;
    for (int i = 0; i < m; i++) {
        cin>>l>>r;
        segment_tree_node res = query(l-1, r-1);
        cout<<2 * res.match<<endl;
    }

    return 0;
}

void build_segment_tree() {
    for (int i = n - 1; i > 0; i--) tree[i] = combine(tree[i<<1],  tree[i<<1|1]);
}

// Query on interval [l, r]
segment_tree_node query(int l, int r) {
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

// Recursive Solution
// #include <iostream>

// #define MAXARRAY 1000010
// #define MAXTREE 4000010

// using namespace std;

// typedef long long int lli;

// struct segment_tree_node {
//     lli match = 0;
//     lli extra_open = 0;
//     lli extra_close = 0;
// };

// void buildST(int node, int tl, int tr);
// segment_tree_node queryST(int node, int tl, int tr, int l, int r);
// segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node);

// int n;
// segment_tree_node tree[MAXTREE], arr[MAXARRAY];

// int main() {
//     int m, l, r;
//     string s;
//     cin>>s;
//     n = s.size();
//     for (int i = 0; i < n; i++) {
//         arr[i].match = 0;
//         if (s[i] == '(') {
//             arr[i].extra_open = 1;
//             arr[i].extra_close = 0;
//         } else { 
//             arr[i].extra_open = 0;
//             arr[i].extra_close = 1;
//         }
//     }
 
//     buildST(1, 0, n - 1);
 
//     cin>>m;
//     for (int i = 0; i < m; i++) {
//         cin>>l>>r;
//         segment_tree_node res = queryST(1, 0, n - 1, l-1, r-1);
//         cout<<2 * res.match<<endl;
//     }
 
//     return 0;
// }

// segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node) {
//     segment_tree_node res;
//     lli extra_match =  min(left_node.extra_open, right_node.extra_close);
//     res.match = left_node.match + right_node.match + extra_match;
//     res.extra_open = left_node.extra_open + right_node.extra_open - extra_match;
//     res.extra_close = left_node.extra_close + right_node.extra_close - extra_match;
//     return res;
// }

// // Call with node = 1, tl = 0, tr = n - 1
// void buildST(int node, int tl, int tr) {
//     if(tl == tr) {
//         tree[node] = arr[tl];
//         return;
//     }
//     int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
//     buildST(left_node, tl, tm); // left node will be 2*node
//     buildST(right_node, tm + 1, tr);  // right node will be 2*node+1
//     tree[node] = combine(tree[left_node], tree[right_node]);
//     return;
// }

// segment_tree_node queryST(int node, int tl, int tr, int l, int r) {
//     if(l > tr || r < tl) return segment_tree_node();
//     if(l <= tl && r >= tr) return tree[node];
//     int tm = (tl + tr)>>1, left_node = node<<1, right_node = node<<1|1;
//     segment_tree_node resl, resr;
//     resl = queryST(left_node, tl, tm, l, r);
//     resr = queryST(right_node, tm + 1, tr, l, r);
//     return combine(resl, resr);
// }
