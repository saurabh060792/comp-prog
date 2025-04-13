#include <iostream>
#include <cstring>

#define MAX 1050

using namespace std;

typedef long long int lli;

void update(int x, int y, lli delta);
lli query(int x1, int y1, int x2, int y2);
lli query(int x, int y);

lli bit[MAX][MAX], mat[MAX][MAX];

int main() {
    int t, n, x1, y1, x2, y2;
    lli num;
    char cmd[10];
    string q_type;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        memset(bit, 0, sizeof(bit));
        memset(mat, 0, sizeof(mat));
        while(1) {
            scanf(" %s", cmd);
            if (cmd[1] == 'E') {
                scanf("%d%d%lld", &x1, &y1, &num);
                x1++, y1++;
                update(x1, y1, num - mat[x1][y1]);
                mat[x1][y1]  = num;
            } else if (cmd[1] == 'U') {
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                x1++, y1++, x2++, y2++;
                printf("%lld\n", query(x1, y1, x2, y2));
            } else break;
        }
    }
    return 0;
}

void update(int x, int y, lli delta) {
    for (int i = x; i <= MAX; i += i&(-i))
        for (int j = y;j <= MAX; j += j&(-j))
            bit[i][j] += delta;
}

lli query(int x1, int y1, int x2, int y2) {
    return query(x1 - 1, y1 - 1) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x2, y2);
}

lli query(int x, int y) {
    lli res = 0;
    for (int i = x; i > 0 ; i -= i&(-i))
        for (int j = y; j > 0 ; j -= j&(-j))
            res += bit[i][j];
    return res;
}
