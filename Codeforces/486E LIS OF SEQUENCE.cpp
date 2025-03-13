#include <cstdio>
#include <functional>
#include <algorithm>

#define MAX 100005

using namespace std;

int a[MAX], f1[MAX], f2[MAX], c[MAX], freq[MAX];
char buf[MAX];

void lis(int *a, int n);

int main() 
{
	int i,n,l;
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	lis(a, n);
	for(i=0;i<n;i++) f1[i] = f2[i], a[i] = -a[i];
	reverse(a, a+n);
	lis(a, n);
	reverse(f2, f2+n);
	l = *max_element(f2, f2+n);
	for(i=0;i<n;i++) {
		if(f1[i] + f2[i] == l + 1) {
			freq[f1[i]]++;
			buf[i] = '2';
		}
		else buf[i] = '1';
	}

	for(i=0;i<n;i++)
		if(f1[i] + f2[i] == l + 1 && freq[f1[i]] == 1)
			buf[i] = '3';
	printf("%s\n", buf);
	return 0;
}

void lis(int *a, int n)
{
	/*
	c[i]: The minimum value of the last element of the
	longest increasing sequence whose length is i.
	Note that c array is always increasing.
	*/
	int i,size=0,it;
	for(i=0;i<n;i++) {
		it = lower_bound(c, c+size, a[i]) - c;
		if(it == size) size++;
		c[it] = a[i];
		f2[i] = it+1;
	}
}