// TLE with sqrt root decomposition

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 200005
#define INF 1000000009
#define BLOCK_SIZE 500

using namespace std;

typedef long long int lli;

lli query_less_than(int l, int r, int c);
lli query_greater_than(int l, int r, int c);
void update_less_than(int idx, int val);
void update_greater_than(int idx, int val);
lli count_inversion();
lli range_query(int l, int r);
lli prefix_query(int x);
void point_update(int x, lli delta);

vector<lli> block_less_than[MAX / BLOCK_SIZE + 10], block_greater_than[MAX / BLOCK_SIZE + 10];
int arr_less_than[MAX], arr_greater_than[MAX], arr_index[MAX], n;
lli bit[MAX];

int main() {
    int m, x;
    lli inversion_count = 0;

    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i <= n; i++) bit[i] = 0;
        for (int i = 0; i < n / BLOCK_SIZE + 10; i++) block_less_than[i].clear(), block_greater_than[i].clear();

        for (int i = 0; i < n; i++) {
            scanf("%d", &arr_less_than[i]);
            arr_greater_than[i] = arr_less_than[i];
            arr_index[arr_greater_than[i]] = i;
            block_less_than[i / BLOCK_SIZE].push_back(arr_less_than[i]);
            block_greater_than[i / BLOCK_SIZE].push_back(arr_greater_than[i]);
        }
        for (int i = 0; i < n / BLOCK_SIZE + 10; i++) {
            sort(block_less_than[i].begin(), block_less_than[i].end());
            sort(block_greater_than[i].begin(), block_greater_than[i].end());
        }

        inversion_count = count_inversion();

        while (m--) {
            printf("%lld\n", inversion_count);
            scanf("%d", &x);
            // printf("arr_index[%d]: %d\n", x, arr_index[x]);
            lli prefix_subtract = query_greater_than(0, arr_index[x], x);
            lli suffix_subtract = query_less_than(arr_index[x], n - 1, x);
            // printf("prefix subtract: %lld\n", prefix_subtract);
            // printf("suffix subtract: %lld\n", suffix_subtract);
            inversion_count -= (prefix_subtract + suffix_subtract);
            update_less_than(arr_index[x], INF);
            update_greater_than(arr_index[x], -1);
        }
    }
    return 0;
}

lli query_less_than(int l, int r, int c) {
    lli ans = 0;
    int bl = l / BLOCK_SIZE, br = r / BLOCK_SIZE;
    if (bl == br) {
        for (int i = l; i <= r; i++) if (arr_less_than[i] < c) ans++;
    } else {
        for (int i = l, end = (bl + 1) * BLOCK_SIZE - 1; i <= end; i++) if (arr_less_than[i] < c) ans++;
        for (int i = bl + 1; i < br; i++)
            ans += (lower_bound(block_less_than[i].begin(), block_less_than[i].end(), c) - block_less_than[i].begin());
        for (int i = br * BLOCK_SIZE; i <= r; i++) if (arr_less_than[i] < c) ans++;
    }
    return ans;
}

lli query_greater_than(int l, int r, int c) {
    lli ans = 0;
    int bl = l / BLOCK_SIZE, br = r / BLOCK_SIZE;
    if (bl == br) {
        for (int i = l; i <= r; i++) if (arr_greater_than[i] > c) ans++;
    } else {
        for (int i = l, end = (bl + 1) * BLOCK_SIZE - 1; i <= end; i++) if (arr_greater_than[i] > c) ans++;
        // printf("start: %d end: %d ans: %lld\n", l, (bl + 1) * BLOCK_SIZE - 1, ans);
        for (int i = bl + 1; i < br; i++)
            ans += (block_greater_than[i].end() - upper_bound(block_greater_than[i].begin(), block_greater_than[i].end(), c));
        // printf("start: %d end: %d ans: %lld\n", bl + 1, br, ans);
        for (int i = br * BLOCK_SIZE; i <= r; i++) if (arr_greater_than[i] > c) ans++;
        // printf("start: %d end: %d ans: %lld\n", br * BLOCK_SIZE, r, ans);
    }
    return ans;
}

