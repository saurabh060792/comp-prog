#include <iostream>
#include <vector>
#include <queue>

#define MAX 1000
#define INF 100000009

using namespace std;

typedef long long int lli;

struct vertex {
    lli d, parent;
};

bool bellman_ford(int s);

vertex V[MAX];
vector<pair<int, int>> graph[MAX];
int n, m;

int main() {
    int u, v, w;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        graph[u].push_back({v, w});
    }
    bellman_ford(1);
    for (int i = 1; i <= n; i++) printf("%d ", V[i].d == INF ? 30000LL : V[i].d);
    printf("\n");
    return 0;
}

bool bellman_ford(int s) {
    int u, v, w;
    for (int i = 0; i <= n; i++) V[i].d = INF;
    vector<int> relaxed_count(MAX, 0);
    vector<bool> in_queue(MAX, false);
    queue<int> q;

    V[s].d = 0;
    q.push(s);
    in_queue[s] = true;
    while (!q.empty()) {
        u = q.front();
        q.pop();
        in_queue[u] = false;
        for (auto i : graph[u]) {
            v = i.first;
            w = i.second;
            if (V[v].d > V[u].d + w ) {
                V[v].d = V[u].d + w;
                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                    relaxed_count[v]++;
                    // Negative Cycle.
                    if (relaxed_count[v] > n) return false;
                }
            }
        }
    }
    return true;
}
