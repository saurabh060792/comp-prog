#include <iostream>
#include <cstdio>
#include <map>
#include <algorithm>

#define MAX 100000

using namespace std;

int a[MAX], b[MAX];
bool vis[MAX];

int main()
{
	int res,n,i,t = 0,min_val,num,sum,j;
	while(scanf("%d", &n) && n) {
		t++;
		for (i=0;i<n;i++) {
			scanf("%d", &a[i]);
			b[i] = a[i];
			vis[i] = false;
		}
		sort(b, b + n);

		// Map the numbers to their desired place after sort
		map<int, int> place;
		
		for(i=0;i<n;i++) place[b[i]] = i;
	
		res = 0;
		for(i=0;i<n;i++) {
			if (vis[i] == false) {
				if (place[a[i]] == i) {
					vis[i] = true;
					continue;
				}
				// We're in new cycle
				min_val = a[i];
				num = 0;
				sum = 0;
				j = i;

				while(vis[j] == false) {
					sum += a[j];
					num++;
					if(a[j] < min_val) {
						min_val = a[j];
					}
					vis[j] = true;
					j = place[a[j]];
				}
				sum -= min_val;
				res += sum + min_val * (num - 1);
				
				// Let's try to borrow the minimum value.
				// If it's less costly then update our result.
				if (2 * (b[0] + min_val) < (min_val - b[0]) * (num - 1)) {
					res -= (min_val - b[0]) * (num - 1) - 2 * (b[0] + min_val);
				}    
			}
		}
		printf("Case %d: %d\n\n", t, res);
	}
	return 0;
}

//http://isolvedaproblem.blogspot.in/2012/02/silly-sort.html