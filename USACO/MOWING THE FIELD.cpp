#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <random>

#define MAX 6000
#define INF 1000000000

using namespace std;

typedef long long int lli;

int matrix[MAX][MAX];

int main() {
    freopen("mowing.in", "r", stdin);
    freopen("mowing.out", "w", stdout);
    int n, dist, time = 0, x = 3000, y = 3000, min_time = INF;
    char ch;
    cin>>n;
    for (int i = 0; i < n; i++) {
        cin>>ch>>dist;
        if (ch == 'N') {
            for (int j = 0; j < dist; j++) {
                x--;
                if (matrix[x][y] > 0) min_time = min(min_time, time - matrix[x][y]);
                matrix[x][y] = time;
                time++;
            }
        }
        if (ch == 'S') {
            for (int j = 0; j < dist; j++) {
                x++;
                if (matrix[x][y] > 0) min_time = min(min_time, time - matrix[x][y]);
                matrix[x][y] = time;
                time++;
            }
        }
        if (ch == 'E') {
            for (int j = 0; j < dist; j++) {
                y++;
                if (matrix[x][y] > 0) min_time = min(min_time, time - matrix[x][y]);
                matrix[x][y] = time;
                time++;
            }
        }
        if (ch == 'W') {
            for (int j = 0; j < dist; j++) {
                y--;
                if (matrix[x][y] > 0) min_time = min(min_time, time - matrix[x][y]);
                matrix[x][y] = time;
                time++;
            }
        }
    }
    cout<<(min_time == INF ? -1 : min_time)<<endl;
    return 0;
}
