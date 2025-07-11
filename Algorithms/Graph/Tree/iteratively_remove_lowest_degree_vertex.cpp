#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

#define MAX 4000006

typedef long long int lli;
typedef pair<int, int> pii;

struct vertex {
    int parent, degree;
    bool visited;
};

void dfs(int u, int p);

vertex V[MAX];
int n, m;
vector<int> tree[MAX];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    for (int i = 0; i < n; i++) V[i].parent = -1;
    for (int u = 0; u < n; u++) if (!V[u].visited) dfs(u, -1);

    priority_queue<pii, vector<pii>, greater<pii>> Q;
    for (int u = 0; u < n; u++) if (V[u].degree > 0) Q.push({V[u].degree, u});

    // Remove w vertices which has lowest degree after each removal.
    set<int> ans;
    while (w > 0) {
        u = Q.top().second;
        Q.pop();
        p = V[u].parent;
        if (p == -1) continue;
        ans.insert(u);
        Q.push({--V[p].degree, p});
        w--;
    }
    return 0;
}

void dfs(int u, int p) {
    int v, degree = 0;
    V[u].visited = true;
    for (auto i : tree[u]) {
        degree++;
        v = i.first;
        if (v == p) continue;
        V[v].parent = u;
        dfs(v, u);
    }
    V[u].degree = degree;
    return;
}
