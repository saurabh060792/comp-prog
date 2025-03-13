#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

#define MAXALPHA 26
#define MAXSTR 100005

using namespace std;

typedef long long int lli;

typedef struct trie
{
	char c;
	bool win,lose;
	struct trie *alphabet[MAXALPHA];
}trie;

int main()
{
	int i,n,k;
	char s[MAXSTR];
	trie *T = initTrie('\0');
	scanf("%d%d",&n,&k);
	for(i=0;i<n;i++) {
		scanf("%s",s);
		addString(T, s);
	}

	return 0;
}

trie* initTrie(char c)
{
	int i;
	trie *T = (trie*)malloc(sizeof(trie));
	T->win = T->lose = false;
	T->c = c;
	for(i=0;i<MAXALPHA;i++) T->alphabet[i] = NULL;
	return T;
}

void addString(trie *T, char *s)
{
	int len = strlen(s),i;
	for(i=0;i<len;i++) {
		if(T->alphabet[s[i]-'a'] == NULL) T->alphabet[s[i]-'a'] = initTrie(s[i]);
		T = T->alphabet[s[i]-'a'];
	}
}

