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
