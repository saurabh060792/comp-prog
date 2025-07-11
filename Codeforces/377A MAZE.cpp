#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

#define MAX 4000006
#define MAX_SIDE 502

typedef long long int lli;
typedef pair<int, int> pii;

struct vertex {
    int parent, degree;
    bool visited;
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
int n, m, x[4] = {1, 0, -1, 0}, y[4] = {0, 1, 0, -1};
vector<pair<int, lli>> mst[MAX];
char grid[MAX_SIDE][MAX_SIDE];

// We dont have to create MST. Any DFS or BSF traversal
// would suffice.
int main() {
    int r, c, w, u, v, a, b, deg, p;
    scanf("%d%d%d", &r, &c, &w);
    n = r * c;
    for (int i = 0; i < r ; i++) scanf("%s", grid[i]);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            u = i * c + j;
            if (grid[i][j] == '#') continue;
            for (int k = 0; k < 4; k++) {
                a = i + x[k];
                b = j + y[k];
                if (a >= 0 && a < r && b >= 0 && b < c) {
                    v = a * c + b;
                    if (grid[a][b] == '#') continue;
                    edges[m++] = {1, u, v, u};
                }
            }
        }
    }

    kruskal();

    for (int i = 0; i < r * c; i++) V[i].parent = -1;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            u = i * c + j;
            if (!V[u].visited) dfs(u, -1);
        }
    }

    priority_queue<pii, vector<pii>, greater<pii>> Q;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            u = i * c + j;
            if (V[u].degree > 0) Q.push({V[u].degree, u});
        }
    }

    set<pair<int, int>> ans;
    while (w > 0) {
        u = Q.top().second;
        Q.pop();
        p = V[u].parent;
        if (p == -1) continue;
        ans.insert({u / c, u % c});
        Q.push({--V[p].degree, p});
        w--;
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (ans.count({i, j})) printf("X");
            else printf("%c", grid[i][j]);
        }
        printf("\n");
    }


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
    int v, degree = 0;
    V[u].visited = true;
    for (auto i : mst[u]) {
        degree++;
        v = i.first;
        if (v == p) continue;
        V[v].parent = u;
        dfs(v, u);
    }
    V[u].degree = degree;
    return;
}
