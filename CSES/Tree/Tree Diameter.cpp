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
#define MAX 300010

using namespace std;

typedef long long int lli;

struct vertex {
    lli status, depth;
};

pair<lli, lli> dfs(lli start, vertex *V);
lli dfs_tree_from_diameter_endpoint();

vector<lli> adjacency_graph[MAX];
vertex Vs[MAX], Vt[MAX], Vr[MAX];
lli n;
bool is_diameter_vertex[MAX];

int main() {
    lli u, v, dia_length;
    scanf("%lld", &n);
    for (int i = 0; i < n - 1; i++) {
        scanf("%lld%lld", &u, &v);
        u--;
        v--;
        adjacency_graph[u].push_back(v);
        adjacency_graph[v].push_back(u);
    }
    dia_length = dfs_tree_from_diameter_endpoint();
    printf("%lld\n", dia_length);
    return 0;
}

pair<lli, lli> dfs(lli start, vertex *V) {
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
        for (lli v : adjacency_graph[u]) {
            if (V[v].status == UNEXPLORED) {
                V[v].status = EXPLORING;
                V[v].depth = V[u].depth + 1;
                if (V[v].depth > max_depth) {
                    max_depth = V[v].depth;
                    max_depth_vertex = v;
                }
                S.push(v);
            }
        }
        V[u].status = EXPLORED;
    }
    return {max_depth_vertex, max_depth};
}

lli dfs_tree_from_diameter_endpoint() {
    pair<lli, lli> t, r;
    t = dfs(0, Vs);
    r = dfs(t.first, Vt);
    dfs(r.first, Vr);
    return r.second;
}
