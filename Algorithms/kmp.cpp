#include <cstdio>
#include <string>
#include <iostream>

#define MAX 10000

using namespace std;

int pi[MAX];

void prefixFunction(string P);
int kmp(string T, string P);

int main()
{
	string T,P;
	cin>>T>>P;
	cout<<kmp(T,P)<<endl;
}

void prefixFunction(string P)
{
	int k=-1,i,n;
	n = P.length();
	pi[0] = -1;
	for(i=1;i<n;i++) {
		while(k>-1 && P[k+1]!=P[i]) k = pi[k];
		if(P[k+1]==P[i]) k++;
		pi[i] = k;
	}
}

int kmp(string T, string P)
{
	int k=-1,i,n,m,count=0;
	prefixFunction(P);
	n = T.length();
	m = P.length();
	for(i=0;i<n;i++) {
		while(k>-1 && P[k+1]!=T[i]) k = pi[k];
		if(P[k+1]==T[i]) k++;
		if(k==m-1) count++;
	}
	return count;
}