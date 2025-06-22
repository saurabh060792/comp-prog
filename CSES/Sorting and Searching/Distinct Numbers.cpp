#include <iostream>
#include <set>

#define MAX 1001

using namespace std;

typedef long long int lli;

set<int> distinct;

int main() {
    int n, x;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        distinct.insert(x);
    }
    printf("%d\n", distinct.size());
    return 0;
}