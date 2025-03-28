#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 110

using namespace std;

typedef long long int lli;

int limit[MAX], speed[MAX];

int main() {
    freopen("speeding.in", "r", stdin);
    freopen("speeding.out", "w", stdout);

    int j = 0, k = 0, n, m, a, b, max_over_limit = 0;
    cin>>n>>m;
    
    for (int i = 0; i < n; i++) {
        cin>>a>>b;
        for (int j = 0; j < a; j++) {
            limit[k] = b;
            k++;
        }
    }

    k = 0;
    for (int i = 0; i < m; i++) {
        cin>>a>>b;
        for (int j = 0; j < a; j++) {
            speed[k] = b;
            k++;
        }
    }

    for (int i = 0; i < 100; i++) {
        if (speed[i] - limit[i] > max_over_limit) max_over_limit = speed[i] - limit[i];
    }

    cout<<max_over_limit<<endl;
    return 0;
}
