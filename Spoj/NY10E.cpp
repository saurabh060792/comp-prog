#include <iostream>

#define MAX 64
#define MAXDIGIT 9

using namespace std;

typedef long long int lli;

lli dp[MAX + 1][MAXDIGIT + 1], ans[MAX];

int main() {
    int t, n, testcase;
    scanf("%d", &t);
    for (int i = 0; i <= MAXDIGIT; i++) dp[1][i] = 1;
    for (int i = 2; i <= MAX; i++)
        for (int j = 0; j <= MAXDIGIT; j++)
            for (int k = 0; k <= j; k++)
                dp[i][j] += dp[i - 1][k];
    for (int i = 0; i <= MAX; i++) {
        for (int j = 0; j <= MAXDIGIT; j++) {
            ans[i] += dp[i][j];
        }
    }

    while (t--) {
        scanf("%d%d", &testcase, &n);
        printf("%d %lld\n", testcase, ans[n]);
    }
    return 0;
}
