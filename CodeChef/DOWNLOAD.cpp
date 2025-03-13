#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>

#define MAX 100005
#define MAXG 5003
#define MAXTREE 300005

using namespace std;

typedef struct event
{
	int type, id, s, f;
}event;

map<int, int> cc;
pair<int, int> interval[MAX];
event E[3*MAX];
int index, bit[MAXTREE], input[5*MAX], ans[MAXG];
vector<int> group[MAXG];

int readBIT(int idx);
void updateBIT(int idx ,int val);
bool comp(event a, event b);

int main()
{
	int n,i,j,q,k,temp;
	scanf("%d",&n);
	index = 0;
	for(i=0;i<n;i++) {
		scanf("%d%d",&interval[i].first, &interval[i].second);
		//start interval event
		E[index].id = i;
		E[index].type = 0;
		E[index].s = interval[i].first;
		E[index++].f = interval[i].second;
		//end interval event
		E[index].id = i;
		E[index].type = 2;
		E[index].s = interval[i].second;
		E[index++].f = interval[i].first;
	}
	scanf("%d",&q);
	for(i=0;i<q;i++) {
		scanf("%d",&k);
		for(j=0;j<k;j++) {
			scanf("%d",&temp);
			group[i].push_back(temp);
		}
		sort(group[i].begin(), group[i].end());
		for(j=0;j<k;j++) {
			//query event
			E[index].id = i;
			E[index].type = 1;
			E[index].s = group[i][j];
			E[index++].f = j>0?group[i][j-1]:0;
		}
	}
	sort(E, E+index, comp);
	
	//cordinate compression
	for(i=0,j=0;i<index;i++) input[j++] = E[i].s;
	input[j++] = 0;
	sort(input, input+j);
	cc[input[0]] = 0;
	for(i=1,k=1;i<j;i++) {
		if(input[i] == input[i-1]) continue;
		cc[input[i]] = k++;
	}
	for(i=0;i<index;i++) {
		E[i].s = cc[E[i].s];
		E[i].f = cc[E[i].f];
	}

	//Offline processing
	for(i=0;i<index;i++)
		if(E[i].type == 0) updateBIT(E[i].s, 1);
		else if(E[i].type == 1) ans[E[i].id] += (readBIT(E[i].s) - readBIT(E[i].f));
		else updateBIT(E[i].f, -1);
	for(i=0;i<q;i++) printf("%d\n",ans[i]);
	return 0;
}

bool comp(event a, event b)
{
	return a.s<b.s?true:(a.s==b.s?a.type<b.type:false);
}

int readBIT(int idx)
{
	int sum = 0;
	while(idx > 0) {
		sum += bit[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

void updateBIT(int idx ,int val)
{
	while(idx < MAXTREE){
		bit[idx] += val;
		idx += (idx & -idx);
	}
}