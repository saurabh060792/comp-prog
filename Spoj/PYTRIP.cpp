#include <iostream>
#include <algorithm>
#include <cmath>

#define MAX 100010
#define MAXLOG 17

using namespace std;

typedef long long int lli;

int main() {
    
    lli N, M, T, sum, c, primitiveTripleMultipleForC1, primitiveTripleMultipleForC2;
    cin>>T;
    while(T--) {
        cin>>N>>M;
        sum = 0;
        // Euclid's formula for generating pythagorean triple.
        for(int m = 2; m * m <= M; m++) {
            // Atleast one of n or m must be even for primitive triple.
            // m > n && m^2 + n^2 (= c) < M
            for(int n = m % 2 + 1; n <= min((int)sqrt(M - m * m), m - 1);n += 2){
                if(__gcd(n, m) == 1){
                    c = m * m + n * n;
                    primitiveTripleMultipleForC1 = M/c;
                    primitiveTripleMultipleForC2 = (N-1)/c;
                    sum += (primitiveTripleMultipleForC1 - primitiveTripleMultipleForC2);
                }
            }
        }
        cout << sum <<endl;
    }
    return 0;
}
