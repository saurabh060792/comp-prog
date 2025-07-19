#include <iostream>
#include <cstring>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

lli const MAX = 10000007, INF = 1000000009;

int main() {
    lli n;
    scanf("%lld", &n);

    if (n == 1 || n == 2) {
        printf("%lld\n", n);
        return 0;
    }

    // gcd(n, n-1) = 1
    if (n % 2) {
        // if n is odd, gcd(n, n-2) == 1
        printf("%lld\n", n * (n - 1) * (n - 2));
    } else {
        if (n % 3) {
            // if n is even and n is not of the form 3n then
            // gcd (n, n-3) = 1
            // Another option is (n - 1)(n - 2)(n - 3) but it
            // is easy to see that is smaller than n(n - 1)(n - 3)
            printf("%lld\n", n * (n - 1) * (n - 3));
        } else {
            // if n is even and n is of the form 3n then n-1 is odd
            // and we can apply the same logic line 24.
            // Another option is n(n-1)(n-5) but it can be easy shown
            // that it will be samller than (n - 1)(n - 2)(n - 3).
            printf("%lld\n", (n - 1) * (n - 2) * (n - 3));
        }
    }
}
