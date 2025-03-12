#include <iostream>
#include <cstdio>
#include <algorithm>

#define MAX 300005

using namespace std;

int main()
{
	int n,array[MAX],i,temp;
	scanf("%d",&n);
	for(i=0;i<n;i++) {
		scanf("%d",&temp);
		array[temp] = i;
	}
	for(i=n;i;i--) 
		if(array[i]<array[i-1]) break;
		
	printf("%d\n",i-1);
}
