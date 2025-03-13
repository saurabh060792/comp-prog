#include <cstdio>
#include <algorithm>

#define MAX 102

using namespace std;

char number[MAX];

void printMin(int m, int s);
void printMax(int m, int s);

int main()
{
	int m,s,i;
	scanf("%d%d",&m,&s);
	if(s==0 && m==1) {
		printf("0 0\n");
		return 0;
	}
	if(9*m < s || s == 0) {
		printf("-1 -1\n");
		return 0;
	}
	for(i=0;i<=m;i++) number[i] = '0';
	printMin(m,s);
	for(i=0;i<=m;i++) number[i] = '0';
	printMax(m,s);
	return 0;
}

void printMin(int m, int s)
{
	int i = m-1;
	number[0] = '1';
	s--;
	while(s) {
		if(s>=9) {
			number[i--] = '9';
			s -= 9;
		}
		else {
			number[i] = i==0?s+1+'0':s+'0';
			s = 0;
			i--;
		}
	}
	number[m] = '\0';
	printf("%s ",number);
}

void printMax(int m, int s)
{
	int i = 0;
	while(s) {
		if(s>=9) {
			number[i++] = '9';
			s -= 9;
		}
		else {
			number[i++] = s+'0';
			s = 0;
		}
	}
	number[m] = '\0';
	printf("%s\n", number);
}