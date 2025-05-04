#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>

#define MAX 10010

using namespace std;

struct vertex {
    int entry_time, lowest_entry_time;
    bool visited;
};

int dfs(int u, int p, int time);
void find_articulation_points();

int n, m;
vertex V[MAX];
vector<int> graph[MAX];
set<int> articulation_points;

int main() {
    int u, v;
    while (scanf("%d%d", &n, &m) && (n || m)) {
        memset(V, 0, sizeof(V));
        for (int i = 0; i < MAX; i++) graph[i].clear();
        articulation_points.clear();
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        find_articulation_points();
        printf("%d\n", articulation_points.size());
    }
    return 0;
}

int dfs(int u, int p, int time) {
    V[u].visited = true;
    V[u].entry_time = time;
    V[u].lowest_entry_time = time;
    int children = 0;
    for (int v : graph[u]) {
        if (v == p) continue;
        if (V[v].visited) V[u].lowest_entry_time = min(V[u].lowest_entry_time, V[v].entry_time);
        else {
            time = dfs(v, u, time + 1);
            children++;
            V[u].lowest_entry_time = min(V[u].lowest_entry_time, V[v].lowest_entry_time);
            if (V[v].lowest_entry_time >= V[u].entry_time && p != -1) articulation_points.insert(u);
        }
    }
    if (p == -1 && children > 1) articulation_points.insert(u);
    return time;
}

void find_articulation_points() {
    for (int u = 1; u <= n; u++) if (!V[u].visited) dfs(u, -1, 0);
}
