#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>

#define MAXDIGIT 60
#define MOD 1000000007

using namespace std;

typedef long long int lli;

lli comb[MAXDIGIT][MAXDIGIT];

lli find(char *a);
lli f(lli digit, lli three, lli six, lli nine);
bool specialNumber(char *a);
void combi();
lli powMod(lli a,lli n);

int main()
{
	lli t,i,j,ans;
	char a[MAXDIGIT], b[MAXDIGIT];
	scanf("%lli",&t);
	combi();
	while(t--) {
		scanf("%s%s",&a,&b);
		ans = find(b)-find(a);
		if(ans<0) ans += MOD;
		if(specialNumber(b)) ans++;
		printf("%lli\n",ans);
	}
	return 0;
}

bool specialNumber(char *a)
{
	int three,six,nine,i;
	three = six = nine = 0;
	for(i=0;a[i]!='\0';i++) {
		if(a[i]=='3') three++;
		else if(a[i]=='6') six++;
		else if(a[i]=='9') nine++;
	}
	return (three>0 && three==six && six==nine);
}

// count the number which satisfy certain property
lli find(char *a)
{
	lli d, len, digit, i, j, k, three, six, nine, ans=0;

	len = strlen(a);
	for(k=1;k<18;k++) {
		three = six = nine = k;
		digit = len;
		for(i=0;i<len;i++) {
			d = a[i] - '0';
			for(j=0;j<d;j++) {
				if(j==3) ans = (ans + f(digit-1, three-1, six, nine))%MOD;
				else if(j==6) ans = (ans + f(digit-1, three, six-1, nine))%MOD;
				else if(j==9) ans = (ans + f(digit-1, three, six, nine-1))%MOD;
				else ans = (ans + f(digit-1, three, six, nine))%MOD;
			}
			if(d==3) three--;
			else if(d==6) six--;
			else if(d==9) nine--;
			digit--;
		}
	}
	return ans;
}

void combi()
{
	int i,j;
	for(i=0;i<MAXDIGIT;i++)	for(j=0;j<MAXDIGIT;j++)	comb[i][j]=0;
	for(i=0;i<MAXDIGIT;i++) comb[i][0]=comb[i][i]=1;
	for(i=0;i<MAXDIGIT;i++){
		for(j=1;j<i;j++){
			comb[i][j]=(comb[i-1][j]+comb[i-1][j-1])%MOD;
		}
	}
}

lli powMod(lli a, lli n)
{
	lli ans=1;
	while(n)
		if(n&1){
			ans=(ans*a)%MOD;
			n--;
		}
		else{
			a=(a*a)%MOD;
			n>>=1;
		}
	return ans;
}

lli f(lli digit, lli three, lli six, lli nine)
{
	if(three<0 || six<0 || nine<0 || digit<three+six+nine) return 0;
	return ( ((comb[three+six+nine][three+six]*comb[three+six][three])%MOD) * ((comb[digit][three+six+nine]*powMod(7,digit-three-six-nine))%MOD) )%MOD;
}
