#include <iostream>
#include <unordered_set>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

int const MAX = 102, MOD = 1000000007;

string s[MAX];
unordered_set<char> unique_characters;

int main() {
    int n, m;
    lli ans = 1;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int j = 0; j < m; j++) {
        unique_characters.clear();
        for (int i = 0; i < n; i++) {
            unique_characters.insert(s[i][j]);
        }
        ans = (ans * unique_characters.size()) % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}
