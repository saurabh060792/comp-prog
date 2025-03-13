#include <cstdio>
#include <algorithm>
#include <map>
#include <cstring>

#define MAX 100005

using namespace std;

typedef long long int lli;

char s[MAX];
lli V[256];
map<pair<int, lli>, int> M;

int main()
{
	int i,n;
	lli prefixSum=0, ans=0;
	for(i=0;i<26;i++)scanf("%lld",&V['a'+i]);
	scanf("%s",s);
	n = strlen(s);
	for(i=0;i<n;i++) {
		ans += M[make_pair(s[i], prefixSum)];
		prefixSum += V[(int)s[i]];
		M[make_pair(s[i], prefixSum)]++;
	}
	/*
	The order of line 24,25 and 26 is very important. We are adding M[(s[i], ps)]
	to the ans but note that ps in line 24 doesnot contain s[i] that is value of
	s[i] has not been add to ps yet. And if M[(s[i], ps)] contains some value then
	it will	all correspond to the prefix string in which s[j]'s (j's are all those
	lower indics which will pair up with i) value is added(as noted in line 26) so
	the lower index of the substring has been considered but the upper index is
	not hence we get the sum of the value of letter which are in between when we
	subtract them as the lower index will be cancelled out.
	*/
	printf("%lld\n",ans);
}

