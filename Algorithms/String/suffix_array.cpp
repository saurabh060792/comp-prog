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

// https://codeforces.com/edu/course/2/lesson/2/1/practice/contest/269100/problem/A
// https://youtu.be/dpu0RDXZAH0?si=OMDH4RL5qN0kQ-U3
int main() {
    string s;
    cin >> s;
    vector<int> p = suffix_array(s);
    for (auto i : p) printf("%d ", i);
    printf("\n");
    return 0;
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
vector<int> sort_cyclic_shifts(string s) {
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
    s += "$";
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}
