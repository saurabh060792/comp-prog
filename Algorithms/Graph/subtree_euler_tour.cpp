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
typedef long double ld;

struct vertex {
    int status, start_time, end_time;
};

int dfs(int u, int time);
ld range_query(int l, int r);
ld prefix_query(int x);
void point_update(int x, ld delta);

vertex V[MAX];
vector<int> adjacency_graph[MAX];
ld bit[MAX], arr[MAX];

// https://codeforces.com/gym/102694/problem/E
// https://youtu.be/MOy4UDjN8DM?si=m5_DYmmvhDEH3kj7&t=1579
int main() {
    int n, q, u, v, t, x, y;
    ld logx, logy, logres;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        adjacency_graph[u].push_back(v);
        adjacency_graph[v].push_back(u);
    }

    dfs(1, 1);

    scanf("%d", &q);
    while (q--) {
        scanf("%d%d%d", &t, &x, &y);
        if (t == 1) {
            logy = log10(y);
            point_update(V[x].start_time, logy - arr[x]);
            arr[x] = logy;
        } else {
            logx = range_query(V[x].start_time, V[x].end_time);
            logy = range_query(V[y].start_time, V[y].end_time);
            logres = min(logx - logy, 9.0L);
            cout << setprecision(10) << fixed << pow(10.0L, logres) << "\n";
        }
    }
}

// Increment the counter when we go down in tree but not when going up. Eg
// Node = (Start time, End time)
//     (1, 7)
//     /     \
//  (2, 2)   (3, 7)
//              \
//             (4, 7)
//             /   \
//         (5, 5)  (6, 7)
//                   \
//                  (7, 7)
// Properties:
// 1. All start times are unique so we can order them by start time.
// 2. When ordering by start time, a subtree will form a continuous segment.
int dfs(int u, int time) {
    V[u].status = EXPLORING;
    V[u].start_time = time;
    for (int v : adjacency_graph[u]) if (V[v].status == UNEXPLORED) time = dfs(v, time + 1);
    V[u].status = EXPLORED;
    V[u].end_time = time;
    return time;
}

ld range_query(int l, int r) {
    return prefix_query(r) - prefix_query(l - 1);
}

ld prefix_query(int x) {
    ld res = 0;
    for (int i = x; i > 0; i -= i & (-i)) res += bit[i];
    return res;
}

void point_update(int x, ld delta) {
    for (int i = x; i <= MAX; i += i & (-i)) bit[i] += delta;
}
