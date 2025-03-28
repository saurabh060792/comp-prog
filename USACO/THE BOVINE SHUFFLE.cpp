#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 110

using namespace std;

typedef long long int lli;

int main() {
    freopen("shuffle.in", "r", stdin);
    freopen("shuffle.out", "w", stdout);

    int n, shuffle[MAX], order[MAX];
    cin>>n;
    for (int i = 0; i < n; i++) cin>>shuffle[i];
    for (int i = 0; i < n; i++) cin>>order[i];

    for (int i = 0; i < 3; i++) {
        int past_order[MAX];
        for (int j = 0; j < n; j++) {
            past_order[j] = order[shuffle[j] - 1];
        }
        for (int j = 0; j < n; j++) order[j] = past_order[j];
    }

    for (int i = 0; i < n; i++) cout<<order[i]<<endl;
    
    return 0;
}
