#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>

#define MAXK 52
#define MOD 5000000
#define MAXN 10001

using namespace std;

int f[MAXK][MAXN], r[MAXK][MAXN], LIM = 0, seq[MAXN], v[MAXN];
map<int, int> m;

int read(int *b, int x);
void update(int *b, int x, int v);

int main()
{
	int k, n, t, z, i, L, temp;
	scanf("%d %d", &n, &k);
	for(i=0;i<n;i++) scanf("%d",seq + i), v[i] = seq[i];
	std::sort(seq, seq + n);
	for(i=0;i<n;i++) if(!m.count(seq[i])) m[seq[i]] = ++LIM;

	for(i=0;i<n;i++) {
		z = m[v[i]];
		for(L=1;L<=k;L++) {
			t = read(f[L - 1], z - 1);
			if(t != r[L-1][z-1]) {							//r[][] stores the previous answer which ends with z-1
				temp = t;									// so we have to subtract the previous value as it is counted twice
				if((t -= r[L-1][z-1]) < 0) t += MOD;		// if the a[i] is not seen before r[][] will be zero and subtracted is trivial
				r[L-1][z-1] = temp;
				update(f[L], z, t);
			}
		}
	}
	printf("%d\n",read(f[k], MAXN));
	return 0;
}

void update(int *b, int x, int v)
{
	for(; x < MAXN; x += (x & -x)) if((b[x] += v) >= MOD) b[x] -= MOD;
}

int read(int *b, int x)
{
	if(b == f[0]) return 1;
	int sum = 0;
	for(; x; x -= (x & -x)) if((sum += b[x]) >= MOD) sum -= MOD;
	return sum;
}
