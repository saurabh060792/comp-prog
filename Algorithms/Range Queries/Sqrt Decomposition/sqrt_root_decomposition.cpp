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

}

void update(int idx, int val) {

}
