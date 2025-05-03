#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

#define MAX 1010

using namespace std;

void bridge(int u, int v);
void dfs(int u, int p, int time);
void find_bridges();

int n;
vector<bool> visited;
vector<vector<int>> graph;
vector<int> entry_time, lowest_entry_time;
vector<pair<int, int>> critical_edges;

int main() {
    int u, v, degree;
    char ch;
    while (scanf("%d", &n) != EOF) {
        graph.clear();
        graph.resize(n);
        for (int i = 0; i < n; i++) {
            scanf("%d %c%d%c ", &u, &ch, &degree, &ch);
            for (int j = 0; j < degree; j++) {
                scanf("%d", &v);
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
        }
        find_bridges();
        sort(critical_edges.begin(), critical_edges.end());
        printf("%d critical links\n", critical_edges.size());
        for (int i = 0; i < critical_edges.size(); i++)
            printf("%d - %d\n", critical_edges[i].first, critical_edges[i].second);
        printf("\n");
    }
    return 0;
}

void dfs(int u, int p, int time) {
    visited[u] = true;
    entry_time[u] = time;

    
    lowest_entry_time[u] = time;
    for (int v : graph[u]) {
        if (v == p) continue;
        // Back edge
        if (visited[v]) lowest_entry_time[u] = min(lowest_entry_time[u], entry_time[v]);
        // Tree edge
        else {
            dfs(v, u, time + 1);
            lowest_entry_time[u] = min(lowest_entry_time[u], lowest_entry_time[v]);
            if (lowest_entry_time[v] > entry_time[u]) bridge(u, v);
        }
    }
}

void find_bridges() {
    critical_edges.clear();
    visited.assign(n, false);
    entry_time.assign(n, -1);
    lowest_entry_time.assign(n, -1);
    for (int i = 0; i < n; i++) if (!visited[i]) dfs(i, -1, 0);
}

void bridge(int u, int v) {
    if (u > v) swap(u, v);
    critical_edges.push_back({u, v});
}