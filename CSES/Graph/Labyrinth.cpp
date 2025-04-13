#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 10000000
#define INVALID -1
#define UNEXPLORED 0
#define EXPLORING 1
#define EXPLORED 2
#define MAX 1010

using namespace std;

struct vertex {
    int d, status, parent;
    char direction; // WRT parent.
};

void bfs(int start_vertex);
int up(int v);
int right(int v);
int down(int v);
int left(int v);

int n, m;
char mat[MAX][MAX];
vertex V[MAX * MAX];

int main() {
    int start_vertex, end_vertex;
    cin>>n>>m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf(" %c", &mat[i][j]);
            if (mat[i][j] == 'A') start_vertex = i * m + j;
            if (mat[i][j] == 'B') end_vertex = i * m + j;
        }
    }

    bfs(start_vertex);

    if (V[end_vertex].status == UNEXPLORED) printf("NO\n");
    else {
        vector<char> path;
        for (int i = end_vertex; V[i].parent != -1; i = V[i].parent) path.push_back(V[i].direction);
        reverse(path.begin(), path.end());
        printf("YES\n%d\n", path.size());
        for (char direction : path) printf("%c", direction);
    }
    return 0;
}

void bfs(int start_vertex)
{
    int u, v;
    queue<int> Q;
    for(int i = 0; i < n*m; i++) {
        V[i].d = INF;
        V[i].parent = INVALID;
        V[i].status = UNEXPLORED;
    }
    V[start_vertex].status = EXPLORING;
    V[start_vertex].d = 0;
    V[start_vertex].parent = -1;
    Q.push(start_vertex);
    while(!Q.empty()) {
        u = Q.front();
        Q.pop();
        vector<pair<int, char>> adjecent_vertices = {{up(u), 'U'}, {right(u), 'R'}, {down(u), 'D'}, {left(u), 'L'}};
        for (pair<int, char> i : adjecent_vertices) {
            if (i.first != -1 && mat[i.first / m][i.first % m] == '#') continue;
            if (V[i.first].status == UNEXPLORED) {
                V[i.first].status = EXPLORING;
                V[i.first].d = V[u].d + 1;
                V[i.first].parent = u;
                V[i.first].direction = i.second;
                Q.push(i.first);
            }
        }
        V[u].status = EXPLORED;
    }
    return;
}

int up(int v) {
    int i = v/m, j = v%m;
    if (i == 0) return INVALID;
    else return (i - 1) * m + j;
}

int down(int v) {
    int i = v/m, j = v%m;
    if (i == n - 1) return INVALID;
    else return (i + 1) * m + j;
}

int right(int v) {
    int j = v%m;
    if (j == m - 1) return INVALID;
    else return v + 1;
}

int left(int v) {
    int j = v%m;
    if (j == 0) return INVALID;
    else return v - 1;
}