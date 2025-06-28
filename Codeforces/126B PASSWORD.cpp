#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define MAX 2000006

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;

vector<int> z_function(string s);

lli freq[MAX];

int main() {
    int n, max_length = -1;
    string s;
    cin >> s;
    n = s.length();
    vector<int> z = z_function(s);
    vector<pair<int, lli>> ans;
    for (int i = 0; i < n; i++) freq[z[i]]++;
    for (int i = n - 1; i >= 0; i--) freq[i] += freq[i + 1];
    for (int i = 0; i < n; i++) freq[i]++;
    for (int i = 0; i < n; i++) {
        if (z[i] == n - i) {
            ans.push_back(make_pair(z[i], freq[z[i]]));
            if (freq[z[i]] > 2) max_length = max(max_length, z[i]);
        }
    }
    cout << (max_length == -1 ? "Just a legend" : s.substr(0, max_length)) << "\n";
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
