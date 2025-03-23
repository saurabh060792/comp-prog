#include <iostream>
#include <algorithm>
#include <cmath>

#define MAX 100010
#define MAXLOG 17

using namespace std;

typedef long long int lli;

int main() {
    
    lli N, M, T, sum, shortSide, c, primitiveTripleMultipleForC, primitiveTripleMultipleForShortSide;
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
                    shortSide = min(m * m - n * n, 2 * m * n);
                    c = m * m + n * n;
                    int primitiveTripleMultipleForShortSide = (N-1)/shortSide;
                    int primitiveTripleMultipleForC = M/c;
                    if(primitiveTripleMultipleForShortSide < primitiveTripleMultipleForC)
                        sum += (primitiveTripleMultipleForC - primitiveTripleMultipleForShortSide);
                }
            }
        }
        cout << sum <<endl;
    }
    return 0;
}