void update_less_than(int idx, int val) {
    int block_id = idx / BLOCK_SIZE;
    int val_sorted_idx = lower_bound(
                             block_less_than[block_id].begin(),
                             block_less_than[block_id].end(),
                             arr_less_than[idx])
                         - block_less_than[block_id].begin();
    block_less_than[block_id][val_sorted_idx] = arr_less_than[idx] = val;
    sort(block_less_than[block_id].begin(), block_less_than[block_id].end());
}

void update_greater_than(int idx, int val) {
    int block_id = idx / BLOCK_SIZE;
    int val_sorted_idx = lower_bound(
                             block_greater_than[block_id].begin(),
                             block_greater_than[block_id].end(),
                             arr_greater_than[idx])
                         - block_greater_than[block_id].begin();
    block_greater_than[block_id][val_sorted_idx] = arr_greater_than[idx] = val;
    sort(block_greater_than[block_id].begin(), block_greater_than[block_id].end());
}

lli count_inversion() {
    lli inversion_count = 0;
    for (int i = 0; i < n; i++) {
        point_update(arr_less_than[i], 1);
        inversion_count += range_query(arr_less_than[i] + 1, n);
    }
    return inversion_count;
}

lli range_query(int l, int r) {
    return prefix_query(r) - prefix_query(l - 1);
}

lli prefix_query(int x) {
    lli res = 0;
    for (int i = x; i > 0; i -= i & (-i)) res += bit[i];
    return res;
}

void point_update(int x, lli delta) {
    for (int i = x; i <= n; i += i & (-i)) bit[i] += delta;
}


// TLE with segment tree

// #include <iostream>
// #include<vector>
// #include <algorithm>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

// #define MAXARRAY 250010
// #define MAXTREE 900040
// #define INF 1000000009

// using namespace std;
// using namespace __gnu_pbds;

// typedef long long int lli;
// typedef tree<lli, null_type, less<lli>, rb_tree_tag, tree_order_statistics_node_update> min_ordered_set;
// typedef tree<lli, null_type, greater<lli>, rb_tree_tag, tree_order_statistics_node_update> max_ordered_set;

// struct segment_tree_node {
//     min_ordered_set less_than_set;
//     max_ordered_set greater_than_set;
// };

// void build(int node, int tl, int tr);
// int query_less_than(int node, int tl, int tr, int l, int r, int k);
// int query_greater_than(int node, int tl, int tr, int l, int r, int k);
// void update(int node, int tl, int tr, int position, lli old_value, lli less_than_value, lli greater_than_value);
// lli count_inversion();
// lli range_query(int l, int r);
// lli prefix_query(int x);
// void point_update(int x, lli delta);

// int n, arr[MAXARRAY], arr_index[MAXARRAY];
// segment_tree_node seg_tree[MAXTREE];
// lli bit[MAXTREE];

// int main() {
//     int m, x;
//     lli inversion_count = 0;

//     while (scanf("%d%d", &n, &m) == 2) {
//         for (int i = 0; i <= n; i++) bit[i] = 0;
//         for (int i = 0; i < 4 * n; i++) seg_tree[i].less_than_set.clear(), seg_tree[i].greater_than_set.clear();

//         for (int i = 0; i < n; i++) {
//             scanf("%d", &arr[i]);
//             arr_index[arr[i]] = i;
//         }

//         inversion_count = count_inversion();
//         // printf("inversion_count: %lld\n", inversion_count);


//         build(1, 0, n - 1);

//         while (m--) {
//             printf("%lld\n", inversion_count);
//             scanf("%d", &x);
//             // printf("arr_index[%d]: %d\n", x, arr_index[x]);
//             lli prefix_subtract = query_greater_than(1, 0, n - 1, 0, arr_index[x], x);
//             lli suffix_subtract = query_less_than(1, 0, n - 1, arr_index[x], n - 1, x);
//             // printf("prefix subtract: %lld\n", prefix_subtract);
//             // printf("suffix subtract: %lld\n", suffix_subtract);
//             inversion_count -= (prefix_subtract + suffix_subtract);
//             update(1, 0, n - 1, arr_index[x], x, INF, -1);
//         }
//     }
//     return 0;
// }

