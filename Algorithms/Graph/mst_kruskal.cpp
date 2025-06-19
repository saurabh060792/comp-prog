#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>

using namespace std;

#define MAX 400005
#define MAXLOG 20

typedef long long int lli;
typedef pair<lli, lli> pll;

struct vertex {
    int parent, depth;
    lli up_weight;  // weight from this node to is parent.
};

struct edge {
    lli w;
    int u, v, id;
    bool operator<(const struct edge& e) { return w < e.w; }
};

struct dsu {
    vector<int> parent, size;

    dsu(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
        size.resize(n, 0);
    }

    void union_sets(int u, int v) {
        int pu, pv;
        pu = find_set(u);
        pv = find_set(v);
        if (pu == pv) return;
        if (size[pu] < size[pv]) swap(pu, pv);
        parent[pv] = pu;
        size[pu] += size[pv];
        return;
    }

    int find_set(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    }
};

lli kruskal();
void dfs(int u, int p);

vertex V[MAX];
edge edges[MAX];
bool present_in_mst[MAX];
int n, m;
vector<pair<int, lli>> mst[MAX];

int main() {
    int u, v, l;
    lli w, mst_w;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m ; i++) {
        scanf("%d%d%lld", &u, &v, &w);
        edges[i] = {w, u, v, i};
    }

    mst_w = kruskal();
    dfs(1, 0);

    return 0;
}

lli kruskal() {
    lli w = 0;
    int u, v, pu, pv, id;
    sort(edges, edges + m);
    dsu d(n + 10);
    for (int i = 0; i < m; i++) {
        u = edges[i].u;
        v = edges[i].v;
        pu = d.find_set(u);
        pv = d.find_set(v);
        if (pu != pv) {
            d.union_sets(pu, pv);
            w += edges[i].w;
            id = edges[i].id;
            present_in_mst[id] = true;
            mst[u].push_back({v, edges[i].w});
            mst[v].push_back({u, edges[i].w});
        }
    }
    return w;
}

void dfs(int u, int p) {
    int v;
    lli w;
    for (auto i : mst[u]) {
        v = i.first;
        w = i.second;
        if (v == p) continue;
        V[v].depth = V[u].depth + 1;
        V[v].parent = u;
        V[v].up_weight = w;
        dfs(v, u);
    }
    return;
}
