#include <iostream>

#define MAX 1000010

using namespace std;

typedef long long int lli;

int a[MAX], asce[MAX], desc[MAX];

int main() {
    int n, q, l, r, j, i;
    scanf("%d%d", &n, &q);
    for (i = 0; i < n; i++) scanf("%d", &a[i]);

    i = 0;
    while (i < n) {
        j = i;
        while (j < n - 1 && a[j + 1] >= a[j]) j++;
        while (i <= j) asce[i++] = j;
    }

    i = n - 1;
    while (i >= 0) {
        j = i;
        while (j >=  1 && a[j - 1] >= a[j]) j--;
        while (i >= j) desc[i--] = j;
    }


    for (int i = 0; i < q; i++) {
        scanf("%d%d", &l, &r);
        l--, r--;
        if (asce[l] >= desc[r]) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
