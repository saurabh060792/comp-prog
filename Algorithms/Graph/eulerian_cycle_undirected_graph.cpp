#include <iostream>
#include <vector>

#define MAX 200010

using namespace std;

typedef long long int lli;

void dfs(int u);

// Stores adjacent node and the edge index.
vector<pair<int, int>> graph[MAX];
vector<int> eulerian_cycle;
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

    if (eulerian_cycle.size() != m + 1) printf("IMPOSSIBLE\n");
    else for (int u : eulerian_cycle) printf("%d ", u);

    return 0;
}

// Hierholzer's algorithm
// https://en.wikipedia.org/wiki/eulerian_cycle#Hierholzer's_algorithm
void dfs(int u) {
    while (!graph[u].empty()) {
        auto [v, idx] = graph[u].back();
        graph[u].pop_back();
        // Visited edges is needed in undirected graph case
        // becuase even though we removed the v from u's
        // adjacency list, u will still be there in v's
        // adjacency list.
        if (visited_edge[idx]) continue;
        visited_edge[idx] = true;
        dfs(v);
    }
    eulerian_cycle.push_back(u);
}
