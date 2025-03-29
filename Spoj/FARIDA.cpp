#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 10100

using namespace std;

typedef long long int lli;

int main() {
    lli t, n, dp[MAX], arr[MAX];
    cin>>t;
    for (int c = 1; c <= t; c++) {
        cin>>n;
        for (int i = 0; i < n; i++) {
            cin>>arr[i];
            dp[i] = 0;
        }
        dp[0] = arr[0];
        dp[1] = max(arr[0], arr[1]);
        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i-2] + arr[i], dp[i-1]);
        }
        cout<<"Case "<<c<<": "<<dp[n-1]<<endl;
    }
    return 0;
}
