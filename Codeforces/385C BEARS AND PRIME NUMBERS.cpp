#include <iostream>
#include <cstring>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

lli const MAX = 10000007, INF = 1000000009;

void sieve_of_eratosthenes();

int a[MAX], f[MAX];
bool is_prime[MAX];

int main() {
    int n, x, q, l, r;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        a[x]++;
    }
    sieve_of_eratosthenes();
    for (int i = 1; i < MAX; i++) f[i] += f[i - 1];
    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &l, &r);
        if (l >= MAX) l = MAX - 1;
        if (r >= MAX) r = MAX - 1;
        printf("%d\n", f[r] - f[l - 1]);
    }
}

void sieve_of_eratosthenes() {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = false;
    is_prime[1] = false;
    for (int i = 2; i < MAX; i++) {
        if (is_prime[i]) {
            for (lli j = i; j < MAX; j += i) {
                is_prime[j] = false;
                if (a[j]) f[i] += a[j];
            }
        }
    }
}