// // Call with node = 1, tl = 0, tr = n - 1
// void build(int node, int tl, int tr) {
//     if (tl == tr) {
//         seg_tree[node].less_than_set.insert(arr[tl]);
//         seg_tree[node].greater_than_set.insert(arr[tl]);
//         return;
//     }
//     int tm = (tl + tr) >> 1, left_node = node << 1, right_node = node << 1 | 1;
//     build(left_node, tl, tm); // left node will be 2*node
//     build(right_node, tm + 1, tr);  // right node will be 2*node+1

//     for (auto i : seg_tree[left_node].less_than_set) seg_tree[node].less_than_set.insert(i);
//     for (auto i : seg_tree[left_node].greater_than_set) seg_tree[node].greater_than_set.insert(i);
//     for (auto i : seg_tree[right_node].less_than_set) seg_tree[node].less_than_set.insert(i);
//     for (auto i : seg_tree[right_node].greater_than_set) seg_tree[node].greater_than_set.insert(i);
//     return;
// }

// // Call with node = 1 as segment seg_tree array starts with 1.
// // Query in interval [l, r] inclusive.
// int query_less_than(int node, int tl, int tr, int l, int r, int k) {
//     if (l > tr || r < tl) return 0;
//     if (l <= tl && r >= tr) return seg_tree[node].less_than_set.order_of_key(k);
//     int tm = (tl + tr) >> 1, left_node = node << 1, right_node = node << 1 | 1;
//     return query_less_than(left_node, tl, tm, l, r, k) + query_less_than(right_node, tm + 1, tr, l, r, k);
// }

// int query_greater_than(int node, int tl, int tr, int l, int r, int k) {
//     if (l > tr || r < tl) return 0;
//     if (l <= tl && r >= tr) return seg_tree[node].greater_than_set.order_of_key(k);
//     int tm = (tl + tr) >> 1, left_node = node << 1, right_node = node << 1 | 1;
//     return query_greater_than(left_node, tl, tm, l, r, k) + query_greater_than(right_node, tm + 1, tr, l, r, k);
// }

// void update(int node, int tl, int tr, int position, lli old_value, lli less_than_value, lli greater_than_value) {
//     if (tl == tr) {
//         seg_tree[node].less_than_set.erase(old_value);
//         seg_tree[node].greater_than_set.erase(old_value);
//         seg_tree[node].less_than_set.insert(less_than_value);
//         seg_tree[node].greater_than_set.insert(greater_than_value);
//         return;
//     }
//     int tm = (tl + tr) >> 1, left_node = node << 1, right_node = node << 1 | 1;
//     if (position <= tm) update(left_node, tl, tm, position, old_value, less_than_value, greater_than_value);
//     else update(right_node, tm + 1, tr, position, old_value, less_than_value, greater_than_value);
//     seg_tree[node].less_than_set.erase(old_value);
//     seg_tree[node].greater_than_set.erase(old_value);
//     seg_tree[node].less_than_set.insert(less_than_value);
//     seg_tree[node].greater_than_set.insert(greater_than_value);
// }

// lli count_inversion() {
//     lli inversion_count = 0;
//     for (int i = 0; i < n; i++) {
//         point_update(arr[i], 1);
//         inversion_count += range_query(arr[i] + 1, n);
//     }
//     return inversion_count;
// }

// lli range_query(int l, int r) {
//     return prefix_query(r) - prefix_query(l - 1);
// }

// lli prefix_query(int x) {
//     lli res = 0;
//     for (int i = x; i > 0; i -= i & (-i)) res += bit[i];
//     return res;
// }

// void point_update(int x, lli delta) {
//     for (int i = x; i <= n; i += i & (-i)) bit[i] += delta;
// }