#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <tuple>

#define MAX 1100
#define INF 1000000000

using namespace std;

typedef long long int lli;


int main() {
    freopen("cbarn.in", "r", stdin);
    freopen("cbarn.out", "w", stdout);

    int n, r[MAX], dist, total, min_total = INF, j;
    cin>>n;
    for (int i = 0; i < n; i++) cin>>r[i];

    for (int i = 0; i < n; i++) {
        dist = total = 0;
        j = i;
        do {
            total += r[j] * dist;
            dist++;
            j = (j + 1) % n;
        } while (j != (i + n) % n);
        if (total < min_total) min_total = total;
    }
    cout<<min_total<<endl;
    return 0;
}
