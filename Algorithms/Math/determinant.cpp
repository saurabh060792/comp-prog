#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

#define MAX 6
#define MOD 599999971

typedef long long int lli;
typedef pair<lli, lli> pll;

lli det(int n);
lli inverse(lli x);
lli pow(lli a, lli exp);

bool vertical_wall[MAX][MAX], horizontal_wall[MAX][MAX];
lli matrix[MAX * MAX][MAX * MAX];

// https://www.spoj.com/problems/KPMAZE/
int main() {
    int r, c, k, r1, r2, c1, c2, u, v;
    scanf("%d%d%d", &c, &r, &k);
    while (k--) {
        scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
        r1--, c1--, r2--, c2--;
        if (r1 == r2) {
            if (c1 > c2) swap(c1, c2);
            vertical_wall[r1][c1] = true;
        } else {
            if (r1 > r2) swap(r1, r2);
            horizontal_wall[r1][c1] = true;
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            u = i * c + j;
            if (!vertical_wall[i][j] && j < c - 1) {
                v = i * c + j + 1;
                matrix[u][u]++;
                matrix[v][v]++;
                matrix[u][v] = (matrix[u][v] + MOD - 1) % MOD;
                matrix[v][u] = (matrix[v][u] + MOD - 1) % MOD;
            }
            if (!horizontal_wall[i][j] && i < r - 1) {
                v = (i + 1) * c + j;
                matrix[u][u]++;
                matrix[v][v]++;
                matrix[u][v] = (matrix[u][v] + MOD - 1) % MOD;
                matrix[v][u] = (matrix[v][u] + MOD - 1) % MOD;
            }
        }
    }

    printf("%lld\n", det(r * c - 1));
}

lli pow(lli a, lli exp) {
    lli ans = 1;
    while (exp > 0) {
        if (exp & 1) ans = (ans * a) % MOD;
        a = (a * a) % MOD;
        exp >>= 1;
    }
    return ans;
}

lli inverse(lli x) {
    return pow(x, (lli) MOD - 2);
}

// Integer Matrix. Choose prime greater which is greater than the answer as a MOD.
// This is to avoid using double and division in determinant calculation.
lli det(int n) {
    lli result = 1;
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j < n && matrix[i][j] == 0) j++;
        if (j == n) return 0;
        swap(matrix[i], matrix[j]);
        result = (result * matrix[i][i]) % MOD;
        lli inv = inverse(matrix[i][i]);
        for (int j = i; j < n; j++) matrix[i][j] = (matrix[i][j] * inv) % MOD;
        for (int k = 0; k < n; k++) {
            if (k == i) continue;
            lli factor = (MOD - matrix[k][i]) % MOD;
            for (int j = i; j < n; j++) {
                matrix[k][j] = (matrix[k][j] + factor * matrix[i][j]) % MOD;
            }
        }
    }
    return result;
}
