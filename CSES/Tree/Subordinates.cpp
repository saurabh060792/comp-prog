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
    int status, sum;
};

int dfs(int u);

vertex V[MAX];
vector<int> graph[MAX];
int n, m;

int main() {
    int u;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &u);
        graph[i].push_back(u);
        graph[u].push_back(i);
    }

    dfs(1);
    for (int i = 1; i <= n; i++) printf("%d ", V[i].sum - 1);
    return 0;
}

int dfs(int u) {
    int sum = 1;
    V[u].status = EXPLORING;
    for (int v : graph[u]) if (V[v].status == UNEXPLORED) sum += dfs(v);
    V[u].status = EXPLORED;
    V[u].sum = sum;
    return sum;
}
