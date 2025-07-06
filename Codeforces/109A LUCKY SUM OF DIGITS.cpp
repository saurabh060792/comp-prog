#include <iostream>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

int const MAX = 1000006, INF = 100000008;


int main() {
    int n, digit, min_digit = INF, num_four = -1;
    scanf("%d", &n);
    for (int i = 0; i <= n / 4; i++) {
        if ((n - 4 * i) % 7) continue;
        digit = i + ((n - 4 * i) / 7);
        if (digit < min_digit) {
            min_digit = digit;
            num_four = i;
        }
    }
    if (num_four == -1) printf("-1\n");
    else {
        for (int i = 0; i < num_four; i++) printf("4");
        for (int i = 0; i < (n - num_four * 4) / 7; i++) printf("7");
    }
    return 0;
}
