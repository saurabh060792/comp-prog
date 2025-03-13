#include <cstdio>

int tree[1024][1024], mat[1024][1024], N;

int sum(int x, int y);
void add(int x, int y, int value);

int main()
{
	int T,i, x, y, num, x1, y1, x2, y2, res;
	char cmd[10];
	scanf("%d", &T);

	while(T--) {
		scanf("%d", &N);
		for(i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				tree[i][j] = mat[i][j] = 0;

		while(scanf(" %s", cmd) == 1 && cmd[0] != 'E') {
			if (cmd[1] == 'E') {
				scanf("%d %d %d", &x, &y, &num);
				if(mat[x][y] != num) {
					add(x, y, num-mat[x][y]);
					mat[x][y] = num;
				}
			}
			else {
				scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
				res = sum(x2, y2) - sum(x1-1, y2) - sum(x2, y1-1) + sum(x1-1, y1-1);
				printf("%d\n", res);
			}
		}
	}
}

void add(int x, int y, int value)
{
    int i,j;
	for(i = x; i < N; i |= i + 1)
		for(j = y; j < N; j |= j + 1)
			tree[i][j] += value;
}

int sum(int x, int y)
{
	int res = 0,i,j;
	for(i = x; i >= 0; i = (i & (i + 1)) - 1)
		for(j = y; j >= 0; j = (j & (j + 1)) - 1)
			res += tree[i][j];
	return res;
}