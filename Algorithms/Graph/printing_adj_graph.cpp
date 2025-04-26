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

vector<int> graph[MAX];
int n, m;

int main() {
    int u, v;
    scanf("%d%m", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        printf("%d: ", i);
        for (int j : graph[i]) printf("%d ", j);
        printf("\n");
    }
    return 0;
}
