#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;

int const ALPHABET_SIZE = 256;

vector<int> suffix_array(string s);
vector<int> sort_cyclic_shifts(string s);
bool substring_search(string t, string s, vector<int> p);
bool less(string t, string s, int id);

int main() {
    int q;
    string s, t;
    cin >> t;
    vector<int> p = suffix_array(t);
    scanf("%d", &q);
    while (q--) {
        cin>>s;
        cout<<((substring_search(t, s, p)) ? "Yes" : "No")<<"\n";
    }
    return 0;
}

bool substring_search(string t, string s, vector<int> p) {
    // for (auto i : p) printf("%d ", i);
    // printf("\n");
    int l = 0, r = p.size() - 1, m;
    while (r - l > 1) {
        m = (l + r)/2;
        string temp = t.substr(p[m], s.size());
        // cout<<temp<<endl;
        if (temp < s) l = m;
        else r = m;
        // printf("l: %d r: %d\n", l, r);
    }
    return t.substr(p[r], s.size()) == s;
}

vector<int> sort_cyclic_shifts(string s) {
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