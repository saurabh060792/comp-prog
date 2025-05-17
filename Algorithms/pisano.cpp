#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

#define M 1000000007
#define MAX 1000050

using namespace std;

typedef long long int lli;

__int128 gcd(__int128 a, __int128 b);
__int128 lcm(__int128 a, __int128 b);
void sieve_of_eratosthenes();
vector<pair<lli, lli>> prime_decomposition(lli x);
vector<vector<lli>> multiply_square_matrices(vector<vector<lli>>& a, vector<vector<lli>>& b, lli mod);
vector<vector<lli>> matrix_power(vector<vector<lli>> base, lli exp, lli mod);
bool is_period(lli n, lli mod);
lli smallest_divisor_period(lli x, lli mod);
lli pisano_prime(lli p);
__int128 pisano(lli x);
void print_int128(__int128 n);

bool is_prime[MAX];
vector<lli> primes;
// One version of fibonacci matrix
// U = 0 1    U^n = F(n-1)  F(n)
//     1 1          F(n)    F(n+1)
// Another version of fibonacci matrix
// Q = 1 1    Q^n = F(n+1)  F(n)
//     0 1          F(n)    F(n-1)
vector<vector<lli>> fibonacciMatrix = {{0, 1}, {1, 1}};

// https://webspace.ship.edu/msrenault/fibonacci/fib.htm
// http://www.jstor.org/stable/2309169?seq=1
int main() {
    int t;
    lli n;

    // Precompute primes to speed up prime decomposition.
    sieve_of_eratosthenes();
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        __int128 res = pisano(n);
        print_int128(res);
    }
    return 0;
}

void print_int128(__int128 n) {
    vector<int> digits;
    while (n) {
        digits.push_back(n % 10);
        n /= 10;
    }
    reverse(digits.begin(), digits.end());
    for (int i = 0; i < digits.size(); i++) printf("%d", digits[i]);
    printf("\n");
}

__int128 gcd(__int128 a, __int128 b) {
    while (a && b) a > b ? a %= b : b %= a;
    return a + b;
}

__int128 lcm(__int128 a, __int128 b) {
    return a / gcd(a, b) * b;
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

vector<pair<lli, lli>> prime_decomposition(lli x) {
    vector<pair<lli, lli>> answer;
    for (lli p : primes) {
        if (x <= 1) break;
        else if (x % p == 0) {
            lli prime_power = 0;
            while (x % p == 0) {
                x /= p;
                prime_power++;
            }
            answer.push_back(make_pair(p, prime_power));
        }
        else if (p * p > x) {
            answer.push_back(make_pair(x, 1));
            break;
        }
    } return answer;
}

vector<vector<lli>> multiply_square_matrices(vector<vector<lli>>& a, vector<vector<lli>>& b, lli mod) {
    int n = a.size();
    vector<vector<lli>> result(n, vector<lli>(n, 0));
    vector<vector<__int128>> temp(n, vector<__int128>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                temp[i][j] = (temp[i][j] + ((__int128) a[i][k] * b[k][j]));
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = temp[i][j] % mod;
        }
    }
    return result;
}

vector<vector<lli>> matrix_power(vector<vector<lli>> base, lli exp, lli mod) {
    int n = base.size();
    vector<vector<lli>> result(n, vector<lli>(n, 0));
    for (int i = 0; i < n; ++i) result[i][i] = 1;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = multiply_square_matrices(result, base, mod);
        }
        base = multiply_square_matrices(base, base, mod);
        exp /= 2;
    }
    return result;
}

bool is_period(lli n, lli mod) {
    vector<vector<lli>> result = matrix_power(fibonacciMatrix, n, mod);
    return result[0][0] == 1 && result[0][1] == 0 && result[1][1] == 1;
}

lli smallest_divisor_period(lli x, lli mod) {
    vector<pair<lli, lli>> factorization = prime_decomposition(x);
    for (int i = 0; i < factorization.size(); i++) {
        // If p is period so is any multiple of p. So we are just taking away multiples of p
        // to arrive at the smallest divisor.
        while (x % factorization[i].first == 0 && is_period(x / factorization[i].first, mod))
            x /= factorization[i].first;
    }
    return x;
}

lli pisano_prime(lli p) {
    if (p == 2) return 3;
    if (p == 5) return 20;
    if (p % 10 == 1 || p % 10 == 9) return smallest_divisor_period(p - 1, p);
    return smallest_divisor_period(2 * (p + 1), p);
}

__int128 pisano(lli x) {
    vector<pair<lli, lli>> factorization = prime_decomposition(x);
    __int128 ans = 1;
    for (int i = 0; i < factorization.size(); i++) {
        __int128 pp = pisano_prime(factorization[i].first);
        for (int j = 1; j < factorization[i].second; j++) {
            pp *= factorization[i].first;
        }
        ans = lcm(ans, pp);
    }
    return ans;
}
