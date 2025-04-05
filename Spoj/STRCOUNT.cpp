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

    // f(n, k) = Last digit is zero + Last digit is one
    //         = f(n-1, k) + 2nd last is zero + 2nd last is one
    //         = f(n-1, k) + f(n-2, k) + 3rd last is zero + 3rd last is one
    //         = so on till kth zero
    // f(n, k) = {sum{i=1}{k} f(n-i, k)} + kth last is one
    // If kth last is one then we already have a longest subarray of 1 of size k.
    // So the k+1th last must be 0 otherwise we would have longest subarray of 1 of size k.
    // Then rest of the (n-k-1) positions can have k or k-1 or k-2 ... or 0 size longest subarray of 1
    // f(n, k) = {sum{i=1}{k} f(n-i, k)} + {sum{i=0}{k} f(n-k-1, i)}
    for (int n = 2; n < MAX; n++) {
        for (int k = 1; k < n; k++) {
            for (int i = 1; i <= k; i++) f[n][k] += f[n - i][k];  // {sum{i=1}{k} f(n-i, k)}
            for (int i = k; i >= 0; i--) f[n][k] += f[n - k - 1][i];  // {sum{i=0}{k} f(n-k-1, i)}
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
