#include <iostream>
#include <vector>

// Fermat's Little Theorem: a^(p-1) = 1 mod p
#define M1 1000000006
#define M2 1000000007

using namespace std;

typedef long long int lli;

vector<vector<lli>> multiplySquareMatrices(const vector<vector<lli>>& a, const vector<vector<lli>>& b) {
    int n = a.size();
    vector<vector<lli>> result(n, vector<lli>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] = (result[i][j] + (a[i][k] * b[k][j])%M1)%M1;
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
        if (exp % 2 == 1) result = multiplySquareMatrices(result, base);
        base = multiplySquareMatrices(base, base);
        exp /= 2;
    }
    return result;
}

lli pow(lli a, lli exp) { 
    lli ans = 1;
    while(exp > 0) {
        if(exp % 2 == 1) ans = (ans * a) % M2;
        a = (a * a) % M2;
        exp /= 2;
    }
   return ans;
}

int main() {
    // Fibonacci matrix
    vector<vector<lli>> fibonacciMatrix = {{1, 1}, {1, 0}}, result;
    lli t, p, q, n;
    scanf("%lld", &t);
    while(t--){
		scanf("%lld%lld%lld", &p, &q, &n);
        
        if (n == 0 || n == 1) {
            printf("%lld\n", n == 0 ? p : q);
            continue;
        }

        result = matrixPower(fibonacciMatrix, n-1);

        // f(n) + 1 = (f(n-1) + 1)(f(n-2) + 1)
		printf("%lld\n", ((pow(p+1, result[1][0]) * pow(q+1, result[0][0]))%M2 + M2 - 1)%M2);
	}
    return 0;
}