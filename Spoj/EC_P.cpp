#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

void bridge(int u, int v);
int dfs(int u, int p, int time);
void find_bridges();

int n, m;
vector<bool> visited;
vector<vector<int>> graph;
vector<int> entry_time, lowest_entry_time;
vector<pair<int, int>> critical_edges;

int main() {
    int t, u, v, degree;
    scanf("%d", &t);
    for (int test_case = 1; test_case <= t; test_case++) {
        scanf("%d%d", &n, &m);
        graph.clear();
        graph.resize(n + 1);
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        find_bridges();
        sort(critical_edges.begin(), critical_edges.end());
        printf("Caso #%d\n", test_case);
        if (critical_edges.size() > 0) printf("%d\n", critical_edges.size());
        else printf("Sin bloqueos\n");
        for (int i = 0; i < critical_edges.size(); i++)
            printf("%d %d\n", critical_edges[i].first, critical_edges[i].second);
    }
    return 0;
}

int dfs(int u, int p, int time) {
    visited[u] = true;
    entry_time[u] = time;
    lowest_entry_time[u] = time;
    for (int v : graph[u]) {
        if (v == p) continue;

        if (visited[v]) lowest_entry_time[u] = min(lowest_entry_time[u], entry_time[v]);
        else {
            time = dfs(v, u, time + 1);
            lowest_entry_time[u] = min(lowest_entry_time[u], lowest_entry_time[v]);
            if (lowest_entry_time[v] > entry_time[u]) bridge(u, v);
        }
    }
    return time;
}

void find_bridges() {
    critical_edges.clear();
    visited.assign(n + 1, false);
    entry_time.assign(n + 1, -1);
    lowest_entry_time.assign(n + 1, -1);
    for (int i = 1; i <= n; i++) if (!visited[i]) dfs(i, -1, 0);
}

void bridge(int u, int v) {
    if (u > v) swap(u, v);
    critical_edges.push_back({u, v});
}
