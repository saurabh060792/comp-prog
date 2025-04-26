#include <iostream>
#include <vector>
#include <map>

#define MAX 200010
#define UNEXPLORED 0
#define EXPLORING 1
#define EXPLORED 2

using namespace std;

struct vertex {
    int parent, status, matching_including_root, matching_excluding_root;
};

void dfs(int u);

vertex V[MAX];
vector<int> graph[MAX];
int n;

int main() {
    int u, v, max_matching = 0;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1);
    printf("%d\n", max(V[1].matching_including_root, V[1].matching_excluding_root));
    return 0;
}

void dfs(int u) {
    int include = 0, exclude = 0;
    map<int, bool> children_matching = {};
    V[u].status = EXPLORING;
    for (int v : graph[u]) {
        if (V[v].status == UNEXPLORED) {
            V[v].parent = u;
            dfs(v);
            if (V[v].matching_including_root > V[v].matching_excluding_root) {
                exclude += V[v].matching_including_root;
                children_matching[v] = true;
            } else {
                exclude += V[v].matching_excluding_root;
                children_matching[v] = false;
            }
        }
    }

    for (int v : graph[u]) {
        if (V[u].parent == v) continue;
        if (children_matching[v])
            include = max(include, exclude - V[v].matching_including_root + V[v].matching_excluding_root + 1);
        else include = max(include, exclude + 1);
    }

    V[u].matching_including_root = include;
    V[u].matching_excluding_root = exclude;
    V[u].status = EXPLORED;
    return;
}
