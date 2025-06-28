#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define MAX 200005

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;

vector<int> z_function(string s);

lli freq[MAX];

// https://codeforces.com/contest/432/problem/D
int main() {
    int n;
    string s;
    cin >> s;
    n = s.length();
    vector<int> z = z_function(s);
    vector<pair<int, lli>> ans;
    for (int i = 0; i < n; i++) freq[z[i]]++;
    for (int i = n - 1; i >= 0; i--) freq[i] += freq[i + 1];
    for (int i = 0; i < n; i++) freq[i]++;
    for (int i = 0; i < n; i++) if (z[i] == n - i) ans.push_back(make_pair(z[i], freq[z[i]]));
    printf("%d\n", ans.size() + 1);
    sort(ans.begin(), ans.end());
    for (auto i : ans) printf("%d %lld\n", i.first, i.second);
    printf("%d 1\n", n);
    return 0;
}


// The z[i] of string s is the length of longest substring
// starting at i which also the prefix of s.
// Eg
// 0 1 2 3 4 5 6 7
// a b a b x y z a b a b x y z
// |_____|       |_____|
//             z[7] = 4
vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);

    // We maintain a string segment denoted by [l, r] which is
    // the rightmost segment (ie it ends rightmost) that matches
    // with the prefix and contains i.
    // Eg
    // 0 1 2 3 4 5   l=7   i     r=13
    // a b a b x y z a b a b x y z
    // |___________| |___________|
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        // When i is between [l, r], then we can
        // Case 1:
        // Initialize z[i] with z[i - l] as illustrated below:
        //
        //      z[l-i] = 3
        //  ___     ___                       ___
        // |   |   |   |             l       |   |        r
        // a b c d a b c e ......... a b c d a b c e ......
        // |____________________|    |_______i____________|
        //
        // Now s[l..r] == s[0..r-l], that means z[i] is equal
        // to z[i - l] and we couldn't extend it, that is the
        // while loop will not trigger as we couldn't extend
        // z[i], otherwise z[i - l] would be extendable.
        //
        // Case 2:
        // Sometime z[i - l] is to much as it pushes z[i]
        // beyond r which we cannot guarentee as we have
        // not seen any character beyond r. Eg
        //
        //         z[l-i] = 5
        //  _______   _______                  _______
        // |       | |       |      l         |   r   |
        // a b c d e a b c d e .... a b c d e a b c x y
        // |_____________|          |_________i___|
        //
        // Now s[l..r] == s[0..r-l], and now if we initialize
        // z[i] to z[i - l] then it will go beyond r and we can
        // see from the example that it will be incorrect. So
        // we have to clip z[i] till r. Hence z[i] will be
        // r - i + 1.
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}
