#include <bits/stdc++.h>

#define MAX 500005
#define BLOCK_SIZE 700

using namespace std;

typedef long long int lli;

int query(int l, int r, int c);
void update(int idx, int val);

vector<int> block[MAX / BLOCK_SIZE + 10];
int arr[MAX];

int main() {
    int n, q, q_type, l, r, c, new_value;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        block[i / BLOCK_SIZE].push_back(arr[i]);
    }
    for (int i = 0; i <= MAX / BLOCK_SIZE + 10; i++) sort(block[i].begin(), block[i].end());

    scanf("%d", &q);
    while (q--) {
        scanf("%d", &q_type);
        if (q_type == 0) {
            scanf("%d%d%d", &l, &r, &c);
            printf("%d\n", query(l - 1, r - 1, c));
        }
        else {
            scanf("%d%d", &l, &new_value);
            update(l - 1, new_value);
        }
    }
}

int query(int l, int r, int c) {
    int ans = 0;
    int bl = l / BLOCK_SIZE, br = r / BLOCK_SIZE;
    if (bl == br) {
        for (int i = l; i <= r; i++) if (arr[i] >= c) ans++;
    } else {
        for (int i = l, end = (bl + 1) * BLOCK_SIZE - 1; i <= end; i++) if (arr[i] >= c) ans++;
        // https://stackoverflow.com/a/41958622/1056672
        for (int i = bl + 1; i < br; i++) ans += (block[i].size() - (lower_bound(block[i].begin(), block[i].end(), c) - block[i].begin()));
        for (int i = br * BLOCK_SIZE; i <= r; i++) if (arr[i] >= c) ans++;
    }
    return ans;
}

void update(int idx, int val) {
    int block_id = idx / BLOCK_SIZE;
    int val_sorted_idx = lower_bound(block[block_id].begin(), block[block_id].end(), arr[idx]) - block[block_id].begin();
    block[block_id][val_sorted_idx] = arr[idx] = val;
    sort(block[block_id].begin(), block[block_id].end());
}
