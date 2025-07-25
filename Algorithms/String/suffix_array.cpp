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
bool substring_search(const string &t, const string &s, const vector<int> &p);
int substring_lower_bound(const string &t, const string &s, const vector<int> &p);
int substring_upper_bound(const string &t, const string &s, const vector<int> &p);
vector<int> lcp_array(const string &s, const vector<int> &p);
void build_sparse_table(vector<int> a);
lli log2_floor(lli i);

// https://codeforces.com/edu/course/2/lesson/2/3/practice/contest/269118/problem/A
// https://codeforces.com/edu/course/2/lesson/2/3/practice/contest/269118/problem/B
// https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/C
// https://youtu.be/dpu0RDXZAH0?si=OMDH4RL5qN0kQ-U3
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
        cout << ((substring_search(t, s, p)) ? "Yes" : "No") << "\n";
    }

    // Lcp Calculation given 2 suffix index
    int l, r, lcp;
    lli k;
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++) rank[p[i]] = i;
    if (rank[a.first] > rank[b.first]) l = rank[b.first], r = rank[a.first] - 1;
    else l = rank[a.first], r = rank[b.first] - 1;
    k = log2_floor(r - l + 1);
    lcp = min(minimum[k][l], minimum[k][r - (1 << k) + 1]);
    
    return 0;
}

bool substring_search(const string &t, const string &s, const vector<int> &p) {
    int l = -1, r = p.size(), m;
    while (r - l > 1) {
        m = (l + r) / 2;
        if (t.substr(p[m], s.size()) < s) l = m;
        else r = m;
    }
    return r < p.size() && t.substr(p[r], s.size()) == s;
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

// Sort cyclic shift of s. Eg if s = abbaba$ then its cyclic shifts will be
//
// abbaba$            $abbaba
// bbaba$a            a$abbab
// baba$ab            aba$abb
// aba$abb  --sort--> abbaba$
// ba$abba            ba$abba
// a$abbab            baba$ab
// $abbaba            bbaba$a
vector<int> sort_cyclic_shifts(const string &s) {
    int n = s.size();
    vector<int> p(n), c(n), cnt(max(ALPHABET_SIZE, n), 0);

    // Use counting sort to prepare the base case (k = 0) by
    // sorting all substring of lenght 2^k (= 1).
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

    // S = abbaba$
    // Lets simulate going from k = 1 to 2. After k = 1 step we
    // will have sorted list of substring of length 2^k (= 2).
    // And p[] containing index of sorted substring and c[]
    // containing classes (equal substring getting same class id)
    // of substring with smaller substring getting lower class id.
    //
    // k = 1         k = 2
    // s   p  c      i  s
    //              sort_____
    // $a  6  0    | 0  abba |
    // a$  5  1    | 1  bbab |
    // ab  0  2    | 2  baba |
    // ab  3  2    | 3  aba$ |
    // ba  2  3    | 4  ba$a |
    // ba  4  3    | 5  a$ab |
    // bb  1  4    | 6  $abb |
    //             |_________|
    //
    // To sort, in step 2 (k = 2), we will use radix sort, ie divide
    // 2^k length substring into 2 substrings of length 2^(k-1) and then
    // sort by 2nd and then 1st substring.
    vector<int> pn(n), cn(n);
    for (int k = 0; (1 << k) < n; k++) {
        // For sorting by 2nd substring of lenght 2^(k-1), we notice that
        // it is already sorted in step k-1, we just have to remap the indices
        // because the substring index in step k-1 is not the same for 2nd
        // substring of length 2^(k-1) in step k. For example substring "a$"
        // has index 5 in step k-1 but in step k, "a$" is the 2nd substring
        // of the substring "aba$" which has index 3. In general ith index
        // substring in step k-1 maps to i-2^(k-1)th substring in step k.
        //
        //   2^k-1        1st 2nd
        // | ab 0      |0 ab  ba
        // | bb 1      |1 bb  ab
        // | ba 2   ---|2 ba  ba
        // | ab 3  /   |3 ab  a$
        // | ba 4--    |4 ba  $a
        // | a$ 5      |5 a$  ab
        // | $a 6      |6 $a  bb
        //
        // So to sort by 2nd substring we just subtract 2^(k-1) from p[]
        //     p        sort    sorted
        //              1st__   2nd
        // $a  6      4 | ba |  $a
        // a$  5      3 | ab |  a$
        // ab  0      5 | a$ |  ab
        // ab  3  --> 1 | bb |  ab
        // ba  2      0 | ab |  ba
        // ba  4      2 | ba |  ba
        // bb  1      5 | a$ |  ab
        //              |____|
        // Now the substrings of step k are already sorted by 2nd substring
        // using results from step k-1.
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << k);
            if (pn[i] < 0) pn[i] += n;
        }

        // For sorting 1st substring, we will use c[] array and counting sort.
        // Note that c[] stores classes and smaller string get lower class id.
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];

        // Now we have to create c[] for this step, which is pretty simple.
        // We simply create pair of classes from 2 substring of length 2^(k-1)
        // and compare them.
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            if (cur != prev) classes++;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);

        // If at any point all classes are distinct then we can stop because
        // the final sorted order of all suffixes will be the same as this.
        if (classes == n) break;
    }
    return p;
}

vector<int> suffix_array(string s) {
    // ! is smaller than #, $. So #, $ can be used elsewhere.
    s += "!";
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

// https://youtu.be/dpu0RDXZAH0?si=sKVQPGarpLJG4Ml2&t=4333
vector<int> lcp_array(const string &s, const vector<int> &p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++) rank[p[i]] = i;

    int k = 0;
    vector<int> lcp(n - 1, 0);

    // We will loop from longest to shortest suffix.
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        // j denotes the next suffix index in the sorted list.
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rank[i]] = k;

        // Now we prepare for the next iteration. In the next iteration
        // we will consider a suffix which is one less than current suffix.
        // So if lcp if i, j is k, then lcp of i+1 and j+1 will be exactly
        // k-1.
        // However in the next iteration we are not comparing i+1 with j+1 
        // but we are comparing i+1 with the suffix that is next to it in
        // the sorted arry but we can jump start the comparison in the while
        // loop by k-1. Eg
        // s = aaabab
        // p
        // 0  aaabab  <---  i
        // 1  aabab   <---- j <--- i+1
        // 4  ab
        // 2  abab    <---- j+1
        // 5  b
        // 3  bab
        // For first iteration, k (lcp) = 2. So for suffix i+1 (aabab) and
        // j+1 (abab) lcp will be k-1 (=1) as we are removing the first character
        // from both string. That means in the next iteration we can jump start
        // k with 1 when comparing suffix 1 with 4.
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
