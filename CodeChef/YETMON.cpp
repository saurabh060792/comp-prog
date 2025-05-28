#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define MAX 200010

using namespace std;

typedef long long int lli;

lli arr[MAX];

int main() {
    lli t, n, op1, op2, l, r;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        for (int i = 0; i < n; i++) scanf("%lld", &arr[i]);
        sort(arr, arr + n);
        op1 = op2 = 0;
        l = 0;
        r = n - 1;
        while (l <= r) {
            if (arr[r] - op2 > (r - l + 1)) {
                op1++;
                r--;
            } else {
                op2++;
                while (arr[l] <= op2 && l <= r) l++;
            }
        }
        printf("%lld\n", op1 + op2);
    }
    return 0;
}
