#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <deque>

#define MAX 2002
#define INF_MEMSET 0x3f

using namespace std;

typedef long long int lli;

void bfs();
bool isValidCoordinate(int r, int c);

int n, m, sr, sc, x, y, ld[MAX][MAX], r[4] = {1, 0, -1, 0}, c[4] = {0, -1, 0, 1};
char matrix[MAX][MAX];

int main() {
    int count = 0;
    scanf("%d%d%d%d%d%d", &n, &m, &sr, &sc, &x, &y);
    sr--;
    sc--;
    for (int i = 0; i < n; i++) scanf("%s", matrix[i]);
    bfs();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (ld[i][j] <= x && ld[i][j] + j - sc <= y) count++;
        }
    }
    printf("%d\n", count);
}

void bfs() {
    int ur, uc, vr, vc, w;
    memset(ld, INF_MEMSET, sizeof(ld));
    ld[sr][sc] = 0;
    deque<pair<int, int>> q;
    q.push_front({sr, sc});
    while (!q.empty()) {
        auto u = q.front();
        ur = u.first;
        uc = u.second;
        q.pop_front();
        for (int i = 0; i < 4; i++) {
            vr = ur + r[i];
            vc = uc + c[i];
            if (!isValidCoordinate(vr, vc)) continue;
            w = vc < uc ? 1 : 0;
            if (ld[vr][vc] > ld[ur][uc] + w) {
                ld[vr][vc] = ld[ur][uc] + w;
                if (w == 1) q.push_back({vr, vc});
                else q.push_front({vr, vc});
            }
        }
    }
}

bool isValidCoordinate(int r, int c) {
    if (r < 0 || r >= n || c < 0 || c >= m || matrix[r][c] == '*') return false;
    return true;
}
