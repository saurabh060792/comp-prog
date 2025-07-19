#include <iostream>
 
using namespace std;
 
int count(int x);
 
int n;
 
int main() {
    scanf("%d", &n);
    printf("%d\n", count(1));
    return 0;
}
 
int count(int x) {
    if (x > n) return 0;
    return count(x * 10) + count(x * 10 + 1) + 1;
}
