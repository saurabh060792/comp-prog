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
    lli coin, total_coin;
    bool visited;
};

int strongly_connected_components();
void dfs(int u, vector<int> *graph, vector<int> &output);
void path(int u);

vertex V[MAX];
vector<int> graph[MAX], graph_t[MAX], condensation_graph[MAX];
vector<vector<int>> components;
int n, m, condensation_n;
lli res[MAX];

int main() {
    int u, v;
    lli max_coin = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &V[i].coin);
    for (int i = 0; i <= m; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
    }
    condensation_n = strongly_connected_components();
    for (int i = 0; i <= n; i++) V[i].visited = false;

    for (auto i : components) if (!V[V[i[0]].comp_id].visited) path((V[i[0]].comp_id));
    for (int i = 1; i <= condensation_n; i++) max_coin = max(max_coin, res[i]);
    printf("%lld\n", max_coin);
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
    lli total_coin;
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
        total_coin = 0;
        for (int v : component) {
            V[v].comp_id = id;
            total_coin += V[v].coin;
        }
        V[id].total_coin = total_coin;
        id++;
    }

    // Condensation graph
    for (int u = 1; u <= n; u++)
        for (auto v : graph[u])
            if (V[u].comp_id != V[v].comp_id)
                condensation_graph[V[u].comp_id].push_back(V[v].comp_id);

    return id - 1;
}

// Aggregates answer along the path from u from the bottom.
void path(int u) {
    V[u].visited = true;
    lli ans = V[u].total_coin, max_coin = 0;
    for (auto v : condensation_graph[u]) {
        if (!V[v].visited) path(v);
        if (res[v] > max_coin) max_coin = res[v];
    }
    res[u] = ans + max_coin;
    return;
}
