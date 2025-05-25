#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
#include <climits>

#define MAX 200010

using namespace std;

typedef long long int lli;

void dfs(int u);

// Stores adjacent node and the edge index.
vector<pair<int, int>> graph[MAX];
vector<int> eulerian_path;
int n, m, degree[MAX];
bool visited_edge[MAX];

int main() {
    int u, v;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back({v, i});
        graph[v].push_back({u, i});
        degree[u]++;
        degree[v]++;
    }

    // An undirected graph has an Eulerian cycle if and only if
    // every vertex has even degree, and all of its vertices with
    // nonzero degree belong to a single connected component.
    for (int i = 1; i <= n; i++) {
        if (degree[i] % 2) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    dfs(1);

    if (eulerian_path.size() != m + 1) printf("IMPOSSIBLE\n");
    else for (int u : eulerian_path) printf("%d ", u);

    return 0;
}

// Hierholzer's algorithm
// https://en.wikipedia.org/wiki/Eulerian_path#Hierholzer's_algorithm
void dfs(int u) {
    while (!graph[u].empty()) {
        auto [v, idx] = graph[u].back();
        graph[u].pop_back();
        if (visited_edge[idx]) continue;
        visited_edge[idx] = true;
        dfs(v);
    }
    eulerian_path.push_back(u);
}
