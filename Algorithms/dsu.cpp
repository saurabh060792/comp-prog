#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;

// Normal DSU
// struct dsu {
//     vector<int> parent, size;

//     dsu(int n) {
//         parent.resize(n);
//         for (int i = 0; i < n; i++) parent[i] = i;
//         size.resize(n, 0);
//     }

//     void union_sets(int u, int v) {
//         int pu, pv;
//         pu = find_set(u);
//         pv = find_set(v);
//         if (pu == pv) return;
//         if (size[pu] < size[pv]) swap(pu, pv);
//         parent[pv] = pu;
//         size[pu] += size[pv];
//         return;
//     }

//     int find_set(int v) {
//         if (v == parent[v]) return v;
//         return parent[v] = find_set(parent[v]);
//     }
// };

// DSU with extra data
struct dsu {
    vector<int> parent, size, minimum, maximum;

    dsu(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
        size.resize(n, 0);
        minimum.resize(n, INT_MAX);
        maximum.resize(n, INT_MIN);
    }

    void union_sets(int u, int v, int w) {
        int pu, pv;
        pu = find_set(u);
        pv = find_set(v);
        if (pu == pv) {
            minimum[pu] = min(minimum[pu], w);
            maximum[pu] = max(maximum[pu], w);
            return;
        }
        if (size[pu] < size[pv]) swap(pu, pv);
        minimum[pu] = min(min(minimum[pu], minimum[pv]), w);
        maximum[pu] = max(max(maximum[pu], maximum[pv]), w);
        parent[pv] = pu;
        size[pu] += size[pv];
        return;
    }

    int find_set(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    }
};

void solve();

// https://codeforces.com/contest/2117/problem/G
int main() {
    lli t;
    scanf("%lld", &t);
    while (t--) solve();
    return 0;
}

void solve() {
    int s, t, u, v, w, n, m, ans = INT_MAX;
    scanf("%d%d", &n, &m);
    vector<pair<int, pair<int, int>>> edges;
    dsu d(n + 10);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        edges.push_back({w, {u, v}});
    }
    sort(edges.begin(), edges.end());
    // for (auto i : edges) printf("%d %d %d\n", i.second.first, i.second.second, i.first);

    for (auto i : edges) {
        u = i.second.first;
        v = i.second.second;
        w = i.first;
        d.union_sets(u, v, w);
        s = d.find_set(1);
        t = d.find_set(n);
        if (s == t) ans = min(ans, d.minimum[s] + d.maximum[s]);
    }
    printf("%d\n", ans);
}
