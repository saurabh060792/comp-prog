#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>

#define INF 10000000
#define INVALID -1
#define UNEXPLORED 0
#define EXPLORING 1
#define EXPLORED 2
#define MAX 100010

using namespace std;

typedef long long int lli;

struct vertex {
    lli status, depth;
};

lli dfs(lli start, vertex *V);
void dfs_tree_from_diameter_endpoint();

vector<pair<lli, lli>> adjacency_graph[MAX];
vertex Vs[MAX], Vt[MAX], Vr[MAX];
lli n;

int main() {
    int t;
    lli u, v, w;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        for (int i = 0; i < n; i++) adjacency_graph[i].clear();
        for (int i = 0; i < n - 1; i++) {
            scanf("%lld%lld%lld", &u, &v, &w);
            u--;
            v--;
            adjacency_graph[u].push_back({v, w});
            adjacency_graph[v].push_back({u, w});
        }
        dfs_tree_from_diameter_endpoint();
        for (int i = 0; i < n; i++) printf("%lld ", max(Vt[i].depth, Vr[i].depth));
        printf("\n");
    }
    return 0;
}

lli dfs(lli start, vertex *V) {
    lli u, max_depth = 0, max_depth_vertex = start;
    stack<int> S;
    memset(V, 0, sizeof(V));
    for (int i = 0; i < n; i++) V[i].status = UNEXPLORED;
    V[start].status = EXPLORING;
    V[start].depth = 0;
    S.push(start);
    while (!S.empty()) {
        u = S.top();
        S.pop();
        for (pair<lli, lli> v : adjacency_graph[u]) {
            if (V[v.first].status == UNEXPLORED) {
                V[v.first].status = EXPLORING;
                V[v.first].depth = V[u].depth + v.second;
                if (V[v.first].depth > max_depth) {
                    max_depth = V[v.first].depth;
                    max_depth_vertex = v.first;
                }
                S.push(v.first);
            }
        }
        V[u].status = EXPLORED;
    }
    return max_depth_vertex;
}

void dfs_tree_from_diameter_endpoint() {
    lli t, r;
    t = dfs(0, Vs);
    r = dfs(t, Vt);
    dfs(r, Vr);
}
