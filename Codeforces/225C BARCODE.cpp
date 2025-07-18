#include <iostream>
#include <cmath>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

lli const MAX = 1003, INF = 1000000009;

int cost_w[MAX], cost_b[MAX], dp_w[MAX], dp_b[MAX];
string s[MAX];

int main() {
    int n, m , x, y;
    scanf("%d%d%d%d", &n, &m, &x, &y);
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '.') cost_b[j + 1]++;
            else cost_w[j + 1]++;
        }
    }

    for (int i = 0; i <= m; i++) cost_w[i] += cost_w[i - 1];
    for (int i = 0; i <= m; i++) cost_b[i] += cost_b[i - 1];

    for (int i = 1; i < x; i++) dp_w[i] = dp_b[i] = INF;
    for (int i = x; i <= m; i++) {
        dp_w[i] = INF;
        for (int j = i - x; j >= max(0, i - y); j--) dp_w[i] = min(dp_w[i], dp_b[j] + cost_w[i] - cost_w[j]);
        dp_b[i] = INF;
        for (int j = i - x; j >= max(0, i - y); j--) dp_b[i] = min(dp_b[i], dp_w[j] + cost_b[i] - cost_b[j]);
    }

    printf("%d\n", min(dp_w[m], dp_b[m]));
}
