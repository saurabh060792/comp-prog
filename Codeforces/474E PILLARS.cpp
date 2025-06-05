#include <bits/stdc++.h>

using namespace std;

#define MAX 400005
#define MAXTREE 900005

typedef long long int lli;

struct segment_tree_node {
    lli maximum, index;
};

void build(int n);
segment_tree_node query(int n, int l, int r);
void update(int n, int p, segment_tree_node value);
segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node);

segment_tree_node tree[MAXTREE];
lli arr[MAX], parent[MAX];
vector<lli> cc_numbers;
unordered_map<lli, lli> assigned_values;

int main() {
    lli n, st_n, d, cc_index = 0;
    segment_tree_node resr, resl, res, max_res = {0, -1};
    scanf("%lld%lld", &n, &d);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
        cc_numbers.push_back(arr[i] > d ? arr[i] - d : 0);
        cc_numbers.push_back(arr[i]);
        cc_numbers.push_back(arr[i] + d);
    }

    sort(cc_numbers.begin(), cc_numbers.end());
    for (int i = 0; i < 3 * n; i++)
        if (!assigned_values.count(cc_numbers[i])) assigned_values[cc_numbers[i]] = cc_index++;
    st_n = cc_index;


    for (int i = 0; i < st_n; i++) tree[st_n + i].index = -1;
    build(st_n);

    for (int i = 0; i < n; i++) {
        resl = query(st_n, 0, assigned_values[arr[i] > d ? arr[i] - d : 0]);
        resr = query(st_n, assigned_values[arr[i] + d], st_n - 1);

        if (resl.maximum > resr.maximum) {
            res.maximum = resl.maximum + 1;
            parent[i] = resl.index;
        } else {
            res.maximum = resr.maximum + 1;
            parent[i] = resr.index;
        }
        res.index = i;

        if (res.maximum > max_res.maximum) max_res = res;

        update(st_n, assigned_values[arr[i]], res);
    }

    printf("%lld\n", max_res.maximum);
    vector<lli> path;
    lli j;
    for (j = max_res.index; parent[j] != -1; j = parent[j]) path.push_back(j);
    path.push_back(j);
    reverse(path.begin(), path.end());
    for (auto i : path) printf("%lld ", i + 1);
    printf("\n");
    return 0;
}

void build(int n) {
    for (int i = n - 1; i > 0; i--) tree[i] = combine(tree[i << 1],  tree[i << 1 | 1]);
}

// Set value at position p and recalculate all O(log n) tree nodes.
void update(int n, int p, segment_tree_node value) {
    for (tree[p += n] = value; p > 1; p >>= 1) tree[p >> 1] = combine(tree[p], tree[p ^ 1]);
}

// Query on interval [l, r]
segment_tree_node query(int n, int l, int r) {
    segment_tree_node resl = {0, -1}, resr = {0, -1};
    // r starts at n+1 to make the interval inclusive. If
    // r starts from n then interval will be [l, r).
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) resl = combine(resl, tree[l++]);
        if (r & 1) resr = combine(tree[--r], resr);
    }
    return combine(resl, resr);
}

segment_tree_node combine(segment_tree_node left_node, segment_tree_node right_node) {
    segment_tree_node res;
    if (left_node.maximum > right_node.maximum) res = left_node;
    else res = right_node;
    return res;
}
