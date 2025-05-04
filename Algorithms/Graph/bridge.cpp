#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

#define MAX 100010

using namespace std;

struct vertex {
    int entry_time, lowest_entry_time;
    bool visited;
};

void bridge(int u, int v);
int dfs(int u, int p, int time);
void find_bridges();

int n;
vertex V[MAX];
vector<int> graph[MAX];
vector<pair<int, int>> critical_edges;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=737
int main() {
    int u, v, degree;
    char ch;
    while (scanf("%d", &n) != EOF) {
        memset(V, 0, sizeof(V));
        for (int i = 0; i < MAX; i++) graph[i].clear();
        critical_edges.clear();
        for (int i = 0; i < n; i++) {
            scanf("%d %c%d%c ", &u, &ch, &degree, &ch);
            for (int j = 0; j < degree; j++) {
                scanf("%d", &v);
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
        }
        find_bridges();
        sort(critical_edges.begin(), critical_edges.end());
        printf("%d critical links\n", critical_edges.size());
        for (int i = 0; i < critical_edges.size(); i++)
            printf("%d - %d\n", critical_edges[i].first, critical_edges[i].second);
        printf("\n");
    }
    return 0;
}

int dfs(int u, int p, int time) {
    V[u].visited = true;
    V[u].entry_time = time;

    // lowest_entry_time stores the entry time of the vertex (lets say s) which is
    // entered the earliest in the DFS search such that vertex u or its decendants
    // can reach s with a single edge.
    //
    // Intuitively we can think of s as the higest ancestor (other than parent) of
    // u or its children
    //
    // (0)          (5)---(6)
    //  | \        / |     |
    //  | (2)---(3)  |     |
    //  | /        \ |     |
    // (1)          (4)---(7)
    //
    // Lets say DFS traversed the above graph in the same order as vertex number.
    // That is entry_time[u] = u
    // DFS Tree: (0)--(1)--(2)--(3)--(4)--(5)--(6)--(7)
    // Now similar to dp the value of lowest_entry_time[7] will be calculated first.
    // That is we are calculating values from the bottom of the DFS tree. And that
    // would be 4 as vertex 4 is the highest ancestor (other than parent) of 7 (or its
    // decendants (none in this case)). Then for vertex 6, highest ancestor (other than
    // parent) of 6 or any of its childrent (7 in this case) is vertex 4. Then for
    // vertex 5, it would be vertex 3 and so on. Following are all the entry_time and
    // lowest_entry_time
    // 0 1 2 3 4 5 6 7
    // 0 0 0 3 3 3 4 4
    V[u].lowest_entry_time = time;
    for (int v : graph[u]) {
        if (v == p) continue;
        // Back edge: It can never be a bridge as existence of back edge denotes a cycle
        // with one of its edge (u, v). So here we are just looping over all the back edges
        // to v and picking up the highest ancestor v (ie with the lowest entry_time) for
        // which u has a back edge.
        if (V[v].visited) V[u].lowest_entry_time = min(V[u].lowest_entry_time, V[v].entry_time);
        // Tree edge
        else {
            time = dfs(v, u, time + 1);
            // Here we are looping over children of u and picking lowest_entry_time
            // of the highest ancestor that can be reached by any children.
            V[u].lowest_entry_time = min(V[u].lowest_entry_time, V[v].lowest_entry_time);
            // If highest ancestor that we can go with v (denoted by lowest_entry_time[v])
            // is still short of, when we first enter u then we have found a bridge.
            // In other words, u is higher up in DFS tree than the highest we can reach
            // with v or its decendants.
            //
            // NOTE that if lowest_entry_time[v] <= entry_time[u], then v or any of its
            // children can exactly reach u or can even go higher than u using back edge.
            // In that case, edge (u, v) cannot be bridge becuase there is a back edge
            // from v or from one of its decendants to u or an ancestor of u.
            if (V[v].lowest_entry_time > V[u].entry_time) bridge(u, v);
        }
    }
    return time;
}

void find_bridges() {
    for (int u = 0; u < n; u++) if (!V[u].visited) dfs(u, -1, 0);
}

void bridge(int u, int v) {
    if (u > v) swap(u, v);
    critical_edges.push_back({u, v});
}
