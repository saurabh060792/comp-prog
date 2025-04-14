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
    int monster_dist, dist, parent;
    char direction; // WRT parent.
};

void bfs();
void monster_bfs();
int up(int v);
int right(int v);
int down(int v);
int left(int v);

int n, m, start_vertex;
vector<int> monster_start_vertices, end_vertices;
char mat[MAX][MAX];
vertex V[MAX * MAX];

int main() {
    int u;
    bool is_start_vertex_boundary = false;
    cin>>n>>m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf(" %c ", &mat[i][j]);
            u = i * m + j;
            if (mat[i][j] == 'A') start_vertex = u;
            if (mat[i][j] == 'M') monster_start_vertices.push_back(u);
            if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                if (mat[i][j] == '.') end_vertices.push_back(u);
                else if (mat[i][j] == 'A') is_start_vertex_boundary = true;
            }
        }
    }

    bfs();
    monster_bfs();

    bool is_viable = false;
    if (is_start_vertex_boundary) {
        is_viable = true;
        printf("YES\n0");
    }
    for (int u : end_vertices) {
        if (V[u].dist < V[u].monster_dist && !is_viable) {
            is_viable = true;
            vector<char> path;
            for (int v = u; V[v].parent != -1; v = V[v].parent) path.push_back(V[v].direction);
            reverse(path.begin(), path.end());
            printf("YES\n%d\n", path.size());
            for (char direction : path) printf("%c", direction);
            break;
        }
    }
    if (!is_viable) printf("NO");
    return 0;
}

bool is_viable(int u) {
    for (int v = u; V[v].parent != -1; v = V[v].parent) {
        if (V[v].dist == V[v].monster_dist) return false;
    }
    return true;
}

void bfs()
{
    int u, status[n * m];
    queue<int> Q;
    for(int i = 0; i < n*m; i++) {
        V[i].dist = INF;
        V[i].parent = INVALID;
        status[i] = UNEXPLORED;
    }
    status[start_vertex] = EXPLORING;
    V[start_vertex].dist = 0;
    V[start_vertex].parent = -1;
    Q.push(start_vertex);
    while(!Q.empty()) {
        u = Q.front();
        Q.pop();
        vector<pair<int, char>> adjacent_vertices = {{up(u), 'U'}, {right(u), 'R'}, {down(u), 'D'}, {left(u), 'L'}};
        for (pair<int, char> i : adjacent_vertices) {
            if (i.first != -1 && mat[i.first / m][i.first % m] == '#') continue;
            if (status[i.first] == UNEXPLORED) {
                status[i.first] = EXPLORING;
                V[i.first].dist = V[u].dist + 1;
                V[i.first].parent = u;
                V[i.first].direction = i.second;
                Q.push(i.first);
            }
        }
        status[u] = EXPLORED;
    }
    return;
}

void monster_bfs()
{
    int u, status[n * m];
    queue<int> Q;
    for(int i = 0; i < n*m; i++) {
        V[i].monster_dist = INF;
        status[i] = UNEXPLORED;
    }

    for (int u : monster_start_vertices) {
        status[u] = EXPLORING;
        V[u].monster_dist = 0;
        Q.push(u);
    }

    while(!Q.empty()) {
        u = Q.front();
        Q.pop();
        vector<pair<int, char>> adjacent_vertices = {{up(u), 'U'}, {right(u), 'R'}, {down(u), 'D'}, {left(u), 'L'}};
        for (pair<int, char> i : adjacent_vertices) {
            if (i.first != -1 && mat[i.first / m][i.first % m] == '#') continue;
            if (status[i.first] == UNEXPLORED) {
                status[i.first] = EXPLORING;
                V[i.first].monster_dist = V[u].monster_dist + 1;
                Q.push(i.first);
            }
        }
        status[u] = EXPLORED;
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
