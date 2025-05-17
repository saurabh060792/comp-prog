#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

#define MAX 1000050

using namespace std;

typedef long long int lli;

struct vertex {
    int depth, parent, comp_id;
    lli fun, total_fun;
    bool visited;
};

int strongly_connected_components();
void dfs(int u, vector<int> *graph, vector<int> &output);
void path(int u, int t);

vertex V[MAX];
vector<int> graph[MAX], graph_t[MAX], condensation_graph[MAX];
vector<vector<int>> components;
int n, m, condensation_n;
pair<bool, lli> res[MAX];

int main() {
    int u, v, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= n; i++) scanf("%lld", &V[i].fun);
    for (int i = 0; i <= m; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
    }
    condensation_n = strongly_connected_components();

    for (int i = 0; i <= n; i++) V[i].visited = false;
    path(V[s].comp_id, V[t].comp_id);
    printf("%lld\n", res[V[s].comp_id].second);
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
    lli total_fun;
    for (int u : sorted_exit_time) {
        if (V[u].visited) continue;
        vector<int> component;
        dfs(u, graph_t, component);
        // Componenets are discovered from transpose graph that means
        // components.back() will have no path to components.back().back().
        // That means if we start from the first component in components vector
        // we can reach any vertex unless the graph is disconnected.
        //
        // This fact is helpful in solving https://cses.fi/problemset/task/1686
        components.push_back(component);
        total_fun = 0;
        for (int v : component) {
            V[v].comp_id = id;
            total_fun += V[v].fun;
        }
        V[id].total_fun = total_fun;
        id++;
    }

    // Condensation graph
    for (int u = 1; u <= n; u++)
        for (auto v : graph[u])
            if (V[u].comp_id != V[v].comp_id)
                condensation_graph[V[u].comp_id].push_back(V[v].comp_id);

    return id - 1;
}

// Aggregates answer along the path from u to t from the bottom.
// Every vertex will have a (bool, lli) pair. First one denoting
// if t is reachable or not. If not reachable second value will be
// 0 else it will contain the sum from u to t.
//
// Further condensation graph is acyclic so no back edges only tree,
// forward and cross edges whic makes the followwing logic work.
void path(int u, int t) {
    V[u].visited = true;
    if (u == t) {
        res[u] = {true, V[t].total_fun};
        return;
    }
    pair<bool, lli> ans = {false, 0};
    for (auto v : condensation_graph[u]) {
        if (!V[v].visited) path(v, t);
        if (res[v].first && res[v].second > ans.second) ans = res[v];
    }
    res[u] = {ans.first, ans.second + ans.first * V[u].total_fun};
    return;
}
