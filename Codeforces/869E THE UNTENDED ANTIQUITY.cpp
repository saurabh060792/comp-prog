#include <iostream>
#include <map>
#include <random>
#include <chrono>

#define MAX 2510
#define INF 1000000007

using namespace std;

typedef long long int lli;

void update(int x, int y, lli delta);
lli query(int x, int y);

map<pair<pair<int,int>, pair<int,int> >, lli> assigned_value;
lli bit[MAX][MAX];

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int n, m, q, q_type, r1, c1, r2, c2;
    lli delta;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < q; i++) {
        scanf("%d%d%d%d%d", &q_type, &r1, &c1, &r2, &c2);
        if (q_type == 1) {
            delta = uniform_int_distribution<lli>(1, INF)(rng);
            assigned_value[{{r1, c1}, {r2, c2}}] = delta;
            update(r1, c1, delta);
            update(r1, c2 + 1, -delta);
            update(r2 + 1, c1, -delta);
            update(r2 + 1, c2 + 1, delta);
        } else if (q_type == 2) {
            delta = assigned_value[{{r1, c1}, {r2, c2}}];
            assigned_value[{{r1, c1}, {r2, c2}}] = 0;
            update(r1, c1, -delta);
            update(r1, c2 + 1, delta);
            update(r2 + 1, c1, delta);
            update(r2 + 1, c2 + 1, -delta);
        } else {
            lli res1 = query(r1, c1);
            lli res2 = query(r2,c2);
            if (res1 == res2) printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}

void update(int x, int y, lli delta) {
    for (int i = x; i <= MAX; i += i&(-i))
        for (int j = y;j <= MAX; j += j&(-j))
            bit[i][j] += delta;
}

lli query(int x, int y) {
    lli res = 0;
    for (int i = x; i > 0 ; i -= i&(-i))
        for (int j = y; j > 0 ; j -= j&(-j))
            res += bit[i][j];
    return res;
}
