#include <iostream>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;
typedef pair<int, int> pii;

int const MAX = 2003;

lli d1[2 * MAX], d2[2 * MAX];
int a[MAX][MAX];

int main() {
    int n;
    lli d1_max = -1, d2_max = -1, cell_ans;
    pii p1, p2;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
            d1[i + j] += a[i][j];
            d2[i - j + n] += a[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cell_ans = d1[i + j] + d2[i - j + n] - a[i][j];
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
