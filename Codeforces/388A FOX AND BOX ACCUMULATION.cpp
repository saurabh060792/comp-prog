#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>

#define MAX 1000010

using namespace std;

typedef long long int lli;

int a[MAX], n;
map<int, int> count_by_strength;

bool check(int w);

int main() {
    int l, r, m;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        count_by_strength[a[i]]++;
    }

    l = 0, r = 100;
    while (r - l > 1) {
        m = (l + r) / 2;
        if (check(m)) r = m;
        else l = m;
    }
    printf("%d\n", r);
    return 0;
}

bool check(int w) {
    int cnt, i = 0, j = 0;
    // Imagine filling up 2d box with width w starting
    // from (i, j). So lets say we have "cnt" number of
    // a[i]'s that we have to fill. Then j th row
    // can have (w-i) and the we can only fill till
    // a[i] so we will have (a[i] - j)*w cells to fill.
    for (auto c : count_by_strength) {
        cnt = c.second;
        if (cnt > (w - i) + (c.first - j)*w) return false;
        else {
            if (cnt < w - i) i += cnt;
            else {
                cnt -= (w - i);
                i = cnt % w;
                j++;
                j += ceil(cnt / w);
            }
        }
    }
    return true;
}
