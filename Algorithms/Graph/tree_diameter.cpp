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

// https://codeforces.com/gym/102694/problem/B
int main() {
    lli u, v, dia_length = 0;
    scanf("%lld", &n);
    for (int i = 0; i < n - 1; i++) {
        scanf("%lld%lld", &u, &v);
        u--;
        v--;
        adjacency_graph[u].push_back(v);
        adjacency_graph[v].push_back(u);
    }
    dia_length = dfs_tree_from_diameter_endpoint();
    // We have to check depth == diameter length for 2 diameterically opposite vertex (t, r)
    // because from t we will get all the diameter vertex that are on the other side of the
    // center (ie on r side). And from r we will all the diameter vertex that on the t's side
    // of the center.
    //
    // If we just check depth == diameter length from one diameter vertex (lets say t). Then
    // we will miss all diameter nodes on t's side. For example:
    //
    //    1---3---6---5---4
    //                |
    //                |
    //                2
    // Here if t = 4 and we just check depth == diameter length from t then we will miss the
    // vertex 2 which is a diameter vertex
    for (int i = 0; i < n; i++) is_diameter_vertex[i] |= (Vt[i].depth == dia_length);
    for (int i = 0; i < n; i++) is_diameter_vertex[i] |= (Vr[i].depth == dia_length);
    for (int i = 0; i < n; i++) printf("%lld\n", is_diameter_vertex[i] ? dia_length + 1 : dia_length);
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
