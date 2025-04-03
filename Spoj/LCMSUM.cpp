#include <iostream>

#define MAX 1000010

using namespace std;

typedef long long int lli;

void phi_sieve();

lli phi[MAX], res[MAX];

void phi_sieve() {
    for (int i = 0; i <= MAX; i++) phi[i] = i;
    for (int i = 2; i <= MAX; i++) {
        if (phi[i] == i) {
	        for (int j = i; j <= MAX; j += i) {
	            phi[j] /= i;
	            phi[j] *= i - 1;
	        }
    	}
    }
 }
 
int main () {
    phi_sieve();
    // https://forthright48.com/spoj-lcmsum-lcm-sum/
    for (int i = 1; i <= MAX; i++) {
    	// For all multiples of i, i|j so we are adding
    	// i * phi[i] to all of its multiples
	    for (int j = i;j <= MAX; j += i) {
	        res[j] += i * phi[i] ;
	    }
	}
 
    int t;
    lli n, ans;
    scanf("%d", &t);
 
    while (t--) {
        scanf ( "%lld", &n);
        ans = res[n] + 1;
        ans *= n;
        ans /= 2;
        printf("%lld\n", ans);
    }
 
    return 0;
}
