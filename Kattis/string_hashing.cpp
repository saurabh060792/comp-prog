#include <bits/stdc++.h>

#define MAX 300005
#define PRIME_BASE 31
#define HASH_MOD 9223372036854775783
#define ALPHABET_SIZE 26

using namespace std;

typedef long long int lli;

void compute_prime_powers();
void compute_hash(char *s);
void print_int128(__int128 n);

__int128 prime_power[MAX], hash_value[MAX];
int n;
char s[MAX];

int main() {
    int l, r, q;
    scanf("%s", s);
    n = strlen(s);

    compute_prime_powers();
    compute_hash(s);

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d%d", &l, &r);
        __int128 cur_h = (hash_value[r - 1] - ((l > 0) * hash_value[l - 1]) + HASH_MOD) % HASH_MOD;
        cur_h = (cur_h * prime_power[n - l - 1]) % HASH_MOD;
        print_int128(cur_h);
    }
    return 0;
}

void print_int128(__int128 n) {
    if (n == 0) {
        printf("0\n");
        return;
    }
    vector<int> digits;
    while (n) {
        digits.push_back(n % 10);
        n /= 10;
    }
    reverse(digits.begin(), digits.end());
    for (int i = 0; i < digits.size(); i++) printf("%d", digits[i]);
    printf("\n");
}

void compute_prime_powers() {
    prime_power[0] = 1;
    for (int i = 1; i <= n; i++) prime_power[i] = (prime_power[i - 1] * PRIME_BASE) % HASH_MOD;
}

void compute_hash(char *s) {
    __int128 temp_hash = 0;
    for (int i = 0; i < strlen(s); i++) {
        temp_hash = (temp_hash + (s[i] - 'a' + 1) * prime_power[i]) % HASH_MOD;
        hash_value[i] = temp_hash;
    }
}