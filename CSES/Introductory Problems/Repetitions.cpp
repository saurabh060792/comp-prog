#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

lli const MAX = 2000001, MOD = 1000000007;

string s;

int main() {
    int n, ans, max_ans = -1, i;
    cin >> s;
    n = s.length();
    i = 0;
    while (i < n) {
        ans = 1;
        while (i < n && s[i] == s[i - 1]) {
            ans++;
            i++;
        }
        max_ans = max(max_ans, ans);
        i++;
    }
    printf("%d\n", max_ans);
    return 0;
}
