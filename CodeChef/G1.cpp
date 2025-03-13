#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX 2003
#define INF 1000000000

using namespace std;

int grundy[MAX], mex[MAX], group[MAX], countGrp[MAX];

int main()
{
	int sum,g,n,k,t,i,j,l,nGrp,maximum,maxk,grp,start,flag;
	char s[MAX];
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d%s",&n,&k,s);
		nGrp = 0;
		for(i=0;i<n;i++) {
			if(s[i]=='1') {
				if(!i || s[i-1] == '0') {
					group[++nGrp] = i; 
					countGrp[nGrp] = 1;
				}
				else countGrp[nGrp]++;
			}
		}
		maximum = -INF;
		for(i=1;i<=nGrp;i++) maximum = max(maximum, countGrp[i]);

		//The group of 1's if size n is considered as an independent game
		//in which the player has to make all 0 by removing atmost
		//k consecutive 1's. So when a player takes out x consecutive 1's 
		//starting form ith positon the game is divided into 2 game of size
		//i and n-i-x. 
		grundy[0] = 0;
		for(i=1;i<=maximum;i++) {
			memset(mex, 0, sizeof(mex));
			for (l=1;l<=k && l<=n;l++)
				for(j=(i-l)>>1;j>=0;j--)
					mex[grundy[j]^grundy[i-l-j]] = 1;
			
			for(g=0;mex[g];g++);
			grundy[i] = g;
		}


		sum=0;
		for(i=1;i<=nGrp;i++)
			sum ^= grundy[countGrp[i]];


		if(!sum) printf("Johnny wins\n\n");
		else {
			maxk = 0;
			printf("Mary wins\n");
			for(i=1;i<=nGrp;i++) {
				flag = 0;
				for(l=k;l>0;l--) {
					for (j=0;j<=(countGrp[i]-l)/2;j++) {
						//Here we are splitting ith group in 2 part by taking out l 1's
						//from jth position so now the grundy will be xor of group removing
						//ith group and modified ith group = (sum^grundy[countGrp[i]]) ^ grundy[j] ^ grundy[countGrp[i]-j-l]
						//which will be equal to zero because Johnny is losing
						if((grundy[countGrp[i]]^grundy[j]^grundy[countGrp[i]-j-l]) == sum) {
							if(l>maxk) {
								maxk = l;
								grp = i;
								start = j;
							}
							flag = 1;
							break;
						}
					}
					if(flag) break;
				}	
			}
			for(i=group[grp]+start;i<group[grp]+start+maxk;i++) s[i]='0';
			printf("%s\n\n",s);
		}
	}
	return 0;
}