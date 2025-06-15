#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>

using namespace std;

#define MAX 200005
#define MAXLOG 20
#define MAXSQRT 400

typedef long long int lli;
typedef pair<lli, lli> pll;

struct vertex {
    int depth, parent, start_time, end_time;
};

struct query {
    int l, r, block, id, lc;
    int operator<(query q)const {
        if (block != q.block) return block < q.block;
        return (block & 1) ? (r < q.r) : (r > q.r);
    }
};

void init(int n);
int dfs(int u, int p, int time);
void build_ancestor_table(vertex *V, int n);
int log2_floor(int n);
int lca(int x, int y);
void addOrRemove(int tree_idx);

query Q[MAX];
vertex V[MAX];
vector<vector<int>> graph;
vector<int> visited, hash_value;
int ancestor[MAXLOG][MAX], arr[MAX], tree_id[MAX], ans[MAX], n, distinct, cc_index;
map<lli, int> cc;

// https://www.spoj.com/problems/COT2/
// https://codeforces.com/blog/entry/43230
int main() {
    lli x;
    int q, u, v, w, l, r;
    while (scanf("%d%d", &n, &q) != EOF) {
        init(n);
        for (int i = 1; i <= n ; i++) {
            scanf("%lld", &x);
            if (!cc.count(x)) cc[x] = cc_index++;
            arr[i] = cc[x];
        }
        for (int i = 0; i < n - 1; i++) {
            scanf("%d%d", &u, &v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        dfs(1, 0, 1);
        build_ancestor_table(V, n);

        // We will create an array based on vertex's start and end time.
        //         (1)
        //      /   |   \ 
        //    (2)  (3)    (4)
        //       /  |  \   |
        //    (5) (6) (7) (8)
        //
        // time    : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
        // tree_id : 1 2 2 3 5 5 6 6 7  7  3  4  8  8  4  1 
        // weight  : 4 2 2 9 8 8 5 5 7  7  9  3  7  7  3  4
        //
        // Query's l & r will vary over time and we will keep a visited array
        // over tree_id to ignore vertex that not on the path. Refer blog. And
        // hash_value for weight array to answer the query.
        for (int i = 0; i < q; i++) {
            scanf("%d%d", &u, &v);
            Q[i].lc = lca(u, v);
            if (V[u].start_time > V[v].start_time) swap(u, v);
            if (Q[i].lc == u) {
                Q[i].l = V[u].start_time;
                Q[i].r = V[v].start_time;
            } else {
                Q[i].l = V[u].end_time;
                Q[i].r = V[v].start_time;
            }
            Q[i].id = i;
            Q[i].block = Q[i].l / MAXSQRT;
        }
        sort(Q, Q + q);
        l = Q[0].l, r = Q[0].l - 1;
        for (int i = 0; i < q; i++) {
            while (r < Q[i].r) addOrRemove(tree_id[++r]);
            while (l > Q[i].l) addOrRemove(tree_id[--l]);
            while (l < Q[i].l) addOrRemove(tree_id[l++]);
            while (r > Q[i].r) addOrRemove(tree_id[r--]);

            u = tree_id[l];
            v = tree_id[r];
            if (Q[i].lc != u && Q[i].lc != v) {
                addOrRemove(Q[i].lc);
                ans[Q[i].id] = distinct;
                // Remove the extra LCA for the next iteration.
                addOrRemove(Q[i].lc);
            } else {
                ans[Q[i].id] = distinct;
            }
        }
        for (int i = 0; i < q; i++) printf("%d\n", ans[i]);
    }

    return 0;
}

void init(int n) {
    cc_index = distinct = 0;
    cc.clear();
    graph.clear();
    graph.resize(n + 10);
    visited.clear();
    visited.resize(n + 10);
    hash_value.clear();
    hash_value.resize(n + 10);
    for (int i = 0; i < MAXLOG; i++) for (int j = 0; j < n + 10; j++) ancestor[i][j] = 0;
}

// tree_idx is the id of the vertex of tree in range [1, n].
void addOrRemove(int tree_idx) {
    if (!visited[tree_idx]) {
        hash_value[arr[tree_idx]]++;
        if (hash_value[arr[tree_idx]] == 1) distinct++;
    } else {
        hash_value[arr[tree_idx]]--;
        if (hash_value[arr[tree_idx]] == 0) distinct--;
    }
    visited[tree_idx] ^= 1;
}

int dfs(int u, int p, int time) {
    V[u].start_time = time;
    tree_id[time] = u;
    for (int v : graph[u])
        if (v != p) {
            V[v].parent = u;
            V[v].depth = V[u].depth + 1;
            time = dfs(v, u, time + 1);
        }
    V[u].end_time = ++time;
    tree_id[time] = u;
    return time;
}

void build_ancestor_table(vertex *V, int n) {
    int k = log2_floor(n);
    for (int i = 2; i <= n; i++) ancestor[0][i] = V[i].parent;
    for (int i = 1; i <= k; i++)
        for (int j = 2; j <= n; j++)
            ancestor[i][j] = ancestor[i - 1][ancestor[i - 1][j]];
}

int log2_floor(int n) {
    return n ? __builtin_clzll(1) - __builtin_clzll(n) : -1;
}

int lca(int x, int y) {
    int k;
    if (V[x].depth < V[y].depth) swap(x, y);
    k = log2_floor(V[x].depth - V[y].depth);
    for (int i = k; i >= 0; i--)
        if (V[x].depth - (1 << i) >= V[y].depth)
            x = ancestor[i][x];
    if (x == y) return x;
    k = log2_floor(V[x].depth);
    for (int i = k; i >= 0; i--) {
        if (ancestor[i][x] != ancestor[i][y]) {
            x = ancestor[i][x];
            y = ancestor[i][y];
        }
    }
    return ancestor[0][x];
}
