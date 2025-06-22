#include <iostream>

using namespace std;

typedef long long int lli;

int main() {
    lli n;
    scanf("%lld", &n);
    printf("%lld ", n);
    while (n != 1) {
        if (n % 2) n = 3 * n + 1;
        else n /= 2;
        printf("%lld ", n);
    };
    return 0;
}