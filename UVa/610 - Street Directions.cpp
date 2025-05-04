#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

#define MAX 1010

using namespace std;

int dfs(int u, int p, int time);
void find_bridges();

int n, m;
vector<bool> visited;
vector<vector<int>> graph, modified_graph;
vector<int> entry_time, lowest_entry_time;

int main() {
    int test_case = 1, u, v;
    while (scanf("%d%d", &n, &m) && (n || m)) {
        graph.clear();
        modified_graph.clear();
        graph.resize(n + 1);
        modified_graph.resize(n + 1);
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        find_bridges();

        printf("%d\n\n", test_case++);
        for (int u = 1; u <= n; u++)
            for (int v : modified_graph[u])
                printf("%d %d\n", u, v);
        printf("#");
    }
    return 0;
}

int dfs(int u, int p, int time) {
    visited[u] = true;
    entry_time[u] = time;
    lowest_entry_time[u] = time;
    for (int v : graph[u]) {
        if (v == p) continue;

        // Back edge
        if (visited[v]) {
            lowest_entry_time[u] = min(lowest_entry_time[u], entry_time[v]);
            if (entry_time[u] > entry_time[v]) modified_graph[u].push_back(v);
        }
        // Tree edge
        else {
            time = dfs(v, u, time + 1);
            lowest_entry_time[u] = min(lowest_entry_time[u], lowest_entry_time[v]);
            modified_graph[u].push_back(v);
            if (lowest_entry_time[v] > entry_time[u]) modified_graph[v].push_back(u);
        }
    }
    return time;
}

void find_bridges() {
    visited.assign(n + 1, false);
    entry_time.assign(n + 1, -1);
    lowest_entry_time.assign(n + 1, -1);
    for (int i = 1; i <= n; i++) if (!visited[i]) dfs(i, -1, 0);
}
