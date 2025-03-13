#include <stdio.h>

#define MAX 100010
#define MOD 1000000007

int n, m, ans;
int P[MAX];

int find(int x);
void merge(int x, int y);

int main()
{
	int i, x, y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n+1;i++) P[i] = i;
	ans = 1;
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		if(find(x) != find(y+1)) {
			merge(x, y + 1);
			ans = (2*ans)%MOD;
		}
	}
	printf("%d\n", ans);
	return 0;
}

int find(int x)
{
	if(P[x] == x) return x;
	return P[x] = find(P[x]);
}

void merge(int x, int y)
{
	x = find(x);
	y = find(y);
	P[y] = x;
}