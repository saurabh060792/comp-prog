#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>

using namespace std;

#define MAX 400005

typedef long long int lli;
typedef pair<lli, lli> pll;

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

pair<lli, pair<int, int>> edges[MAX];
bool present_in_mst[MAX];
int n, m;

int main() {
    int u, v;
    lli w;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m ; i++) {
        scanf("%d%d%lld", &u, &v, &w);
        edges[i] = {w, {u, v}};
    }
    return 0;
}

lli kruskal() {
    lli w = 0;
    int u, v;
    sort(edges, edges + m);
    dsu d(n + 10);
    for (int i = 0; i < m; i++) {
        u = d.find_set(edges[i].second.first);
        v = d.find_set(edges[i].second.second);
        if (u != v) {
            d.union_sets(u, v);
            w += edges[i].first;
            present_in_mst[i] = true;
        }
    }
    return w;
}
