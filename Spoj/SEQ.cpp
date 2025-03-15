#include <iostream>
#include <vector>

#define M 1000000000

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
    for (int i = 0; i < n; i++) result[i][i] = 1;

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
    lli t, k, n, result;
    scanf("%lld", &t);
    while(t--){
		scanf("%lld", &k);
		vector<lli> b(k, 0), c(k, 0);
        for (int i = 0; i < k; i++) scanf("%lld", &b[i]);
        for (int i = 0; i < k; i++) scanf("%lld", &c[i]);
		scanf("%lld", &n);

        if (n <= k) {
            printf("%lld\n", b[n-1]%M);
            continue; 
        }

        vector<vector<lli>> matrix(k, vector<lli>(k, 0)), resultMatrix(k, vector<lli>(k, 0));
        for (int i = 0; i < k; i++) matrix[0][i] = c[i];
        for (int i = 0; i < k-1; i++) matrix[i+1][i] = 1;
		resultMatrix = matrixPower(matrix, n-k);
		result = 0;
        for (int i = 0; i < k; i++) result = (result + (resultMatrix[0][i] * b[k-i-1]) % M) % M;
        
		printf("%lld\n", result%M);
	}
    return 0;
}