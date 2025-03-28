#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 110

using namespace std;

typedef long long int lli;


int main() {
    freopen("shell.in", "r", stdin);
    int n, a[MAX], b[MAX], g[MAX], correct, max_correct = 0;
    cin>>n;
    for (int i = 0; i < n; i++) cin>>a[i]>>b[i]>>g[i];

    for (int i = 1; i <= 3; i++) {
        correct = 0;
        int ic[3] = {1, 2, 3};
        for (int j = 0; j < n; j++) {
            swap(ic[a[j] - 1], ic[b[j] - 1]);
            // cout<<ic[0]<<" "<<ic[1]<<" "<<ic[2]<<endl;
            if (ic[g[j] - 1] == i) correct++;
        }
        if (correct > max_correct) max_correct = correct;
    }
    freopen("shell.out", "w", stdout);
    cout<<max_correct<<endl;
    return 0;
}