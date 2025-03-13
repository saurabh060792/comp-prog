#include <cstdio>
#include <sstream>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long int lli;

lli dp[20][2][2][2];
string s;
char globaldigit;

lli solve(int i, bool loose, bool started, bool found);

int main() 
{
	char digit;
	int t;
	lli n,num,den,g;
	scanf("%d", &t);
	while(t--) {
		num = 0;
		scanf("%lld",&n);
		den = n*10;
		ostringstream ss;
		ss << n;
		s = ss.str();
		for(digit='0';digit<='9';digit++) {
			memset(dp, -1, sizeof dp);
			globaldigit = digit;
			num += solve(0, 0, 0, 0);
		}
		g = __gcd(num,den);
		num /= g;
		den /= g;
		printf("%lld/%lld\n",num,den);
	}
	return 0;
}

lli solve(int i, bool loose, bool started, bool found) 
{
	bool nstarted, nloose, nfound;
	char digit;
	if(i == s.length()) return found;
	lli &ret = dp[i][loose][started][found];
	if(ret != -1) return ret;
	ret = 0;
	for(digit='0';digit<='9';digit++) {
		if(!loose && digit > s[i]) break;
		nstarted = started || digit != '0';
		nloose = loose || digit < s[i];
		nfound = nstarted && (found || digit == globaldigit);
		ret += solve(i+1, nloose, nstarted, nfound);
	}
	return ret;
}