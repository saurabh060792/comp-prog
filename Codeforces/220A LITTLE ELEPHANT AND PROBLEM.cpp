#include <iostream>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

int const MAX = 100005;

int a[MAX], s[MAX];

int main() {
    int n, count = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &s[i]);
        a[i] = s[i];
    }
    sort(s, s + n);
    for (int i = 0; i < n; i++) count += (a[i] != s[i]);
    if (count <= 2) printf("YES\n");
    else printf("NO\n");
    return 0;
}


