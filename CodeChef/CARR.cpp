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
    vector<vector<lli>> result;
    lli t, n, m, mminusone, count;
    scanf("%lld", &t);
    while(t--){
        scanf("%lld%lld", &n, &m);
        m = m % M;
        mminusone = (m == 0 ? m - 1 + M : m - 1);
        
        if (n == 1 || n == 2) {
            printf("%lld\n", n == 1 ? m : (m * m) % M);
            continue;
        }

        // Fix first number like X___..n-numbers..____. Then let cn be the count of number of ways to fill rest of the n numbers.
        // cn = [2nd number same as X] +  [2nd number different than X] = 1*(M-1)*cn-2 + (M-1)*cn-1
        // Then our answer would be an = M * cn-1
        // Simplifying:
        // an = M(M-1)cn-3 + M(M-1)cn-2 = (M-1)an-2 + (M-1)an-1
        vector<vector<lli>> matrix = {{mminusone, mminusone}, {1, 0}};
        result = matrixPower(matrix, n-2);
        count = (((result[0][0] * ((m * m) % M)) % M) + ((result[0][1] * m) % M))%M;

        printf("%lld\n", count);
    }
    return 0;
}
