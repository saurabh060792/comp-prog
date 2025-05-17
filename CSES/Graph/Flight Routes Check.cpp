#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

#define MAX 1000050

using namespace std;

typedef long long int lli;

struct vertex {
    int comp_id;
    bool visited;
};

int strongly_connected_components();
void dfs(int u, vector<int> *graph, vector<int> &output);
void path(int u, int t);

vertex V[MAX];
vector<int> graph[MAX], graph_t[MAX], condensation_graph[MAX];
vector<vector<int>> components;
int n, m, condensation_n;

int main() {
    int u, v;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= m; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
    }
    condensation_n = strongly_connected_components();

    if (condensation_n == 1) printf("YES\n");
    else printf("NO\n%d %d\n", components[1][0], components[0][0]);
    return 0;
}

void dfs(int u, vector<int> *graph, vector<int> &output) {
    V[u].visited = true;
    for (int v : graph[u]) if (!V[v].visited) dfs(v, graph, output);
    output.push_back(u);
}

int strongly_connected_components() {
    vector<int> sorted_exit_time;
    for (int i = 1; i <= n; i++) if (!V[i].visited) dfs(i, graph, sorted_exit_time);

    // G^T
    for (int u = 1; u <= n; u++) for (int v : graph[u]) graph_t[v].push_back(u);

    for (int i = 0; i <= n; i++) V[i].visited = false;
    reverse(sorted_exit_time.begin(), sorted_exit_time.end());

    int id = 1;
    for (int u : sorted_exit_time) {
        if (V[u].visited) continue;
        vector<int> component;
        dfs(u, graph_t, component);
        // Componenets are discovered from transpose graph that means
        // components.back() will have no path to components.back().back().
        components.push_back(component);
        for (int v : component) V[v].comp_id = id;
        id++;
    }

    // Condensation graph
    for (int u = 1; u <= n; u++)
        for (auto v : graph[u])
            if (V[u].comp_id != V[v].comp_id)
                condensation_graph[V[u].comp_id].push_back(V[v].comp_id);

    return id - 1;
}
