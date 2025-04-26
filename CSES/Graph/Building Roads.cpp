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
    int status;
};

vector<int> dfs();

vertex V[MAX];
vector<int> graph[MAX];
int n, m;

int main() {
    int u, v;
    vector<int> comp;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // for (int i = 1; i <= n; i++) {
    //     printf("%d: ", i);
    //     for (int j : compressed_graph[i]) printf("%d ", j);
    //     printf("\n");
    // }

    comp = dfs();
    printf("%d\n", comp.size() - 1);
    for (int i = 0; i < comp.size() - 1; i++) printf("%d %d\n", comp[i], comp[i + 1]);
    return 0;
}

vector<int> dfs() {
    int u;
    vector<int> comp;
    stack<int> S;
    for (int i = 1; i <= n; i++) V[i].status = UNEXPLORED;
    for (int i = 1; i <= n; i++) {
        if (V[i].status == UNEXPLORED) {
            V[i].status = EXPLORING;
            S.push(i);
            comp.push_back(i);
            while (!S.empty()) {
                u = S.top();
                S.pop();
                for (int v : graph[u]) {
                    if (V[v].status == UNEXPLORED) {
                        V[v].status = EXPLORING;
                        S.push(v);
                    }
                }
                V[u].status = EXPLORED;
            }
        }
    }
    return comp;
}
