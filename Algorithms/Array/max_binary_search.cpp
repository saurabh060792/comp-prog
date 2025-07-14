#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

lli const MAX = 2000000000012, MOD = 1000000007;

string s;
lli nb, ns, nc, pb, ps, pc, ruble, ib, is, ic;

bool check(lli h);
lli num_hamburger(lli n, lli i);

int main() {
    lli l, r, m;
    cin >> s;
    scanf("%lld%lld%lld%lld%lld%lld%lld", &nb, &ns, &nc, &pb, &ps, &pc, &ruble);
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'B') ib++;
        if (s[i] == 'S') is++;
        if (s[i] == 'C') ic++;
    }

  
    l = 0, r = MAX;
    while (r - l > 1) {
        m = (l + r) / 2;
        if (check(m)) l = m;
        else r = m;
    }
    printf("%lld\n", l);
    return 0;
}

bool check(lli h) {
    lli initial_h, leftb, lefts, leftc, extrab, extras, extrac;
    initial_h = min(num_hamburger(nb, ib), min(num_hamburger(ns, is), num_hamburger(nc, ic)));
    if (initial_h >= h) return true;

    h -= initial_h;
    leftb = nb - initial_h * ib;
    lefts = ns - initial_h * is;
    leftc = nc - initial_h * ic;
    extrab = max(0LL, h * ib - leftb);
    extras = max(0LL, h * is - lefts);
    extrac = max(0LL, h * ic - leftc);
    return (extrab * pb + extras * ps + extrac * pc) <= ruble;
}

lli num_hamburger(lli n, lli i) {
    if (i == 0) return LLONG_MAX;
    else return n / i;
}
