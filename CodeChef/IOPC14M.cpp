#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX 1100000

using namespace std;

int visited[MAX], dist[MAX], q[MAX], front, back;

int main()
{
	int t, n, MOD, a, b, c, d, k, u, v, Q, ans;
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d%d%d%d%d%d", &n, &a, &b, &c, &d, &k, &Q);
		
		MOD=d*k;
		if (n%k==Q%k) {
			printf("0\n");
			continue;
		}
		ans = -1;
		memset(visited, 0, sizeof(visited));
		dist[n%MOD] = 0;
		visited[n%MOD] = 1;
		front = back = 0;
		q[back++] = n%MOD;
		while(front<back) {
			u = q[front++];
			v = (u+a)%MOD;
			if(!visited[v]) {
				dist[v] = dist[u]+1;
				visited[v] = 1;
				q[back++] = v;
				if(v%k == Q%k) {
					ans = dist[v];
					break;
				}
			}
			v = (u-b)%MOD;
			if(v<0) v += MOD;
			if(!visited[v]) {
				dist[v] = dist[u]+1;
				visited[v] = 1;
				q[back++] = v;
				if(v%k == Q%k) {
					ans = dist[v];
					break;
				}
			}
			v = (u*c)%MOD;
			if(!visited[v]) {
				dist[v] = dist[u]+1;
				visited[v] = 1;
				q[back++] = v;
				if(v%k == Q%k) {
					ans = dist[v];
					break;
				}
			}
			v = (u%d)%MOD;
			if(!visited[v]) {
				dist[v] = dist[u]+1;
				visited[v] = 1;
				q[back++] = v;
				if(v%k == Q%k) {
					ans = dist[v];
					break;
				}
			}
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
