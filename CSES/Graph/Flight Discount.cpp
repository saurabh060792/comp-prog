#include <iostream>
#include <queue>
#include <vector>
#include <climits>

#define MAX 500010
#define INF 1000000000000015

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;

struct vertex {
    lli d, parent;
};

void dijkstra(vector<pair<int, int>> *graph, vertex *V, lli s);

vertex V[MAX], U[MAX];
vector<pair<int, int>> graph[MAX], graph_t[MAX];
pair<pll, lli> edges[MAX];
lli n, m;

int main() {
    lli u, v, w, ans = INF;
    scanf("%lld%lld", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%lld%lld%lld", &u, &v, &w);
        graph[u].push_back({v, w});
        graph_t[v].push_back({u, w});
        edges[i] = {{u, v}, w};
    }
    dijkstra(graph, U, 1);
    dijkstra(graph_t, V, n);

    for (int i = 0; i < m; i++) {
        u = edges[i].first.first;
        v = edges[i].first.second;
        w = edges[i].second;
        ans = min(ans, U[u].d + V[v].d + w / 2);
    }
    printf("%lld\n", ans);
    return 0;
}

void dijkstra(vector<pair<int, int>> *graph, vertex *V, lli s) {
    lli u, v, d;
    // {distance, index} pair.
    priority_queue<pll, vector<pll>, greater<pll>> Q;
    for (int i = 1; i <= n; i++) V[i].d = INF;
    V[s] = {0, 0};
    Q.push({0, s});
    while (!Q.empty()) {
        u = Q.top().second;
        d = Q.top().first;
        Q.pop();
        if (d != V[u].d) continue;
        for (auto v : graph[u]) {
            if (d + v.second < V[v.first].d) {
                V[v.first].parent = u;
                Q.push({V[v.first].d = d + v.second, v.first});
            }
        }
    }
    return;
}
