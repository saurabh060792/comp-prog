#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <iomanip>

#define MAX 100010

using namespace std;

typedef long long int lli;

int bridge_dfs(int u, int p, int time);
void comp_dfs(int u, int p, int comp_id);
void find_bridges();
int find_comp();

int n, m;
bool visited[MAX];
vector<int> graph[MAX];
int entry_time[MAX], lowest_entry_time[MAX];
lli comp_count[MAX];
map<pair<int, int>, bool> is_bridge;

int main() {
    int u, v, comp_num;
    lli success = 0;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    find_bridges();
    memset(visited, false, sizeof(visited));
    comp_num = find_comp();

    for (int i = 0; i < comp_num; i++) success += (comp_count[i] * (comp_count[i] - 1));
    cout << fixed << setprecision(5) << (1.0 - 1.0 * success / (1LL * n * (n - 1)));
    return 0;
}

int bridge_dfs(int u, int p, int time) {
    visited[u] = true;
    entry_time[u] = time;
    lowest_entry_time[u] = time;
    for (int v : graph[u]) {
        if (v == p) continue;
        if (visited[v]) lowest_entry_time[u] = min(lowest_entry_time[u], entry_time[v]);
        else {
            time = bridge_dfs(v, u, time + 1);
            lowest_entry_time[u] = min(lowest_entry_time[u], lowest_entry_time[v]);
            if (lowest_entry_time[v] > entry_time[u]) is_bridge[ {u, v}] = is_bridge[ {v, u}] = true;
        }
    }
    return time;
}

void comp_dfs(int u, int p, int comp_id) {
    visited[u] = true;
    comp_count[comp_id]++;
    for (int v : graph[u]) if (!visited[v] && !is_bridge[ {u, v}]) comp_dfs(v, u, comp_id);
}

void find_bridges() {
    for (int i = 1; i <= n; i++) if (!visited[i]) bridge_dfs(i, -1, 1);
}

int find_comp() {
    int id = 0;
    for (int i = 1; i <= n; i++) if (!visited[i]) comp_dfs(i, -1, id++);
    return id;
}
