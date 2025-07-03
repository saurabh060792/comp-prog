#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;

int const ALPHABET_SIZE = 256;

vector<int> suffix_array(string s);
vector<int> sort_cyclic_shifts(const string &s);
int substring_lower_bound(const string &t, const string &s, const vector<int> &p);
int substring_upper_bound(const string &t, const string &s, const vector<int> &p);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    string s, t;
    cin >> t;
    vector<int> p = suffix_array(t);
    cin >> q;
    while (q--) {
        cin >> s;
        cout << (substring_upper_bound(t, s, p) - substring_lower_bound(t, s, p)) << "\n";
    }
    return 0;
}

int substring_lower_bound(const string &t, const string &s, const vector<int> &p) {
    int l = -1, r = p.size(), m;
    while (r - l > 1) {
        m = (l + r) / 2;
        if (t.substr(p[m], s.size()) < s) l = m;
        else r = m;
    }
    return ++l;
}

int substring_upper_bound(const string &t, const string &s, const vector<int> &p) {
    int l = -1, r = p.size(), m;
    while (r - l > 1) {
        m = (l + r) / 2;
        if (t.substr(p[m], s.size()) <= s) l = m;
        else r = m;
    }
    return r;
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
    s += "$";
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}
