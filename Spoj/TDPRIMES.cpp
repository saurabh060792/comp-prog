#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>

#define MAX 100000000

using namespace std;

typedef long long int lli;

bool is_prime[MAX];

void sieve_of_eratosthenes();

int main() {
    sieve_of_eratosthenes();
    int nth_prime = 0;
    for (int i = 1; i < MAX; i++) {
        if (is_prime[i]) {
            nth_prime++;
            if (nth_prime % 100 == 1) printf("%d\n", i);
        }
    }
    return 0;
}

void sieve_of_eratosthenes() {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = false;
    is_prime[1] = false;
    for (lli i = 2; i <= sqrt(MAX) + 1; i++) {
        if (is_prime[i]) {
            for (lli j = i * i; j < MAX; j += i) {
                is_prime[j] = false;
            }
        }
    }
}
