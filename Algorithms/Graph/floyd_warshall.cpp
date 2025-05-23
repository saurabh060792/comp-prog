#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <climits>

#define MAX 505
#define INF_MEMSET 0x3f
#define INF LLONG_MAX

using namespace std;

typedef long long int lli;

void floyd_warshall();

int n, m;
lli d[MAX][MAX];

int main() {
    int q, u, v;
    lli w;
    scanf("%d%d%d", &n, &m, &q);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) d[i][j] = 0;
            else d[i][j] = INF;
        }
    }
    for (int i = 0; i < m; i++) {
        scanf("%d%d%lld", &u, &v, &w);
        u--, v--;

        // Multiple edges.
        d[u][v] = d[v][u] = min(d[u][v], w);
    }

    floyd_warshall();

    while (q--) {
        scanf("%d%d", &u, &v);
        u--; v--;
        if (d[u][v] == INF) printf("-1\n");
        else printf("%lld\n", d[u][v]);
    }
}

void floyd_warshall() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] < INF && d[k][j] < INF)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}
