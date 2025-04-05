#include <iostream>
#include <algorithm>
#include <cmath>

#define MAX 64

using namespace std;

typedef long long int lli;

lli f[MAX][MAX];

int main() {

    for (int i = 0; i < MAX; i++) {
        f[i][0] = 1;
        f[i][i] = 1;
    }

    for (int n = 2; n < MAX; n++) {
        for (int k = 1; k < n; k++) {
            for (int i = 1; i <= k; i++) f[n][k] += f[n - i][k];
            for (int i = k; i >= 0; i--) f[n][k] += f[n - k - 1][i];
        }
    }

    for (int i = 1; i < MAX; i++) {
        for (int j = 0; j <= i; j++) {
            cout<<f[i][j];
            if (j < i) cout << " ";
        }
        cout << endl;
    }
    
    return 0;
}
