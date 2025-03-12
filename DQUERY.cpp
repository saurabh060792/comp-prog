#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXQUERY 200000
#define MAXVAL 1000006
#define MAXN 30004

using namespace std;

struct event
{
	int ind,start,end;
	
	event(){};
	event(int ind, int start, int end) : ind(ind), start(start), end(end) {};
	
	bool operator < (event E)const
	{
		return end < E.end;
	}
}e[MAXQUERY];

int sum(int idx);
void update(int idx, int val);

int n,a[MAXN],T[MAXN],last[MAXVAL],q,ans[MAXQUERY];

int main()
{
	int i, x, y, pos = 0, tot = 0;
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	
	scanf("%d",&q);
	for(i=0;i<q;i++) {
		scanf("%d %d",&x,&y);
		e[i] = event(i,x,y);
	}

	sort(e,e+q);
	
	memset(last,-1,sizeof(last));
	memset(T,0,sizeof(T));
	
	//We maintain a BIT which will correctly answer all the distinct numbers between 0..i
	//only if the query is sorted by it end index.
	//If the number on which we are iterating if already seen(can easily be done by a hash)
	//then delete(update(last[a[i]], -1)) the last seen entry and add 1 in the new position
	//(update(i, 1)) and answer all the query which are ending in i since as we move on to
	//the larger index and if any number is previously seen then we can safely delete that
	//becausse the previously seen number position's query are already been answered

	for(i=0;i<n;++i) {
		if(last[a[i]] != -1) update(last[a[i]],-1);
		else tot++;
		
		update(i+1,1);
		last[a[i]] = i+1;
		
		while(pos < q && e[pos].end == i+1) {
			ans[e[pos].ind] = tot - sum(e[pos].start-1);
			pos++;
		}
	}
	
	for(i=0;i<q;i++) printf("%d\n",ans[i]);	
	return 0;
}

void update(int idx, int val)
{
	for(;idx<=n;idx += (idx & -idx)) T[idx] += val;
}

int sum(int idx)
{
	int sum = 0;
	for(;idx>0;idx -= (idx & -idx)) sum += T[idx];
	return sum;
}