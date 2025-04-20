#include <iostream>

#define MAX 200010
#define MAXLOG 18

using namespace std;

typedef long long int lli;

void buildAncestorTable(int *a, int n);
int log2_floor(int i);

int ancestor[MAXLOG][MAX], arr[MAX];

int main() {
    int n, q, x, k, lg;
    scanf("%d%d", &n, &q);
    for (int i = 2; i <= n; i++) scanf("%d", &arr[i]);
    buildAncestorTable(arr, n);

    while (q--) {
        scanf("%d%d", &x, &k);
        lg = log2_floor(k);
        for (int i = lg; i >= 0; i--)
            if (k >= (1 << i)) {
                x = ancestor[i][x];
                k -= (1 << i);
            }
        if (x == 0) printf("-1\n");
        else printf("%d\n", x);
    }
}

int log2_floor(int i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

void buildAncestorTable(int *a, int n) {
    lli k = log2_floor(n);
    for (int i = 2; i <= n; i++) ancestor[0][i] = a[i];
    for (int i = 1; i <= k; i++)
        for (int j = 2; j <= n; j++)
            ancestor[i][j] = ancestor[i - 1][ancestor[i - 1][j]];
}
