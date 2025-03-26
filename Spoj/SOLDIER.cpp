#include <iostream>
#include <algorithm>
#include <vector>

#define INVALID 1000000000

using namespace std;

typedef long long int lli;

int main() {
    lli t, n, type, price, quality, dp[7][1010];
    vector<vector<pair<lli, lli>>> gears(7, vector<pair<lli, lli>>());
    cin>>n>>t;
    for (int i = 0; i < n; i++) {
        cin>>type>>price>>quality;
        gears[type].push_back(make_pair(price, quality));
    }

    for (int i = 0; i <= t; i++) dp[0][i] = INVALID;
    for (int i = 1; i <= 6; i++) {
        for (int j = 0; j <= t; j++) {
            dp[i][j] = dp[i][j - 1];
            for (auto & gear : gears[i]) {
                if (gear.first > j) continue;
                dp[i][j] = max(dp[i][j], min(gear.second, dp[i-1][j - gear.first]));
            }
        }
    }

    cout<<dp[6][t]<<endl;
    return 0;
}
