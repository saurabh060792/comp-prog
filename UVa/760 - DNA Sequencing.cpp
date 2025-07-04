#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;

int const ALPHABET_SIZE = 256, PRIME_BASE = 31;
__int128 const HASH_MOD = 9223372036854775783;

vector<int> suffix_array(string s);
vector<int> sort_cyclic_shifts(const string &s);
vector<int> lcp_array(const string &s, const vector<int> &p);
vector<__int128> compute_prime_powers(int n);
vector<__int128> compute_hash(const string &s, const vector<__int128> &prime_power);

unordered_set<lli> unique_hash;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, nm, max_lcs;
    string s, t, seperator = "";
    while (cin >> s >> t) {
        cout << seperator;
        seperator = "\n";
        unique_hash.clear();
        max_lcs = -1;

        n = s.size();
        m = t.size();
        s += "#";
        s += t;
        nm = s.size();
        vector<int> p = suffix_array(s);
        vector<int> lcp = lcp_array(s, p);
        vector<__int128> prime_power = compute_prime_powers(nm);
        vector<__int128> hash_value = compute_hash(s, prime_power);

        for (int i = 0; i < nm - 1; i++) {
            if ((p[i] < n && p[i + 1] < n) || (p[i] > n && p[i + 1] > n)) continue;
            max_lcs = max(max_lcs, lcp[i]);
        }

        if (!max_lcs) {
            cout << "No common sequence.\n";
            continue;
        }
        for (int i = 0; i < nm - 1; i++) {
            if ((p[i] < n && p[i + 1] < n) || (p[i] > n && p[i + 1] > n)) continue;
            if (lcp[i] == max_lcs) {
                __int128 cur_h = (hash_value[p[i] + max_lcs - 1] - ((p[i] > 0) * hash_value[p[i] - 1]) + HASH_MOD) % HASH_MOD;
                cur_h = (cur_h * prime_power[nm - p[i] - 1]) % HASH_MOD;
                if (!unique_hash.count(cur_h)) cout << s.substr(p[i], max_lcs) << "\n";
                unique_hash.insert(cur_h);
            }
        }
    }
    return 0;
}

vector<__int128> compute_prime_powers(int n) {
    vector<__int128> prime_power(n + 1);
    prime_power[0] = 1;
    for (int i = 1; i <= n; i++) prime_power[i] = (prime_power[i - 1] * PRIME_BASE) % HASH_MOD;
    return prime_power;
}

vector<__int128> compute_hash(const string &s, const vector<__int128> &prime_power) {
    int n = s.size();
    __int128 temp_hash = 0;
    vector<__int128> hash_value(n + 1);
    for (int i = 0; i < n; i++) {
        temp_hash = (temp_hash + (s[i] - '#' + 1) * prime_power[i]) % HASH_MOD;
        hash_value[i] = temp_hash;
    }
    return hash_value;
}

vector<int> sort_cyclic_shifts(const string &s) {
    int n = s.size();
    vector<int> p(n), c(n), cnt(max(ALPHABET_SIZE, n), 0);
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < ALPHABET_SIZE; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]])
            classes++;
        c[p[i]] = classes - 1;
    }

    vector<int> pn(n), cn(n);
    for (int k = 0; (1 << k) < n; k++) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << k);
            if (pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            if (cur != prev) classes++;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
        if (classes == n) break;
    }
    return p;
}

vector<int> suffix_array(string s) {
    s += "!";
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

vector<int> lcp_array(const string &s, const vector<int> &p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++) rank[p[i]] = i;

    int k = 0;
    vector<int> lcp(n - 1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rank[i]] = k;
        if (k) k--;
    }
    return lcp;
}
