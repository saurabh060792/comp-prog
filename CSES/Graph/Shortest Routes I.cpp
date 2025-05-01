#include <iostream>
#include <queue>
#include <vector>
#include <climits>

#define MAX 200010

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;

struct vertex {
    lli d, parent;
};

void dijkstra(lli s);

vertex V[MAX];
vector<pair<int, int>> graph[MAX];
lli n, m;

int main() {
    lli u, v, w;
    scanf("%lld%lld", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%lld%lld%lld", &u, &v, &w);
        graph[u].push_back({v, w});
    }
    dijkstra(1);
    for (int i = 1; i <= n; i++) printf("%lld ", V[i].d);
    return 0;
}

void dijkstra(lli s) {
    lli u, v, d;
    priority_queue<pll, vector<pll>, greater<pll>> Q;
    for (int i = 1; i <= n; i++) V[i].d = LLONG_MAX;
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
