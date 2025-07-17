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

// https://codeforces.com/problemset/problem/388/A
int main() {
    int l, r, m;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        count_by_strength[a[i]]++;
    }


    // Here we have to find minimum. So we start l where
    // solution is not possible and r where solution is
    // definitly possible. Then we binary search to find
    // the minimum solution.
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
    for (auto c : count_by_strength) {
        cnt = c.second;
        if (cnt > (w - i) + (c.first - j)*w) return false;
        else {
            if (cnt < w - i) i += cnt;
            else {
                cnt -= (w - i);
                i = cnt % w;
                j++;
                j += (cnt / w);
            }
        }
    }
    return true;
}
