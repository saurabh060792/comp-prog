#include <algorithm>
#include <cstdio>

using namespace std;

const int K = 52, M = 5000000, MAXVAL = 100048, N = 10001;

int read(int *b, int x);
void update(int *b, int x, int v);

int f[K][N], LIM = 0, map[MAXVAL], seq[N], v[N];

int main()
{
	int k, n, t, z, i, L;
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n; ++i) scanf("%d", seq + i), v[i] = seq[i];
	sort(seq, seq + n);

	map[seq[0]] = ++LIM;
	for(int i = 1; i < n; ++i)
		if(seq[i] == seq[i - 1]) map[seq[i]] = LIM;
		else map[seq[i]] = ++LIM;
	++LIM;

	for(i = 0; i < n; ++i){
		z = map[v[i]];
		update(f[1], z, 1);												//Any number can start an increasing sequence
		for(L = 2; L <= k; ++L)
			if(t = read(f[L - 1], z - 1)) update(f[L], z, t);			//Any increasing sequence of size L - 1 with last number smaller than z can be extended to a sequence of size L
	}
	printf("%d\n", read(f[k], LIM - 1));
	return 0;
}

int read(int *b, int x)
{
	int sum = 0;
	for(; x; x -= (x & -x)) if((sum += b[x]) >= M) sum -= M;
	return sum;
}
void update(int *b, int x, int v)
{
	for(; x < LIM; x += (x & -x)) if((b[x] += v) >= M) b[x] -= M;
}