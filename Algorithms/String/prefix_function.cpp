#include <iostream>
#include <vector>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;

vector<int> prefix_function(string s);

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=396
int main() {
    int t, period, n;;
    string s;
    scanf("%d", &t);
    while (t--) {
        cin >> s;
        vector<int> pi = prefix_function(s);
        n = s.length();
        period = n - pi[n - 1];
        printf("%d\n", n % period ? n : period);
        if (t) printf("\n");
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
