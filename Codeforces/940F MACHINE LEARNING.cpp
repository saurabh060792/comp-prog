#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

#define MAX 300005
#define MAXTWOTHIRD 2000

struct query {
    int l, r, t, id, l_block, r_block;
    int operator<(query q)const {
        return l_block != q.l_block ? l < q.l : (r_block != q.r_block ? r < q.r : t < q.t);
    }
};

int compress(int x);
void add(int x);
void remove(int x);
void time_travel(int u_id, int q_id);

query Q[MAX];
int n, q, cc_index = 1, arr[MAX], freq[MAX], freq_of_freq[MAX], ans[MAX];
map<int, int> cc;
pair<int, int> U[MAX];

int main() {
    int x, q_type, l, r, t, q_id = 0, u_id = -1, pos;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        arr[i] = compress(x);
    }
    while (q--) {
        scanf("%d", &q_type);
        if (q_type == 1) {
            scanf("%d%d", &l, &r);
            l--, r--;
            Q[q_id] = {l, r, u_id, q_id, l / MAXTWOTHIRD, r / MAXTWOTHIRD};
            q_id++;
        } else {
            scanf("%d%d", &pos, &x);
            pos--;
            U[++u_id] = {pos, compress(x)};
        }
    }
    sort(Q, Q + q_id);
    l = 0, r = -1, t = -1;
    for (int i = 0; i < q_id; i++) {
        while (l > Q[i].l) add(arr[--l]);
        while (r < Q[i].r) add(arr[++r]);
        while (l < Q[i].l) remove(arr[l++]);
        while (r > Q[i].r) remove(arr[r--]);
        while (t < Q[i].t) time_travel(++t, i);
        while (t > Q[i].t) time_travel(t--, i);

        // Finding MEX will take O(sqrt(n)) time because in the worst case
        // 1 will appear 1 time, 2 will appear 2 time, 3 will appear 3 time
        // and so on. But sum (1+2+3...m = m(m+1)/2) cannot be greater than n.
        int j = 1;
        while (freq_of_freq[j]) j++;
        ans[Q[i].id] = j;
    }
    for (int i = 0; i < q_id; i++) printf("%d\n", ans[i]);
}

int compress(int x) {
    if (!cc[x])
        cc[x] = cc_index++;
    return cc[x];
}

void add(int x) {
    freq_of_freq[freq[x]]--;
    freq_of_freq[++freq[x]]++;
}

void remove(int x) {
    freq_of_freq[freq[x]]--;
    freq_of_freq[--freq[x]]++;
}

// u_id = update id first unapplied update
// q_id = query id
void time_travel(int u_id, int q_id) {
    if (Q[q_id].l <= U[u_id].first && U[u_id].first <= Q[q_id].r)
        add(U[u_id].second), remove(arr[U[u_id].first]);
    swap(U[u_id].second, arr[U[u_id].first]);
}
