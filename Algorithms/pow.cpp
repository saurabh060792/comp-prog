#include <iostream>
#include <vector>

#define M1 1000000006
#define M2 1000000007

using namespace std;

typedef long long int lli;

lli pow(lli a, lli exp) { 
    lli ans = 1;
    while(exp > 0) {
        if(exp & 1) ans = (ans * a) % M2;
        a = (a * a) % M2;
        exp >>= 1;
    }
   return ans;
}

int main() {
    ans = pow(3, 5)
    printf("%lld\n", ans);
    return 0;
}
