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
#define MAX 55

using namespace std;

struct vertex {
    int status, depth;
};

int dfs(pair<int, int> start_vertex);

char mat[MAX][MAX];
vector<int> X = {0, 0, 1, -1, -1, 1, -1, 1}, Y = { -1, 1, 0, 0, 1, 1, -1, -1};
vector<pair<int, int>> start_vertex;
vertex V[MAX][MAX];
int n, m;

int main() {
    int length, max_length, test_case = 1;
    while (1) {
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0) break;

        memset(mat, 0, sizeof(mat));
        start_vertex.clear();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf(" %c", &mat[i][j]);
                if (mat[i][j] == 'A') start_vertex.push_back({i, j});
            }
        }

        max_length = 0;
        for (auto i : start_vertex) {
            memset(V, 0, sizeof(V));
            length = dfs(i);
            if (length > max_length) max_length = length;
        }
        printf("Case %d: %d\n", test_case++, max_length + (start_vertex.size() > 0 ? 1 : 0));
    }
    return 0;
}

int dfs(pair<int, int> start_vertex) {
    int max_depth = 0;
    pair<int, int> u, v;
    stack<pair<int, int>> S;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) V[i][j].status = UNEXPLORED;
    V[start_vertex.first][start_vertex.second].status = EXPLORING;
    V[start_vertex.first][start_vertex.second].depth = 0;
    S.push(start_vertex);
    while (!S.empty()) {
        u = S.top();
        S.pop();
        for (int i = 0; i < 8; i++) {
            v = {u.first + X[i], u.second + Y[i]};
            int vx = v.first, vy = v.second;
            if (vx < 0 || vx >= n || vy < 0 || vy >= m || mat[vx][vy] - mat[u.first][u.second] != 1) continue;
            if (V[vx][vy].status == UNEXPLORED) {
                V[vx][vy].status = EXPLORING;
                V[vx][vy].depth = V[u.first][u.second].depth + 1;
                max_depth = max(max_depth, V[vx][vy].depth);
                S.push(v);
            }
        }
        V[u.first][u.second].status = EXPLORED;
    }
    return max_depth;
}
