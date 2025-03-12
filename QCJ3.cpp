#include <cstdio>

using namespace std;

typedef long long int lli;

int main()
{
	int t,s,x,i;
	lli ans;
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&s);         
		ans=0;
		for(i=1;i<=s;i++) {
			scanf("%d",&x);
			if(x&1)ans=ans^i;
		}
		printf("%s\n",ans==0?"Hanks Wins":"Tom Wins");
	}
	return 0;
}

//Let Modified Nims game is the following
//You have n heaps and player can choose any heap and take out
//any number of coin from the chosen heap

//So in this question each index is like one Modified Nims game
//and if a[i] is even then the grundy number of that game will
//zero so we only have to consider those games where a[i] is odd.