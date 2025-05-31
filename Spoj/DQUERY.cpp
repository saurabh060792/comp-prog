#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

#define MAX 30004
// n/sqrt(q) https://codeforces.com/blog/entry/61203?#comment-451304
#define MAXSQRT 70
#define MAXQ 200005
#define MAXNUM 1000006

struct query {
    int l, r, bucket, id;
};

int hash[MAXNUM], a[MAX], ans[MAXQ], distinct = 0;
query Q[MAXQ];

void add(int idx);
void remove(int idx);
bool cmp(const query &a, const query &b);

int main() {
    int n, q, i, l, r;
    scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    scanf("%d", &q);
    for (i = 0; i < q; i++) {
        scanf("%d%d", &Q[i].l, &Q[i].r);
        Q[i].l--, Q[i].r--;
        Q[i].id = i;
        Q[i].bucket = Q[i].l / MAXSQRT;
    }
    sort(Q, Q + q, cmp);
    l = 0, r = -1;
    for (i = 0; i < q; i++) {
        while (r < Q[i].r) r++, add(r);
        while (l > Q[i].l) l--, add(l);
        while (l < Q[i].l) remove(l), l++;
        while (r > Q[i].r) remove(r), r--;
        ans[Q[i].id] = distinct;
    }
    for (i = 0; i < q; i++) printf("%d\n", ans[i]);
}

void add(int idx) {
    hash[a[idx]]++;
    if (hash[a[idx]] == 1) distinct++;
}

void remove(int idx) {
    hash[a[idx]]--;
    if (hash[a[idx]] == 0) distinct--;
}

// In odd blocks sort the right index in ascending order and
// in even blocks sort it in descending order. This will
// minimize the movement of right pointer, as the normal
// sorting will move the right pointer from the end back to
// the beginning at the start of every block. With the improved
// version this resetting is no more necessary.
bool cmp(const query &p, const query &q) {
    if (p.bucket != q.bucket) return p.bucket < q.bucket;
    return (p.bucket & 1) ? (p.r < q.r) : (p.r > q.r);
}
