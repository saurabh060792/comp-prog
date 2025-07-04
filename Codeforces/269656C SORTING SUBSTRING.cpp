#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int , int> pii;

int const ALPHABET_SIZE = 256, MAX = 400005, MAXLOG = 20;

vector<int> suffix_array(string s);
vector<int> sort_cyclic_shifts(const string &s);
vector<int> lcp_array(const string &s, const vector<int> &p);
void build_sparse_table(vector<int> a);
lli log2_floor(lli i);

vector<pii> ss;
lli minimum[MAXLOG][MAX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q, l, r;
    string s;
    cin >> s;
    n = s.size();
    vector<int> p = suffix_array(s);
    vector<int> lcp = lcp_array(s, p);
    build_sparse_table(lcp);
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++) rank[p[i]] = i;

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> l >> r;
        ss.push_back({l - 1, r - 1});
    }
    sort(ss.begin(), ss.end(), [&s, &rank](pii & a, pii & b) {
        if (a.first == b.first) return a.second < b.second;

        int l, r, lcp;
        lli k;

        if (rank[a.first] > rank[b.first]) l = rank[b.first], r = rank[a.first] - 1;
        else l = rank[a.first], r = rank[b.first] - 1;
        k = log2_floor(r - l + 1);
        lcp = min(minimum[k][l], minimum[k][r - (1 << k) + 1]);

        if (lcp >= a.second - a.first + 1 || lcp >= b.second - b.first + 1) {
            if (a.second - a.first == b.second - b.first) return a < b;
            else return a.second - a.first < b.second - b.first;
        }
        else return s[a.first + lcp] < s[b.first + lcp];
    });

    for (auto i : ss) cout << i.first + 1 << " " << i.second + 1 << "\n";

    return 0;
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
    s += " ";
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

lli log2_floor(lli i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

void build_sparse_table(vector<int> a) {
    int n = a.size();
    lli k = log2_floor(n);
    for (int i = 0; i < n; i++) minimum[0][i] = a[i];
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= n - (1 << i); j++) {
            minimum[i][j] = min(minimum[i - 1][j], minimum[i - 1][j + (1 << (i - 1))]);
        }
    }
}
