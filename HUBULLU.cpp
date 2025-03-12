#include <cstdio>

using namespace std;

int main()
{
	int t, c, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%ld%d", &n, &c);
		if(c==0) printf("Airborne wins.\n");
		else printf("Pagfloyd wins.\n");
	}
	return 0;
}

/*
A game of this kind usually consists of 2 states: winning or losing.
A state is a winning one iff there exists at least one move that leads
to a losing state. Otherwise, it is a losing one.

It is trivial for N = 1.
For N > 1, assume that the first player will lose (the game starts with
a losing state). This means all possible moves will lead to a winning state.
Let's pick 1. Now it is the second player's turn. Let x be the number he
will pick to win this game. Consequently, the state after these 2 picks
is a losing one. Note that by picking x at the first turn, the first player
can also reach this losing state. This contradicts our above assumption.
Hence, the first player always wins the game.
*/