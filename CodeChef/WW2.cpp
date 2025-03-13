#include <cstdio>
#include <algorithm>
#include <cstring>

#define MOD 1000000007
#define MAXM 35

using namespace std;

typedef long long int lli;

lli** powerMat(lli **A, lli n, lli pow);
lli** multMat(lli **A, lli **B, lli p, lli q, lli r);


int main()
{
	int t,i,j;
	lli n,m,**even,**odd,**temp,**ans,count;
	even = (lli**)malloc(MAXM*sizeof(lli*));
	odd = (lli**)malloc(MAXM*sizeof(lli*));
	for(i=0;i<MAXM;i++) {
		even[i] = (lli*)malloc(MAXM*sizeof(lli));
		odd[i] = (lli*)malloc(MAXM*sizeof(lli));
	}
	scanf("%d",&t);
	while(t--) {
		scanf("%lld%lld",&n,&m);

		for(i=0;i<m;i++)
			for(j=0;j<m;j++)
				odd[i][j] = even[i][j] = 0;


		for(i=0;i<m;i++) {
			odd[i][i] = 1;
			if(i-1>=0) even[i][i-1] = odd[i][i-1] = 1;
			if(i+1<m) even[i][i+1] = odd[i][i+1] = 1;
		}

		n -= 1;
		temp = multMat(even, odd, m, m, m);

		ans = powerMat(temp, m, n/2);
		count = 0;
		if(n%2) ans = multMat(ans, even, m, m, m);
		for(i=0;i<m;i++)
			for(j=0;j<m;j++)
			count = (count + ans[i][j])%MOD;
		printf("%lld\n",count);
	}
	return 0;
}


lli** multMat(lli **A, lli **B, lli p, lli q, lli r)
{
	lli i, j, k;
	lli temp, **mult;
	mult=(lli**)malloc(sizeof(lli*)*p);
	for(i=0; i<p; i++){
		mult[i]=(lli*)malloc(sizeof(lli)*r);
		for(j=0; j<r; j++){
			temp=0;
			for(k=0; k<q; k++){
				temp = (temp + (A[i][k]*B[k][j])%MOD)%MOD;
			}
			mult[i][j]=temp;
		}
	}
	return mult;
}

lli** powerMat(lli **A, lli n, lli pow)
{
	lli **t1, **t2;
	if(pow == 0) {
		int i;
		t2 = (lli**)malloc(MAXM*sizeof(lli*));
		for(i=0;i<MAXM;i++) t2[i] = (lli*)malloc(MAXM*sizeof(lli));
		for(i=0;i<n;i++) t2[i][i] = 1;
	}
	else if(pow == 1){
		t2 = A;
	}
	else if(pow %2) {
		t1 = powerMat(A, n, pow-1);
		t2 = multMat(A, t1, n, n, n);
	}
	else {
		t1 = powerMat(A, n, pow/2);
		t2 =  multMat(t1, t1, n, n, n);
	}
	return t2;
}