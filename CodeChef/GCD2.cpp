#include <iostream>
#include <cstring>

#define MAX 255

using namespace std;

int findRem(char*, int);
int gcd(int a, int b);

int main()
{
	int r,t,a;
	char b[MAX];
	cin>>t;
	while(t--) {
		cin>>a;
		cin>>b;
		if(a == 1) {
			cout<<"1"<<endl;
			continue;
		}
		else if(a == 0) {
			cout<<b<<endl;
			continue;
		}
		r = findRem(b,a);
		cout<<gcd(a,r)<<endl;
	}
	return 0;
}

int findRem(char *b, int a)
{
	int i,rem=0,n=strlen(b);
	for(i=0;i<n;i++) {
		rem = 10*rem + (b[i]-'0');
		rem %= a;
	}
	return rem%a;
}

int gcd(int a, int b)
{
	if(b==0) return a;
	return gcd(b,a%b);
}