#include <iostream>
#include <queue>
#include <vector>
#include <climits>

#define MAX 200010
#define INF 1000000000000015
#define MOD 1000000007

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;

struct vertex {
    lli d, parent, paths;
};

void dijkstra(lli s);

vertex V[MAX];
vector<pair<int, int>> graph[MAX];
lli n, m;

int main() {
    lli u, v, w;
    scanf("%lld%lld", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%lld%lld%lld", &u, &v, &w);
        graph[u].push_back({v, w});
    }
    dijkstra(1);
    for (int i = 1; i <= n; i++) printf("%lld ", V[i].d);
    return 0;
}

void dijkstra(lli s) {
    lli u, v, d;
    // {distance, index} pair.
    priority_queue<pll, vector<pll>, greater<pll>> Q;
    for (int i = 1; i <= n; i++) V[i].d = INF;
    V[s] = {0, s, 1};
    Q.push({0, s});
    while (!Q.empty()) {
        u = Q.top().second;
        d = Q.top().first;
        Q.pop();
	// A vertex can appear multiple times with different distance
	// in the queue at the same time. So make sure the distance
	// we get equals the distance stored in V[u].d (which is optimal)
	// otherwise ignore and continue.
	// More Details: https://usaco.guide/gold/shortest-paths?lang=cpp#implementation-1
	//       __ (2)__       __(n+2)
	//      /__ (3)__\     /__(n+3)
	//     /     .     \  /     .
	//  (1)      .    (n+1)     .
	//     \     .      /  \    .
	//      \    .     /    \   .
	//       \__(n)___/      \__(2n)
	// In the above example, edge weight can be such that (n+1) node is pushed to the 
	// queue n-1 times, for each vertex (2) to (n). When we pop (n+1) vertex for the first
	// time and relax its neighbors, we dont want to do it again n-2 times becuase then
	// the time complexity would be n^2(log n) because (n+1) node is processed n-1 times
	// and each time we will be going ove its 2n-1 neighbours.
	// The if condition below prevent this from happening. That is for all later n-2 times when
	// vertex (n+1) is popped it wont have the same distance as stored in V[n+1].d because
	// V[n+1].d will contain the lowest distance which it got the first time when it is popped.
        if (d != V[u].d) continue;
        for (auto v : graph[u]) {
            if (d + v.second < V[v.first].d) {
                V[v.first].parent = u;
		V[v.first].paths = V[u].paths;
                Q.push({V[v.first].d = d + v.second, v.first});
            } else if (d + v.second == V[v.first].d) {
                V[v.first].paths = (V[u].paths + V[v.first].paths) % MOD;
            }
        }
    }
    return;
}
