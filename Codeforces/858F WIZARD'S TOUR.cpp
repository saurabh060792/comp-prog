#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cstring>

#define MAX 200010

using namespace std;

struct vertex {
    int depth;
    bool visited;
};

struct connected_edge_pair {
    int left, middle, right;
};

pair<int, int> dfs(int u, int p);
void find_2_len_edge_disjoint_path();
connected_edge_pair merge(pair<int, int> e1, pair<int, int> e2);

int n, m;
vertex V[MAX];
vector<int> graph[MAX];
map<pair<int, int>, bool> used_edges;
vector<connected_edge_pair> res;

// https://youtu.be/x5uWOWV-54E?si=L7FY8sL27Q-UyQEC&t=1907
int main() {
    int u, v;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        if (u > v) swap(u, v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    find_2_len_edge_disjoint_path();

    printf("%d\n", res.size());
    for (auto i : res) printf("%d %d %d\n", i.left, i.middle, i.right);
    return 0;
}

// We try to pair all (u, v) edges (tree or back edges) for all children v of u.
// If there is a odd one out then we pair it with (p, u) edge and return empty edge.
// Else we return (p, u) edge to u's parent p denoting that we could'nt use (p, u)
// edge and p should try to use it to pair its edges.
pair<int, int> dfs(int u, int p) {
    pair<int, int> odd_edge = {0, 0};
    V[u].visited = true;
    for (int v : graph[u]) {
        if (v == p) continue;
        if (V[v].visited) {
            pair<int, int> uv = u < v ? make_pair(u, v) : make_pair(v, u);
            if (!used_edges[uv]) {
                if (odd_edge == make_pair(0, 0)) odd_edge = uv;
                else {
                    res.push_back(merge(odd_edge, uv));
                    used_edges[odd_edge] = true;
                    used_edges[uv] = true;
                    odd_edge = {0, 0};
                }
            }
        }
        else {
            pair<int, int> child_odd_edge = dfs(v, u);
            if (odd_edge == make_pair(0, 0)) odd_edge = child_odd_edge;
            else if (odd_edge != make_pair(0, 0) && child_odd_edge != make_pair(0, 0)) {
                res.push_back(merge(odd_edge, child_odd_edge));
                used_edges[odd_edge] = true;
                used_edges[child_odd_edge] = true;
                odd_edge = {0, 0};
            }
        }
    }

    if (p == 0) return {0, 0};

    pair<int, int> pu = u < p ? make_pair(u, p) : make_pair(p, u);
    if (odd_edge == make_pair(0, 0)) return pu;
    else {
        res.push_back(merge(odd_edge, pu));
        used_edges[odd_edge] = true;
        used_edges[pu] = true;
        return {0, 0};
    }
}

void find_2_len_edge_disjoint_path() {
    for (int i = 1; i <= n; i++) if (!V[i].visited) dfs(i, 0);
}

connected_edge_pair merge(pair<int, int> e1, pair<int, int> e2) {
    if (e1.first == e2.first) return {e1.second, e1.first, e2.second};
    else if (e1.first == e2.second) return {e1.second, e1.first, e2.first};
    else if (e1.second == e2.first) return {e1.first, e1.second, e2.second};
    else return {e1.first, e1.second, e2.first};
}
