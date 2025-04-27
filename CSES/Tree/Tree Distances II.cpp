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

typedef long long int lli;

struct vertex {
    int status, depth, subtree_size;
    lli ans;
};

int dfs(int u);
void sum_of_all_paths(int u);

vertex V[MAX];
vector<int> graph[MAX];
int n, m;

int main() {
    int u, v;
    lli sum = 0;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1);

    for (int i = 1; i <= n; i++) {
        sum += V[i].depth;
        V[i].status = UNEXPLORED;
    }
    V[1].ans = sum;

    sum_of_all_paths(1);

    for (int i = 1; i <= n; i++) printf("%lld ", V[i].ans);
    printf("\n");
    return 0;
}

int dfs(int u) {
    int subtree_size = 1;
    V[u].status = EXPLORING;
    for (int v : graph[u]) {
        if (V[v].status == UNEXPLORED) {
            V[v].depth = V[u].depth + 1;
            subtree_size += dfs(v);
        }
    }
    V[u].status = EXPLORED;
    V[u].subtree_size = subtree_size;
    return subtree_size;
}

void sum_of_all_paths(int u) {
    V[u].status = EXPLORING;
    for (int v : graph[u]) {
        if (V[v].status == UNEXPLORED) {
            // Ans[child] = Ans[Parent] + (Ans from vertex not in child's subtree) - (Ans from child's subtree)
            V[v].ans = V[u].ans + (n - V[v].subtree_size) - V[v].subtree_size;
            sum_of_all_paths(v);
        }
    }
    V[u].status = EXPLORED;
    return;
}
