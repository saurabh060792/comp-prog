#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cstring>

#define MAX 100010

using namespace std;

struct vertex {
    int depth, color, parent, same_color_ancestor, num_same_color_back_edge,
        num_same_color_edges_going_over,
        num_different_color_edges_going_over;
    bool visited;
};

bool dfs(int u, int p);
void find_bipartite_component();

int n, m;
vertex V[MAX];
vector<int> graph[MAX];
map<pair<int, int>, int> edges;
set<pair<int, int>> component_edges;
set<int> component_vertices;

// https://codeforces.com/blog/entry/68138
int main() {
    int u, v;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        if (u > v) swap(u, v);
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges[ {u, v}] = i;
    }
    find_bipartite_component();
    return 0;
}


bool dfs(int u, int p) {
    bool is_bipartite = true;
    V[u].visited = true;
    component_vertices.insert(u);
    for (int v : graph[u]) {
        if (v == p) continue;
        component_edges.insert(u < v ? make_pair(u, v) : make_pair(v, u));
        if (V[v].visited) {
            is_bipartite &= (V[u].color != V[v].color);
            if (V[v].depth < V[u].depth) {
                if (V[v].color == V[u].color) {
                    V[u].num_same_color_back_edge++;
                    V[u].same_color_ancestor = v;
                    V[u].num_same_color_edges_going_over++;
                }
                else V[u].num_different_color_edges_going_over++;
            }
            else {
                V[u].num_same_color_edges_going_over -= (V[v].color == V[u].color);
                V[u].num_different_color_edges_going_over -= (V[v].color != V[u].color);
            }
        }
        else {
            V[v].depth = V[u].depth + 1;
            V[v].color = V[u].color ? 0 : 1;
            V[v].parent = u;
            is_bipartite &= dfs(v, u);
            V[u].num_same_color_edges_going_over += V[v].num_same_color_edges_going_over;
            V[u].num_different_color_edges_going_over += V[v].num_different_color_edges_going_over;
        }
    }
    return is_bipartite;
}

void find_bipartite_component() {
    int non_bipartite_component = 0;
    vector<int> bres, nbres;
    for (int i = 1; i <= n; i++) {
        if (V[i].visited) continue;
        component_edges.clear();
        component_vertices.clear();
        bool is_bipartite = dfs(i, 0);
        if (is_bipartite) {
            for (auto e : component_edges) bres.push_back(edges[ {e.first, e.second}]);
        } else {
            non_bipartite_component++;
            int total_same_color_back_edge = 0, same_color_back_edge;
            bool is_possible = false;
            for (auto u : component_vertices) {
                if (V[u].num_same_color_back_edge > 0) {
                    total_same_color_back_edge += V[u].num_same_color_back_edge;
                    same_color_back_edge = u < V[u].same_color_ancestor
                                           ? edges[ {u, V[u].same_color_ancestor}]
                                           : edges[ {V[u].same_color_ancestor, u}];
                }
            }

            // Back edge will never be a solution unless its the only back edge in the
            // entire graph.
            if (total_same_color_back_edge == 1) {
                nbres.push_back(same_color_back_edge);
                is_possible = true;
            }
            // Tree edges will be in solution when all "bad" back edges in the graph pass
            // over them and none of the "good". Because if even one of them doesn't pass
            // over this tree edge then removing this tree edge wont make the graph bipartite
            // becuase there there will some back edge that this tree edge miss which will
            // cause graph to be non bipartite graph.
            for (auto u : component_vertices) {
                if (V[u].num_same_color_edges_going_over == total_same_color_back_edge
                        && V[u].num_different_color_edges_going_over == 0) {
                    is_possible = true;
                    if (u > V[u].parent) nbres.push_back(edges[ {V[u].parent, u}]);
                    else nbres.push_back(edges[ {u, V[u].parent}]);
                }
            }
            if (!is_possible) {
                printf("0\n");
                return;
            }
        }
    }

    if (non_bipartite_component > 1) {
        printf("0\n");
    } else if (non_bipartite_component == 1) {
        sort(nbres.begin(), nbres.end());
        printf("%d\n", nbres.size());
        for (auto i : nbres) printf("%d ", i);
    } else {
        sort(bres.begin(), bres.end());
        printf("%d\n", bres.size());
        for (auto i : bres) printf("%d ", i);
    }
    return;
}
