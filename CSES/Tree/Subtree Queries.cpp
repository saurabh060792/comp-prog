#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#define MAX 300010
#define UNEXPLORED 0
#define EXPLORING 1
#define EXPLORED 2

using namespace std;

typedef long long int lli;

struct vertex {
    int status, start_time, end_time;
};

int dfs(int u, int time);
void build_bit();
lli range_query(int l, int r);
lli prefix_query(int x);
void point_update(int x, lli delta);

vertex V[MAX];
vector<int> adjacency_graph[MAX];
lli bit[MAX], arr[MAX];
int n;

int main() {
    int q, u, v, t, s;
    lli x;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        adjacency_graph[u].push_back(v);
        adjacency_graph[v].push_back(u);
    }

    dfs(1, 1);
    build_bit();

    while (q--) {
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%lld", &s, &x);
            point_update(V[s].start_time, x - arr[s]);
            arr[s] = x;
        } else {
            scanf("%d", &s);
            printf("%lld\n", range_query(V[s].start_time, V[s].end_time));
        }
    }
}

int dfs(int u, int time) {
    V[u].status = EXPLORING;
    V[u].start_time = time;
    for (int v : adjacency_graph[u]) if (V[v].status == UNEXPLORED) time = dfs(v, time + 1);
    V[u].status = EXPLORED;
    V[u].end_time = time;
    return time;
}

void build_bit() {
    for (int i = 1; i <= n; i++) point_update(V[i].start_time, arr[i]);
}

lli range_query(int l, int r) {
    return prefix_query(r) - prefix_query(l - 1);
}

lli prefix_query(int x) {
    lli res = 0;
    for (int i = x; i > 0; i -= i & (-i)) res += bit[i];
    return res;
}

void point_update(int x, lli delta) {
    for (int i = x; i <= MAX; i += i & (-i)) bit[i] += delta;
}
