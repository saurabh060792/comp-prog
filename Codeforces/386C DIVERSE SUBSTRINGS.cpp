#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>

#define MAX 300005

using namespace std;

typedef long long int lli;

//A[i][j] stores the count of string ending at i and 
//diversity j
lli A[MAX][26]={0}, p[MAX], h[26];
char str[MAX];

int main()
{
	lli i, j, len, sum, t_sum=0;
	set<lli> s;
	set<lli>::iterator it;
	
	scanf("%s", str+1);
	len = strlen(str+1);
	memset(p, -1, sizeof(p));
	memset(h, -1, sizeof(h));

	for(i=1;i<=len;i++){
		p[i] = h[str[i]-'a'];
		h[str[i]-'a'] = i;
	}

	s.insert(0);
	for(i=1;i<=len;i++){
		// s stores the list of the places where 
		// a character appears for the first time
		// when traversing the string from right (position i)
		// to left.
		it = s.find(p[i]);
		if(it != s.end()) s.erase(it);
		it = s.insert(i).first;
		for(j=0; j<26, it!=s.begin();j++){
			A[i][j] = *it - *(--it);
		}
	}
	printf("%d\n", s.size()-1);
	for(j=0; j<26; j++){
		sum=0;
		for(i=1; i<=len; i++){
			sum+=A[i][j];
		}
		if(sum==0) break;
		printf("%lld\n", sum);
	}
	return 0;
}
