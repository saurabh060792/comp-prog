#include <bits/stdc++.h>

using namespace std;

#define MAX 500005

typedef long long int lli;

int arr[MAX], freq[MAX];
lli hash_value[MAX], prefix_hash[MAX], ans;
vector<queue<int>> indices(MAX);
unordered_map<lli, int> hash_freq;

int main() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    int n, l, r;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
        hash_value[arr[i]] = uniform_int_distribution<lli>(1, LLONG_MAX)(rng);
    }

    // https://codeforces.com/blog/entry/82643
    hash_freq[0]++;
    l = 0;
    for (int i = 1; i <= n; i++) {
        if (indices[arr[i]].size() >= 4) {
            int leftmost_index = indices[arr[i]].front();
            indices[arr[i]].pop();
            while (l <= leftmost_index) hash_freq[prefix_hash[l++]]--;
        }

        int pre_freq = freq[arr[i]];
        freq[arr[i]] = (freq[arr[i]] + 1) % 3;
        prefix_hash[i] = prefix_hash[i - 1] + (freq[arr[i]] - pre_freq) * hash_value[arr[i]];
        ans += hash_freq[prefix_hash[i]];
        hash_freq[prefix_hash[i]]++;
        indices[arr[i]].push(i);
    }
    printf("%lld\n", ans);
    return 0;
}
