#include <iostream>
#include <queue>
#include <vector>
#include <climits>

#define MAX 200010
#define INF 1000000000000015
#define MOD 1000000007

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;

struct vertex {
    lli d, parent, paths;
};

void dijkstra(lli s);

vertex V[MAX];
vector<pair<int, int>> graph[MAX];
lli n, m;

int main() {
    lli u, v, w;
    scanf("%lld%lld", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%lld%lld", &u, &v);
        graph[u].push_back({v, 1});
        graph[v].push_back({u, 1});
    }
    dijkstra(1);
    printf("%lld\n", V[n].d == INF ? 0 : V[n].paths);
    return 0;
}

void dijkstra(lli s) {
    lli u, v, d;
    // {distance, index} pair.
    priority_queue<pll, vector<pll>, greater<pll>> Q;
    for (int i = 1; i <= n; i++) V[i].d = INF;
    V[s] = {0, s, 1};
    Q.push({0, s});
    while (!Q.empty()) {
        u = Q.top().second;
        d = Q.top().first;
        Q.pop();
        if (d != V[u].d) continue;
        for (auto v : graph[u]) {
            if (d + v.second < V[v.first].d) {
                V[v.first].parent = u;
                V[v.first].paths = V[u].paths;
                Q.push({V[v.first].d = d + v.second, v.first});
            } else if (d + v.second == V[v.first].d) {
                V[v.first].paths = (V[u].paths + V[v.first].paths) % MOD;
            }
        }
    }
    return;
}