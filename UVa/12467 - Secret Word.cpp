#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> prefix_function(string s);

int main() {
    int t, n;
    string s, rev_s;
    scanf("%d", &t);
    while (t--) {
        cin >> s;
        rev_s = s;
        reverse(rev_s.begin(), rev_s.end());
        s += "#";
        s += rev_s;
        vector<int> pi = prefix_function(s);
        n = s.length();
        int i = n - 1, max_pi = -1;
        while (s[i] != '#') max_pi = max(max_pi, pi[i--]);
        cout << s.substr(n - max_pi , max_pi) << "\n";
    }
    return 0;
}

vector<int> prefix_function(string s) {
    int n = s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
