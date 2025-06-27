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
