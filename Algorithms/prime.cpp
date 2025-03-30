#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>

#define MAX 1000010

using namespace std;

typedef long long int lli;

bool is_prime[MAX];
vector<lli> primes;

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
            primes.push_back(i);
            for (lli j = i * i; j < MAX; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

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
