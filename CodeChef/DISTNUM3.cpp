#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>

using namespace std;

#define MAX 400005
#define MAXLOG 20
#define MAXTWOTHIRD 700

typedef long long int lli;
typedef pair<lli, lli> pll;

struct vertex {
    int depth, parent, start_time, end_time;
};

struct query {
    int l, r, t, id, l_block, r_block, lc;
    int operator<(query q)const {
        return l_block != q.l_block ? l < q.l : (r_block != q.r_block ? r < q.r : t < q.t);
    }
};

void init(int n);
int dfs(int u, int p, int time);
void build_ancestor_table(vertex *V, int n);
int log2_floor(int n);
int lca(int x, int y);
void addOrRemove(int tree_idx);
void time_travel(int u_id, int q_id);
int compress(int x);

query Q[MAX];
pair<int, int> U[MAX];
vertex V[MAX];
vector<vector<int>> graph;
int ancestor[MAXLOG][MAX], arr[MAX], tree_id[MAX], ans[MAX], visited[MAX], hash_value[MAX], n, distinct, cc_index;
map<int, int> cc;

int main() {
    int x, q, q_type, u, v, w, l, r, t, q_id = 0, u_id = -1;
    scanf("%d%d", &n, &q);
    init(n);
    for (int i = 1; i <= n ; i++) {
        scanf("%d", &x);
        arr[i] = compress(x);
    }
    for (int i = 0; i < n - 1; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, 0, 1);
    build_ancestor_table(V, n);

    for (int i = 0; i < q; i++) {
        scanf("%d", &q_type);
        if (q_type == 1) {
            scanf("%d%d", &u, &v);
            Q[q_id].lc = lca(u, v);
            if (V[u].start_time > V[v].start_time) swap(u, v);
            if (Q[q_id].lc == u) {
                Q[q_id].l = V[u].start_time;
                Q[q_id].r = V[v].start_time;
            } else {
                Q[q_id].l = V[u].end_time;
                Q[q_id].r = V[v].start_time;
            }
            Q[q_id].t = u_id;
            Q[q_id].id = q_id;
            Q[q_id].l_block = Q[q_id].l / MAXTWOTHIRD;
            Q[q_id].r_block = Q[q_id].r / MAXTWOTHIRD;
            q_id++;
        } else {
            scanf("%d%d", &u, &x);
            U[++u_id] = {u, compress(x)};

        }
    }

    sort(Q, Q + q_id);
    l = 0, r = -1, t = -1;
    for (int i = 0; i < q_id; i++) {
        while (r < Q[i].r) addOrRemove(tree_id[++r]);
        while (l > Q[i].l) addOrRemove(tree_id[--l]);
        while (l < Q[i].l) addOrRemove(tree_id[l++]);
        while (r > Q[i].r) addOrRemove(tree_id[r--]);
        while (t < Q[i].t) time_travel(++t, i);
        while (t > Q[i].t) time_travel(t--, i);

        u = tree_id[l];
        v = tree_id[r];
        if (Q[i].lc != u && Q[i].lc != v) {
            addOrRemove(Q[i].lc);
            ans[Q[i].id] = distinct;
            addOrRemove(Q[i].lc);
        } else {
            ans[Q[i].id] = distinct;
        }
    }
    for (int i = 0; i < q_id; i++) printf("%d\n", ans[i]);

    return 0;
}

void init(int n) {
    cc_index = 1;
    distinct = 0;
    cc.clear();
    graph.clear();
    graph.resize(n + 10);
}

int compress(int x) {
    if (!cc[x]) cc[x] = cc_index++;
    return cc[x];
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

// u_id = update id first unapplied update
// q_id = query id
void time_travel(int u_id, int q_id) {
    if (visited[U[u_id].first]) {
        addOrRemove(U[u_id].first);
        swap(U[u_id].second, arr[U[u_id].first]);
        addOrRemove(U[u_id].first);
    } else {
        swap(U[u_id].second, arr[U[u_id].first]);
    }
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
