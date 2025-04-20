#include <iostream>

#define MAX 200010
#define MAXLOG 18

using namespace std;

typedef long long int lli;

void buildAncestorTable(int *a, int n);
int log2_floor(int n);
void compute_depth(int n);
int lca(int x, int y);

int ancestor[MAXLOG][MAX], arr[MAX], depth[MAX];

int main() {
    int n, q, x, y;
    scanf("%d%d", &n, &q);
    for (int i = 2; i <= n; i++) scanf("%d", &arr[i]);
    buildAncestorTable(arr, n);
    compute_depth(n);
    while (q--) {
        scanf("%d%d", &x, &y);
        printf("%d\n", lca(x, y));
    }
}


int log2_floor(int n) {
    return n ? __builtin_clzll(1) - __builtin_clzll(n) : -1;
}

void buildAncestorTable(int *a, int n) {
    int k = log2_floor(n);
    for (int i = 2; i <= n; i++) ancestor[0][i] = a[i];
    for (int i = 1; i <= k; i++)
        for (int j = 2; j <= n; j++)
            ancestor[i][j] = ancestor[i - 1][ancestor[i - 1][j]];
}

void compute_depth(int n) {
    for (int i = 2; i <= n; i++) depth[i] = depth[ancestor[0][i]] + 1;
}

int lca(int x, int y) {
    int k;
    if (depth[x] < depth[y]) swap(x, y);
    k = log2_floor(depth[x] - depth[y]);
    for (int i = k; i >= 0; i--)
        if (depth[x] - (1 << i) >= depth[y])
            x = ancestor[i][x];
    if (x == y) return x;
    k = log2_floor(depth[x]);
    for (int i = k; i >= 0; i--) {
        if (ancestor[i][x] != ancestor[i][y]) {
            x = ancestor[i][x];
            y = ancestor[i][y];
        }
    }
    return ancestor[0][x];
}
