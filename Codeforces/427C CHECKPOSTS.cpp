#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <map>

using namespace std;

typedef long long int lli;

lli const MAX = 500005, INF = 1000000001, MOD = 1000000007;

struct vertex {
    int depth, parent, comp_id;
    lli cost, min_cost, min_cost_count;
    bool visited;
};

int strongly_connected_components();
void dfs(int u, vector<int> *graph, vector<int> &output);

vertex V[MAX];
vector<int> graph[MAX], graph_t[MAX];
vector<vector<int>> components;
int n, m, condensation_n;

int main() {
    int u, v, s, t;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &V[i].cost);
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
    }
    condensation_n = strongly_connected_components();

    lli ans1 = 0, ans2 = 1;
    for (int i = 1; i <= condensation_n; i++) {
        ans1 += V[i].min_cost;
        ans2 = (ans2 * V[i].min_cost_count) % MOD;
    }
    printf("%lld %lld\n", ans1, ans2);

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
    for (int u = 1; u <= n; u++) for (int v : graph[u]) graph_t[v].push_back(u);
    for (int i = 0; i <= n; i++) V[i].visited = false;
    reverse(sorted_exit_time.begin(), sorted_exit_time.end());

    int id = 1;
    lli min_cost, min_cost_count;
    for (int u : sorted_exit_time) {
        if (V[u].visited) continue;
        vector<int> component;
        dfs(u, graph_t, component);
        components.push_back(component);
        min_cost = INF;
        min_cost_count = 0;
        for (int v : component) {
            V[v].comp_id = id;
            min_cost = min(min_cost, V[v].cost);
        }
        for (int v : component) if (V[v].cost == min_cost) min_cost_count++;
        V[id].min_cost = min_cost;
        V[id].min_cost_count = min_cost_count;
        id++;
    }
    return id - 1;
}
