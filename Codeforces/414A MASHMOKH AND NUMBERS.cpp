#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#define MAX 100005

using namespace std;

typedef long long int lli;

int a[MAX];

int main() {
    int i, j, n, k, a1, a2;
    scanf("%d%d", &n, &k);
    if (k == 0 && n == 1) {
        printf("1\n");
        return 0;
    }
    if (k < n / 2 || (k > 0 && n <= 1)) {
        printf("-1\n");
        return 0;
    }

    a1 = k - ((n - 2) / 2);
    a2 = 2 * a1;
    i = 1;
    j = 0;
    while (j < n) {
        if (i == a1 || i == a2) {
            i++;
            continue;
        }
        a[j++] = i++;
    }

    printf("%d %d ", a1, a2);
    for (int i = 0; i < n - 2; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
