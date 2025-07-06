#include <iostream>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

int const MAX = 1000006;

lli a[MAX];
set<lli> r_set;
map<lli, int> r_map;

int main() {
    lli n, r, r1, r2, r1_count, r2_count;
    scanf("%lld", &n);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    sort(a, a + n);
    if (n == 1) printf("-1\n");
    else if (n == 2) {
        r = a[1] - a[0];
        if (r % 2) printf("2\n%lld %lld", a[0] - r, a[1] + r);
        else {
            if (r > 0) printf("3\n%lld %lld %lld", a[0] - r, a[0] + r / 2, a[1] + r);
            else printf("1\n%lld\n", a[0]);
        }
    } else {
        for (int i = 1; i < n; i++) {
            r_set.insert(a[i] - a[i - 1]);
            r_map[a[i] - a[i - 1]]++;
        }
        if (r_set.size() == 1) {
            r = a[1] - a[0];
            if (r > 0) printf("2\n%lld %lld\n", a[0] - r, a[n - 1] + r);
            else printf("1\n%lld\n", a[0]);
        }
        else if (r_set.size() >= 3) printf("0\n");
        else {
            r1 = *r_set.begin();
            r2 = *r_set.rbegin();
            if (r1 > r2) swap(r1, r2);
            r2_count = r_map[r2];
            if (r2_count > 1 || r1 * 2 != r2) printf("0\n");
            else {
                for (int i = 1; i < n; i++) {
                    if (a[i] - a[i - 1] == r2) {
                        printf("1\n%lld\n", a[i - 1] + r2 / 2);
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
