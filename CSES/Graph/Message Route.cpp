#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 10000000
#define INVALID -1
#define UNEXPLORED 0
#define EXPLORING 1
#define EXPLORED 2
#define MAX 100010

using namespace std;

struct vertex {
    int status, parent;
};

void bfs();

int n, m;
vector<int> graph[MAX];
vertex V[MAX];

int main() {
    int u, v;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }

    bfs();

    if (V[n - 1].status == UNEXPLORED) printf("IMPOSSIBLE\n");
    else {
        vector<int> path;
        for (int i = n - 1; V[i].parent != -1; i = V[i].parent) {
            path.push_back(V[i].parent);
        }
        reverse(path.begin(), path.end());
        printf("%d\n", path.size() + 1);
        for (int i : path) printf("%d ", i + 1);
        printf("%d\n", n);
    }
    return 0;
}

void bfs()
{
    int u, v;
    queue<int> Q;
    for(int i = 0; i < n; i++) {
        V[i].parent = INVALID;
        V[i].status = UNEXPLORED;
    }
    V[0].status = EXPLORING;
    V[0].parent = -1;
    Q.push(0);
    while(!Q.empty()) {
        u = Q.front();
        Q.pop();
        for (int v : graph[u]) {
            if (V[v].status == UNEXPLORED) {
                V[v].status = EXPLORING;
                V[v].parent = u;
                Q.push(v);
            }
        }
        V[u].status = EXPLORED;
    }
    return;
}


