#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

#define MAX 100010

using namespace std;

struct vertex {
    // Number of edges going over this vertex and its parent
    int depth, num_edges_going_over;
    bool visited;
};

void bridge(int u, int v);
int dfs(int u, int p, int time);
void find_bridges();

int n, m;
vertex V[MAX];
vector<int> graph[MAX];
vector<pair<int, int>> critical_edges;

int main() {
    int t, u, v;
    scanf("%d", &t);
    for (int test_case = 1; test_case <= t; test_case++) {
        scanf("%d%d", &n, &m);
        memset(V, 0, sizeof(V));
        critical_edges.clear();
        for (int i = 0; i <= n; i++) graph[i].clear();
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

void dfs(int u, int p) {
    V[u].visited = true;
    for (int v : graph[u]) {
        if (v == p) continue;
        if (V[v].visited) {
            // If v is below u, then this back edge is already counted
            // in line 74 because there we added number of edges going
            // over v and its parent and it can happen that some of those
            // edges just went up till u but never over (u, p) edge. So we
            // got to subtract them.
            if (V[v].depth > V[u].depth) V[u].num_edges_going_over--;
            else V[u].num_edges_going_over++;
        }
        else {
            V[v].depth = V[u].depth + 1;
            dfs(v, u);
            // Number of edges going over u and its parent is equal to
            // number of edges going over v and its parent (ie u) but 
            // we will be over counting because some of the edges that
            // are passing over edge (v, u) will end exactly at u. So we
            // got to subtract them. And we are doing exactly that in 
            // line 60. We are detecting those edges which are passing 
            // over (v, u) but ending at u as back edges that are going
            // down from u.
            V[u].num_edges_going_over += V[v].num_edges_going_over;
        }
    }

    // Bridges will be edges where there is no edge passing over
    // (u, p). And of course we have to ignore root.
    if (V[u].num_edges_going_over == 0 && p != -1) bridge(u, p);
    return;
}

void find_bridges() {
    for (int i = 1; i <= n; i++) if (!V[i].visited) dfs(i, -1);
}

void bridge(int u, int v) {
    if (u > v) swap(u, v);
    critical_edges.push_back({u, v});
}
