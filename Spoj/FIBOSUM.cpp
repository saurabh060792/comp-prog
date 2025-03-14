#include <iostream>
#include <vector>

#define M 1000000007

using namespace std;

typedef long long int lli;

vector<vector<lli>> multiplySquareMatrices(const vector<vector<lli>>& a, const vector<vector<lli>>& b) {
    int n = a.size();
    vector<vector<lli>> result(n, vector<lli>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] = (result[i][j] + (a[i][k] * b[k][j])%M)%M;
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

int main() {
    // Fibonacci matrix
    vector<vector<lli>> fibonacciMatrix = {{1, 1}, {1, 0}}, result;
    lli t, n, m, sumTillM, sumTillN;
    scanf("%lld", &t);
    while(t--){
		scanf("%lld%lld", &n, &m);
		result = matrixPower(fibonacciMatrix, m+2);
		sumTillM = result[1][0];
		result = matrixPower(fibonacciMatrix, n+1);
		sumTillN = result[1][0];
		printf("%lld\n", (sumTillM - sumTillN + M)%M);
	}
    return 0;
}