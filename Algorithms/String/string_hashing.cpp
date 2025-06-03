#include <bits/stdc++.h>

#define MAX 1510
#define PRIME_BASE 31
#define HASH_MOD 9223372036854775783
#define ALPHABET_SIZE 26

using namespace std;

typedef long long int lli;

void compute_prime_powers();
void compute_hash(char *s);

__int128 prime_power[MAX], hash_value[MAX];
int bad_character[ALPHABET_SIZE], num_bad_character[MAX][MAX], n;
unordered_set<lli> unique_hash;
char s[MAX], t[MAX];

// https://codeforces.com/contest/271/problem/D
// https://cp-algorithms.com/string/string-hashing.html
int main() {
    int k, num_good_substring = 0;
    scanf("%s %s", s, t);
    n = strlen(s);
    for (int i = 0; i < ALPHABET_SIZE; i++) bad_character[i] = (t[i] == '0');
    scanf("%d", &k);

    compute_prime_powers();
    compute_hash(s);

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) num_bad_character[i][j] = bad_character[s[j] - 'a'];
            else num_bad_character[i][j] = num_bad_character[i][j - 1] + bad_character[s[j] - 'a'];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            __int128 cur_h = (hash_value[j] - ((i > 0) * hash_value[i - 1]) + HASH_MOD) % HASH_MOD;
            // When subtracting hashes we get hash of the string * p^i. So we have to normalize it by
            // multiplying it with p^(n-i-1) to raise the prime power to n-1 so that we can compare
            // different substring.
            cur_h = (cur_h * prime_power[n - i - 1]) % HASH_MOD;
            if (!unique_hash.count(cur_h)) num_good_substring += (num_bad_character[i][j] <= k);
            unique_hash.insert(cur_h);
        }
    }
    printf("%d\n", num_good_substring);

    return 0;

}

void compute_prime_powers() {
    prime_power[0] = 1;
    for (int i = 1; i <= n; i++) prime_power[i] = (prime_power[i - 1] * PRIME_BASE) % HASH_MOD;
}

void compute_hash(char *s) {
    __int128 temp_hash = 0;
    for (int i = 0; i < strlen(s); i++) {
        // Assigning a to 0 is not a good idea because then the hashes of the strings
        // a, aa, aaa, aaaa etc will all evaluate to 0.
        temp_hash = (temp_hash + (s[i] - 'a' + 1) * prime_power[i]) % HASH_MOD;
        hash_value[i] = temp_hash;
    }
}