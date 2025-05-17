#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>

#define MAX 1000010

using namespace std;

typedef long long int lli;
typedef unsigned long long int ulli;
typedef __int128 llli;
typedef unsigned __int128 ullli;

bool is_prime[MAX];
vector<lli> primes;

bool miller_rabin(ulli n);
bool check_composite(ulli n, ulli a, ulli d, int s);
ulli pow(ulli a, ulli exp, ulli mod);
void sieve_of_eratosthenes();
vector<pair<lli, lli>> prime_decomposition(lli x);

int main() {
    sieve_of_eratosthenes();
    lli t, a, b, g, ans;

    scanf("%lld", &t);
    while(t--){
        scanf("%lld%lld", &a, &b);
        g = __gcd(a, b);
        vector<pair<lli, lli>> pd = prime_decomposition(g);
        ans = 1;
        for (pair<lli, lli> d : pd) ans *= (d.second + 1);
        printf("%lld\n", ans);
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
    for (int i = 0; i < MAX; i++) if (is_prime[i]) primes.push_back(i);
}

// Prime Factorization.
vector<pair<lli, lli>> prime_decomposition(lli x) {
    vector<pair<lli, lli>> answer;
    for(lli p: primes) {
        if(x <= 1) break;
        else if(x % p == 0) {
            lli prime_power = 0;
            while(x % p == 0) {
                x /= p;
                prime_power++;
            }
            answer.push_back(make_pair(p, prime_power));
        }
        else if(p*p > x) {
            answer.push_back(make_pair(x, 1));
            break;
        }
    } return answer;
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

// For a base 2 <= a <= n-1 we check if either
// a^d = 1 mod n OR a^(d*2^r) = -1 mod n where 0 <= r <= s -1 
bool check_composite(ulli n, ulli a, ulli d, int s) {
    ulli x = pow(a, d, n);
    if (x == 1 || x == n - 1) return false;
    for (int r = 1; r < s; r++) {
        x = (ullli)x * x % n;
        if (x == n - 1) return false;
    }
    return true;
};

// https://cp-algorithms.com/algebra/primality_tests.html
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
