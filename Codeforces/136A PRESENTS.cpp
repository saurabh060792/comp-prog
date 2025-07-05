#include <bits/stdc++.h>

using namespace std;

int const MAX = 102;

int p[MAX], inv_p[MAX];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++) {
        scanf("%d", &p[i]);
        inv_p[p[i]] = i;
    }
    for (int i = 1; i <= n; i ++) printf("%d ", inv_p[i]);
    return 0;
}
