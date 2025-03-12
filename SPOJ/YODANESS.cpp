#include <cstdio>
#include <map>
#include <string>

#define MAX 30048

using namespace std;

int read(int x);
void update(int x);

int f[MAX];
map<string, int> m;

int main(void){
	int ans, n, t, x, i;
	char word[32];
	scanf("%d", &t); 
	while(t--) {
		m.clear();
		ans = 0;
		scanf("%d",&n);
		for(i=n+1;i>1;i--){
			scanf("%s", word);
			m[word] = i;
			f[i] = 0;
		}
		for(i=1;i<=n;i++) {
			scanf("%s",word);
			update(x = m[word]);
			ans += read(x - 1);
		}
		printf("%d\n",ans);
	}
	return 0;
}

int read(int x)
{
	int sum = 0;
	for(; x; x -= (x & -x)) sum += f[x];
	return sum;
}

void update(int x)
{
	for(; x < MAX; x += (x & -x)) ++f[x];
}