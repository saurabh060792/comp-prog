// Another solution using Pisano Period.
// #include <iostream>

// using namespace std;

// int f[1572864];

// int main() {
//     int i, t, n, m;
//     f[0] = 1;
//     f[1] = 1;
//     // Pisano period of 2^n is 3*2^(k-1) = 3*2^19 = 1572864
//     for (i = 2; i < 1572864; i++) f[i] = (f[i - 1] + f[i - 2]) % 1048576;
//     scanf("%d", &t);
//     while (t--) {
//         scanf("%d%d", &n, &m);
//         printf("%d\n", f[n % 1572864] % (1 << m));
//     }
//     return 0;
// }

#include <iostream>
#include <vector>

#define M 1000000007

using namespace std;

typedef long long int lli;

vector<vector<lli>> multiplySquareMatrices(
                     const vector<vector<lli>>& a,
                     const vector<vector<lli>>& b,
lli mod) {
    int n = a.size();
    vector<vector<lli>> result(n, vector<lli>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] = (result[i][j] + (a[i][k] * b[k][j]) % mod) % mod;
            }
        }
    }
    return result;
}

vector<vector<lli>> matrixPower(vector<vector<lli>> base, lli exp, lli mod) {
    int n = base.size();
    vector<vector<lli>> result(n, vector<lli>(n, 0));
    for (int i = 0; i < n; ++i) result[i][i] = 1;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = multiplySquareMatrices(result, base, mod);
        }
        base = multiplySquareMatrices(base, base, mod);
        exp /= 2;
    }
    return result;
}

int main() {
    // Fibonacci matrix
    vector<vector<lli>> fibonacciMatrix = {{1, 1}, {1, 0}}, result;
    lli t, n, m, f_n, mod;
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld%lld", &n, &m);
        mod = 1 << m;
        result = matrixPower(fibonacciMatrix, n, mod);
        f_n = result[0][0];
        printf("%lld\n", f_n);
    }
    return 0;
}
