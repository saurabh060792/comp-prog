#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

lli const MAX = 2000001, MOD = 1000000007;

int a[MAX];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) scanf("%d", &a[i]);
    sort(a, a + n - 1);
    for (int i = 0; i < n - 1; i++) {
        if (a[i] == i + 1) continue;
        printf("%d\n", i + 1);
        return 0;
    }
    printf("%d\n", n);
    return 0;
}
