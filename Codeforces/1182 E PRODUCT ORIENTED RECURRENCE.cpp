#include <iostream>
#include <vector>

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
        if (exp % 2 == 1) {
            result = multiplySquareMatrices(result, base);
        }
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
    lli n, f1, f2, f3, c, ans;
    scanf("%lld%lld%lld%lld%lld", &n, &f1, &f2, &f3, &c);

    if (n == 4) {
        ans = (((((pow(c, 2) * f3) % M2) * f2) % M2) * f1) % M2;
        printf("%lld\n", ans);
        return 0;
    }

    if (n == 5) {
        ans = (((((pow(c, 6) * pow(f3, 2)) % M2) * pow(f2, 2)) % M2) * f1) % M2;
        printf("%lld\n", ans);
        return 0;
    }

    // Recurrence for c: cn = cn-1 + cn-2 + cn-3 + 2n - 6
    // Subtract cn-1 from cn to remove the 2n term and then do it again to remove the constant term.
    // Somehow negative numbers in matrix is not working
    // vector<vector<lli>> cMatrix = {{3, -2, 0, -1, 1}, {1, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 1, 0}};
    vector<vector<lli>> cMatrix = {{3, M1-2, 0, M1-1, 1}, {1, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 1, 0}};
    // Recurrence for f: fn = fn-1 + fn-2 + fn-3
    vector<vector<lli>> fMatrix = {{1 ,1 ,1}, {1 ,0 ,0}, {0 ,1 ,0}};
    vector<vector<lli>> cExpoMatrix = matrixPower(cMatrix, n-5), fExpoMatrix = matrixPower(fMatrix, n-3);
    lli cPower = (((cExpoMatrix[0][0] * 6) % M1) + ((cExpoMatrix[0][1] * 2) % M1)) % M1;
    ans = (((((pow(c, cPower) * pow(f3, fExpoMatrix[0][0])) % M2) * pow(f2, fExpoMatrix[0][1])) % M2) * pow(f1, fExpoMatrix[0][2])) % M2;

    printf("%lld\n", ans);
    return 0;
}