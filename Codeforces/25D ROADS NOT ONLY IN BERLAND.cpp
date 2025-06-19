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

vector<pair<int, int>> edges;
vector<int> components;

int main() {
    int n, u, v, pu, pv;
    scanf("%d", &n);
    dsu d(n + 10);
    for (int i = 0; i < n - 1; i ++) {
        scanf("%d%d", &u, &v);
        if (u > v) swap(u, v);
        pu = d.find_set(u);
        pv = d.find_set(v);
        if (pu == pv) edges.push_back({u, v});
        else d.union_sets(u, v);
    }


    for (int i = 1; i <= n; i++) if (d.parent[i] == i) components.push_back(i);

    printf("%d\n", components.size() - 1);
    for (int i = 0; i < components.size() - 1; i++) {
        pair<int, int> e = edges.back();
        edges.pop_back();
        printf("%d %d %d %d\n", e.first, e.second, components[i], components[i + 1]);
    }
    return 0;
}
