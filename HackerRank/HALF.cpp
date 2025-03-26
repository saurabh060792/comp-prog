#include <cstdio>
#include <algorithm>

using namespace std;

int t[32][32] = {0};

// t[i][j]^1^i^j = 0
void init()
{
	int i, j;
	for (i = 0; i <= 31; i++)
		for (j = 0; j <= 31; j++)
			t[i][j] = 1^i^j;
}

// minimum tiles need to be removed
// to change from grundy class a to b
int difference(int a, int b)
{
	return (1<<(max(a,b)-1)) - (1<< (min(a,b))) + 1;
}

int main()
{
	int test, temp, count, a, b, minimum, n, min_a, min_b;
	scanf("%d", &test);
	init();
	while(test--){
		scanf("%d", &n);
		temp = 1;
		count = 0;
		while(temp <= n){
			temp *= 2;
			count +=1;
		}
		if (n % 2 == 1) {
			printf("1\n");
			continue;
		}
		minimum = 100000000;
		// loop for the grundy class a
		// which is converted to class b
		// such that 1^count^a^b = 0
		for (a=1; a<=count; a++){
			b = t[count][a];
			temp = difference(b,a);
			// since atleat x/2 tiles need to be 
			// remove from pile with x tile
			temp = max(temp, 1<<(max(a,b)-2));
			if (temp <= minimum){
				minimum = temp;
			}
		}
		printf("%d\n", minimum);
	}
	return 0;
}
