#include <bits/stdc++.h>

#define MAX 1510
#define PRIME_BASE 31
#define HASH_MOD 9223372036854775783
#define ALPHABET_SIZE 26

using namespace std;

typedef long long int lli;

void compute_prime_powers();
void compute_hash(string const& s);

__int128 prime_power[MAX], hash_value[MAX];
int bad_character[ALPHABET_SIZE], num_bad_character[MAX][MAX];
unordered_set<lli> unique_hash;

int main() {
    string s, t;
    int n, k, num_good_substring = 0;

    printf("here\n");

    scanf("%s %s", s, t);

    printf("here\n");

    for (int i = 0; i < ALPHABET_SIZE; i++) bad_character[i] = (t[i] == 0);
    scanf("%d", &k);
    compute_prime_powers();

    printf("here\n");
    
    compute_hash(s);

    printf("here\n");

    n = s.length();
    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            __int128 cur_h = (hash_value[i + l] - hash_value[i - 1] + HASH_MOD) % HASH_MOD;
            cur_h = (cur_h * prime_power[n-i-1]) % HASH_MOD;
            unique_hash.insert(cur_h);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (i == j) num_bad_character[i][j] = bad_character[s[j]];
            else num_bad_character[i][j] = num_bad_character[i][j-1] + bad_character[s[j]];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) 
            num_good_substring += (num_bad_character[i][j] <= k);
    }
    printf("%d\n", num_good_substring);

    return 0;
}

void compute_prime_powers() {
    prime_power[0] = 1;
    for (int i = 1; i < MAX; i++) prime_power[i] = (prime_power[i-1] * PRIME_BASE) % HASH_MOD;
}

void compute_hash(string const& s) {
    __int128 temp_hash = 0;
    for (int i = 1; i <= s.length(); i++) {
        temp_hash = (temp_hash + (s[i] - 'a' + 1) * prime_power[i]) % HASH_MOD;
        hash_value[i] = temp_hash;
    }
}