#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#define MAX 1000010
#define MAX_X 1000


using namespace std;

typedef long long int lli;

struct vertex {
    bool visited;
};

void dfs(int u);

int n;
vector<int> graph[MAX];
pair<int, int> coords[MAX];
vertex V[MAX];

int main() {
    int x, y, u, v, cc = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &x, &y);
        coords[i] = {x - 1, y - 1};
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (coords[i].first == coords[j].first || coords[i].second == coords[j].second) {
                u = coords[i].first * MAX_X + coords[i].second;
                v = coords[j].first * MAX_X + coords[j].second;
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        u = coords[i].first * MAX_X + coords[i].second;
        if (!V[u].visited) {
            dfs(u);
            cc++;
        }
    }
    printf("%d\n", cc - 1);

    return 0;
}

void dfs(int u) {
    V[u].visited = true;
    for (int v : graph[u]) {
        if (V[v].visited) continue;
        else dfs(v);
    }
    return;
}
