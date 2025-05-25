#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
#include <climits>

#define MAX 500010

using namespace std;

typedef long long int lli;

void dfs(int u);

vector<pair<int, int>> graph[MAX];
vector<int> eulerian_path;
int n, m;
bool visited_edge[MAX];
map<pair<int, int>, int> edges;
// Coordinate compression maps
map<int, int> cc_v, cc_p;

int main() {
    int u, v, volume, pitch, t, cc_index;
    scanf("%d", &t);
    while (t--) {
        for (int i = 0; i <= 2 * n; i++) graph[i].clear();
        eulerian_path.clear();
        memset(visited_edge, false, sizeof(visited_edge));
        edges.clear();
        cc_v.clear();
        cc_p.clear();
        cc_index = 1;

        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            scanf("%d%d", &volume, &pitch);
            if (cc_v.find(volume) == cc_v.end()) cc_v[volume] = cc_index++;
            if (cc_p.find(pitch) == cc_p.end())  cc_p[pitch] = cc_index++;
            graph[cc_v[volume]].push_back({cc_p[pitch], i});
            graph[cc_p[pitch]].push_back({cc_v[volume], i});
            if (cc_v[volume] > cc_p[pitch]) edges[ {cc_p[pitch], cc_v[volume]}] = i;
            else edges[ {cc_v[volume], cc_p[pitch]}] = i;
        }

        // Size of the graph.
        n = cc_index - 1;

        int root1 = -1, root2 = -1, odd_degree_count = 0;
        for (int i = 1; i <= n; i++) {
            if (graph[i].size() % 2) {
                odd_degree_count++;
                if (root1 == -1) root1 = i;
                else if (root2 == -1) root2 = i;
                else break;
            }
        }

        // For Eulerian cycle or path, we can't have more than 2 odd degree vertex.
        if (odd_degree_count > 2) {
            printf("NO\n");
            continue;
        }

        // If odd degree vertex count is 0 then we will have Eulerian cycle else
        // we will have a Eulerian path which we are starting from root1 and it will
        // end at root2 (as those 2 are the only odd degree vertices).
        if (odd_degree_count == 0) dfs(1);
        else dfs(root1);

        // This is the ensure that we have covered all the edges. Because if the
        // graph is not connected, then we wont have a Eulerian cycle/path.
        if (eulerian_path.size() != m + 1) {
            printf("NO\n");
            continue;
        }

        reverse(eulerian_path.begin(), eulerian_path.end());
        printf("YES\n");
        for (int i = 0; i < eulerian_path.size() - 1; i++) {
            u = eulerian_path[i];
            v = eulerian_path[i + 1];
            if (u > v) swap(u, v);
            printf("%d ", edges[ {u, v}]);
        }
        printf("\n");
    }
    return 0;
}

void dfs(int u) {
    while (!graph[u].empty()) {
        auto [v, idx] = graph[u].back();
        graph[u].pop_back();
        if (visited_edge[idx]) continue;
        visited_edge[idx] = true;
        dfs(v);
    }
    eulerian_path.push_back(u);
}
