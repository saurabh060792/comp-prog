#include <cstdio>
#include <set>
#include <string>

using namespace std;

int main()
{
	int n, i;
	set <string> S;
	set <string> :: iterator it;
	char a[1000];
	while(scanf("%d", &n)==1) {
		S.clear();
		for(i=0; i<n; i++) {
			scanf("%s",a);
			it = S.find(string(a));
			if(it==S.end()) S.insert(string(a));
			else S.erase(it);
		}
		if(S.empty()) printf("second player\n");
		else printf("first player\n");
	}
	return 0;
}

/*
From one pile, we can reallocate to any other pile. We can even reallocate to multiple piles.
The only loosing state is when we can make pair of all the piles. That is, when we have something
like this: 1 1 1 1 2 2 5 5 10 10 ( I have written the piles in increasing order ). Because in
this case, whatever the first person does, the second person mirrors. As a result, the second
person makes the last move. In every other case, we can break down the piles in two sets. Set A
will contain all the piles that have pairs, and set B will contain the piles that don't have a pile.
For example, 1 1 1 2 2 3 4 5 will become, set A { 1, 1, 2, 2 } and set B {1, 3, 4, 5}. Now notice
that, if the set B is empty, then it is the first case, a loosing state. If it is not empty, we
can in one move, convert all piles in set B into pairs, thus pushing player 2 into loosing state.
Hence we will win. If we have odd number of piles, then we will vanish the last pile and reallocate
it in such a way that we can form pair with first and second, third and fourth, fifth and sixth and
so one. In case of when number of piles is even, we will reduce the last pile equal to the first
pile, and reallocate the remaining elements to form pair between second and third, fourth and
fifth... and so on. For example, in our case, set B{1,3,4,5} will become {1,4,4,1} if we take 3
from pile 4 and reallocate 1 from pile 4 to 2. This is ALWAYS possible.

So, if set B is empty, first player loses. Otherwise he wins
*/