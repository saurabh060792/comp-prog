#include <iostream>
#include <cmath>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

lli const MAX = 1000005;

int main() {
    lli n, sum = 0, maximum = -1, x;
    scanf("%lld", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &x);
        sum += x;
        maximum = max(maximum, x);
    }
    // https://stackoverflow.com/a/2745086/1056672
    printf("%lld\n", max(maximum, (sum + n - 2) / (n - 1)));
}
