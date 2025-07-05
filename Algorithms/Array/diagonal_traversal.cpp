#include <iostream>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

int const MAX = 2003;

lli d1[2 * MAX], d2[2 * MAX];
int a[MAX][MAX];

// https://codeforces.com/problemset/problem/463/C
int main() {
    int n;
    lli d1_max = -1, d2_max = -1, cell_ans;
    pii p1, p2;
    scanf("%d", &n);

    //     0 1 2 3
    //    --------
    // 0 | a b c d
    // 1 | e f g h
    // 2 | i j k l
    // 3 | m n o p
    // 
    // Traversing by (i + j) and (i - j + n - 1) will give us element in
    //  (i+j)   element        (i-j+n)  element
    //    0     a                 0     d
    //    1     e, b              1     c, h
    //    2     i, f, c           2     b, g, l
    //    3     m, j, g, d        3     a, f, k, p
    //    4     n, k, h           4     e, j, 0
    //    5     o, l              5     i, n
    //    6     p                 6     m
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
            d1[i + j] += a[i][j];
            d2[i - j + n - 1] += a[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cell_ans = d1[i + j] + d2[i - j + n - 1] - a[i][j];
            if ((i + j) % 2 && cell_ans > d1_max) {
                d1_max = cell_ans;
                p1 = {i, j};
            } else if (((i + j) % 2 == 0) && cell_ans > d2_max) {
                d2_max = cell_ans;
                p2 = {i, j};
            }
        }
    }
    printf("%lld\n%d %d %d %d", d1_max + d2_max, p1.first + 1, p1.second + 1, p2.first + 1, p2.second + 1);
    return 0;
}
