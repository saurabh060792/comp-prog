#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 1000010
#define MOD 314159

using namespace std;

typedef long long int lli;


int main() {
    lli t, n, odd[MAX], even[MAX];
    cin>>t;
    while (t--) {
        cin>>n;
        for (int i = 0; i < n; i++) odd[i] = even[i] = 0;
        odd[1] = 1;
        even[1] = 9;
        for (int i = 2; i <= n; i++) {
            even[i] = ((even[i - 1] * 9) % MOD + odd[i - 1]) % MOD;
            odd[i] = ((odd[i - 1] * 9) % MOD + even[i - 1]) % MOD;
        }
        cout<<even[n]<<endl;
    }
    return 0;
}
