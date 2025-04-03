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
    lli t, n;
    scanf("%lld", &t);
    while(t--){
		  scanf("%lld", &n);
      // Essentially we have to calculate sum(F(4i+3))
      // F(4i+3) = F(2i+2 + 2i+1) = F(2i+1)^2 + F(2i+2)^2 (By Honsberger's Identity)
      // Then for summation use this identity sum(F(i)^2) = F(n)F(n+1)$
  		result = matrixPower(fibonacciMatrix, n<<1);
  		printf("%lld\n", (result[0][0]*result[1][0])%M);
	  }
    return 0;
}
