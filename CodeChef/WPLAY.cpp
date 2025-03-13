#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>

#define MAX 17
#define MAXSET (1<<18)

using namespace std;

typedef long long int lli;

lli grundy[MAXSET], inDictionary[MAXSET];

lli getHash(string s);

int main()
{
	lli d,t,r,c,i,j,s,mask,n;
	char board[MAX], word[MAX];
	string temp;
	set<lli> dictionary;
	scanf("%lld",&d);
	for(i=0;i<d;i++) {
		scanf("%s",word);
		dictionary.insert(getHash(word));
	}
	scanf("%lld%lld%lld",&r,&c,&t);
	n = r*c;
	while(t--) {
		for(i=0;i<n;i+=c) scanf("%s",board+i);
		
		for(s=0;s<(1<<n);s++) {
			temp = "";
			for(i=0;i<n;i++)
				if(s&(1<<i)) temp += board[i];
			inDictionary[s] = dictionary.count(getHash(temp));
		}

		for(s=0;s<(1<<n);s++) {
			grundy[s] = 0;
			for(mask=s;;mask=(mask-1)&s) {
				if(inDictionary[mask] && !grundy[s^mask]) {
					grundy[s] = 1;
					break;
				}
				if(mask==0) break;
			}
		}
		if(grundy[(1<<n)-1]) puts("Alice");
		else puts("Bob");
	}
	return 0;
}

lli getHash(string s)
{
	lli i,h = 0, n = s.length();
	sort(s.begin(), s.end());
	for(i=0;i<n;i++) h = h*29 + s[i];
	return h;
}
