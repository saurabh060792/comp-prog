#include <iostream>
#include <vector>
#include <cmath>

#define M 1000000007

using namespace std;

typedef long long int lli;

vector<vector<lli>> multiplySquareMatrices(const vector<vector<lli>>& a, const vector<vector<lli>>& b) {
    int n = a.size();
    vector<vector<lli>> result(n, vector<lli>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] = (result[i][j] + (a[i][k] * b[k][j]) % M) % M;
            }
        }
    }
    return result;
}

vector<vector<lli>> matrixPower(vector<vector<lli>> base, lli exp) {
    int n = base.size();
    vector<vector<lli>> result(n, vector<lli>(n, 0));
    for (int i = 0; i < n; ++i) result[i][i] = 1;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = multiplySquareMatrices(result, base);
        }
        base = multiplySquareMatrices(base, base);
        exp /= 2;
    }
    return result;
}

// https://www.spoj.com/problems/POWERPHI/
int main() {
    // Fibonacci matrix
    vector<vector<lli>> fibonacciMatrix = {{1, 1}, {1, 0}}, result;
    lli t, n, m;
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld", &n);
        if (n == 0) {
            printf("1\n");
            continue;
        }
        if (n == 1) {
            printf("2\n");
            continue;
        }
        result = matrixPower(fibonacciMatrix, n);
        // nth Lucas number
        // L(n) = F(n+1) + F(n-1)
        //      = 2F(n+1) - F(n)
        // https://en.wikipedia.org/wiki/Golden_ratio#Relationship_to_Fibonacci_and_Lucas_numbers
        // result[0][0] = F(n+1)
        // result[1][0] = F(n)
        printf("%lld\n", (2LL * result[0][0] - result[1][0] + M) % M);
    }
    return 0;
}
