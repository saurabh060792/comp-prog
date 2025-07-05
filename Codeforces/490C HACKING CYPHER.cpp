#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

int const MAX = 1000006;

lli rem_b[MAX], ten_b[MAX];

int main() {
    lli a, b, rem = 0, n, curr_rem_a = 0, curr_rem_b;
    string s;
    cin >> s;
    n = s.size();
    scanf("%lld%lld", &a, &b);

    if (n == 1) printf("NO\n");

    ten_b[0] = 1;
    for (int i = 1; i <= n; i++) ten_b[i] = (ten_b[i - 1] * 10) % b;
    for (int i = n - 1; i >= 0; i--) {
        rem = (rem + ((s[i] - '0') * ten_b[n - i - 1])) % b;
        rem_b[i] = rem;
    }
    for (int i = 0; i < n - 1; i++) {
        curr_rem_a = (curr_rem_a * 10 + s[i] - '0') % a;
        curr_rem_b = (rem_b[i] + b - ((ten_b[n - i - 1] * (s[i] - '0')) % b)) % b;
        if (curr_rem_a == 0 && curr_rem_b == 0 && s[i + 1] != '0') {
            printf("YES\n");
            cout << s.substr(0, i + 1) << "\n" << s.substr(i + 1, n - i - 1) << "\n";
            return 0;
        }
    }
    printf("NO\n");
    return 0;
}
