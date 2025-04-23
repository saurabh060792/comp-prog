#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>

#define MAX 200010
#define UNEXPLORED 0
#define EXPLORING 1
#define EXPLORED 2

using namespace std;

struct vertex {
    int status, depth, compressed_vertex;
};

void compress_graph(int start_vertex);
pair<int, int> dfs(int start, vertex *V);
int dfs_tree_from_diameter_endpoint();

vertex V[MAX], Vs[MAX], Vt[MAX], Vr[MAX];
vector<int> graph[MAX], compressed_graph[MAX];
int n, color[MAX];

int main() {
    int u, v, ans;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &color[i]);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    compress_graph(1);

    // for (int i = 1; i <= n; i++) {
    //     printf("%d: ", i);
    //     for (int j : compressed_graph[i]) printf("%d ", j);
    //     printf("\n");
    // }

    ans = dfs_tree_from_diameter_endpoint();
    printf("%d\n", (ans + 1) / 2);
    return 0;
}

void compress_graph(int start_vertex) {
    int u, compressed_vertex_counter = 1;
    queue<int> Q;
    for (int i = 1; i <= n; i++) V[i].status = V[i].compressed_vertex = UNEXPLORED;
    V[start_vertex].status = EXPLORING;
    V[start_vertex].compressed_vertex = compressed_vertex_counter;
    Q.push(start_vertex);
    while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        for (int v : graph[u]) {
            if (V[v].status == UNEXPLORED) {
                V[v].status = EXPLORING;
                Q.push(v);
                if (color[v] == color[u]) {
                    V[v].compressed_vertex = V[u].compressed_vertex;
                } else {
                    compressed_vertex_counter++;
                    compressed_graph[V[u].compressed_vertex].push_back(compressed_vertex_counter);
                    compressed_graph[compressed_vertex_counter].push_back(V[u].compressed_vertex);
                    V[v].compressed_vertex = compressed_vertex_counter;
                }
            }
        }
        V[u].status = EXPLORED;
    }
    return;
}

pair<int, int> dfs(int start, vertex *V) {
    int u, max_depth = 0, max_depth_vertex = start;
    stack<int> S;
    memset(V, 0, sizeof(V));
    for (int i = 0; i < n; i++) V[i].status = UNEXPLORED;
    V[start].status = EXPLORING;
    V[start].depth = 0;
    S.push(start);
    while (!S.empty()) {
        u = S.top();
        S.pop();
        for (int v : compressed_graph[u]) {
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

int dfs_tree_from_diameter_endpoint() {
    pair<int, int> t, r;
    t = dfs(1, Vs);
    r = dfs(t.first, Vt);
    dfs(r.first, Vr);
    return r.second;
}
