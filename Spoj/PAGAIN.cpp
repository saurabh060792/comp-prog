#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

typedef long long int lli;
typedef unsigned long long int ulli;
typedef __int128 llli;
typedef unsigned __int128 ullli;

bool miller_rabin(ulli n);
bool check_composite(ulli n, ulli a, ulli d, int s);
ulli pow(ulli a, ulli exp, ulli mod);

int main() {
    lli n;
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        n = n % 2 ? n - 2 : n - 1;
        for (lli i = n; i >= 2; i -= 2) {
            if (miller_rabin(i)) {
                printf("%lld\n", i);
                break;
            }
        }
    }
    return 0;
}

ulli pow(ulli a, ulli exp, ulli mod) {
    ulli result = 1;
    a %= mod;
    while (exp) {
        if (exp & 1)
            result = (ullli)result * a % mod;
        a = (ullli)a * a % mod;
        exp >>= 1;
    }
    return result;
}

bool check_composite(ulli n, ulli a, ulli d, int s) {
    ulli x = pow(a, d, n);
    if (x == 1 || x == n - 1) return false;
    for (int r = 1; r < s; r++) {
        x = (ullli)x * x % n;
        if (x == n - 1) return false;
    }
    return true;
};

bool miller_rabin(ulli n) {
    if (n < 2) return false;

    int r = 0;
    ulli d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return true;
        if (check_composite(n, a, d, r)) return false;
    }
    return true;
}
