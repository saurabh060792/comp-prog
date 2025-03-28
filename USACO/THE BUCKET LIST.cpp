#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 1100

using namespace std;

typedef long long int lli;

int usage[MAX];

int main() {
    freopen("blist.in", "r", stdin);
    freopen("blist.out", "w", stdout);

    int n, s[MAX], t[MAX], b[MAX], max_bucket = 0;
    cin>>n;
    for (int i = 0; i < n; i++) cin>>s[i]>>t[i]>>b[i];
    for (int i = 0; i < n; i++) {
        usage[s[i]] += b[i];
        usage[t[i] + 1] -= b[i];
    }
    for (int i = 1; i < MAX; i++) usage[i] += usage[i - 1];
    for (int i = 1; i < MAX; i++) if (usage[i] > max_bucket) max_bucket = usage[i];
    cout<<max_bucket<<endl;
    return 0;
}
