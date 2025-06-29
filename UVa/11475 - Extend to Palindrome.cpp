#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;

vector<int> z_function(string s);

int main() {
    int n;
    string s, s_rev;
    while (cin >> s) {
        s_rev = s;
        reverse(s_rev.begin(), s_rev.end());
        s_rev += s;
        vector<int> z = z_function(s_rev);
        n = s.length();
        for (int i = n; i < 2 * n; i++) {
            // Try to get longest suffix which is also a prefix in s_rev
            // which is concatination of reverse(s) + s
            if (z[i] == 2 * n - i) {
                cout << s.substr(0, n - z[i]) + s_rev.substr(0, n) << "\n";
                break;
            }
        }
    }
    return 0;
}

vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}
