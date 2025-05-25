#include <iostream>
#include <vector>

#define MAX 200010

using namespace std;

typedef long long int lli;

void dfs(int u);

vector<int> graph[MAX];
vector<int> eulerian_path;
int n, m, in_degree[MAX], out_degree[MAX];

int main() {
    int u, v;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        in_degree[v]++;
        out_degree[u]++;
    }

    bool possible = true;
    for (int i = 2; i < n; i++) {
        if (in_degree[i] != out_degree[i]) {
            possible = false;
            break;
        }
    }
    if (out_degree[1] != in_degree[1] + 1 || out_degree[n] != in_degree[n] - 1 || !possible) {
        printf("IMPOSSIBLE\n");
        return 0;
    }

    dfs(1);

    reverse(eulerian_path.begin(), eulerian_path.end());
    if (eulerian_path.size() != m + 1 || eulerian_path.back() != n) printf("IMPOSSIBLE\n");
    else for (int u : eulerian_path) printf("%d ", u);

    return 0;
}

// Hierholzer's algorithm
// https://en.wikipedia.org/wiki/Eulerian_path#Hierholzer's_algorithm
void dfs(int u) {
    while (!graph[u].empty()) {
        int v = graph[u].back();
        graph[u].pop_back();
        // Visited edges is not needed in directed graph as we
        // removing edges
        dfs(v);
    }
    eulerian_path.push_back(u);
}
