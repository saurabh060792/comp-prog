#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

#define MAX 102
#define MOD 31011


using namespace std;

typedef long long int lli;

lli parent[MAX], height[MAX];

vector<vector<lli> > removed(vector<vector<lli> > vector);
lli det(vector<vector<lli> > v, int mod);
void createSet(lli x);
lli find(lli x);
lli merge(lli x, lli y);
lli countMST(int n, int m, vector<pair<lli, pair<lli, lli> > > v, int mod);
lli norm(lli a, lli mod);
lli mulInverse(lli a, lli b);
lli CRT(lli *n, lli *a, lli size);

int main()
{
	int n, m, i, j, cnt;
	lli a, b, w, ans1, ans2, coef[2], mod[2];

	scanf("%d%d",&n,&m);
	vector<pair<lli, pair<lli, lli> > > v;
	for(i=0;i<m;i++) {
		scanf("%lld%lld%lld",&a,&b,&w);
		--a;
		--b;
		v.push_back(make_pair(w, make_pair(a,b)));
	}
	printf("%lld\n",countMST(n, m, v, MOD));
	return 0;
}

lli countMST(int n, int m, vector<pair<lli, pair<lli, lli> > > v, int mod)
{
	int i, cnt,j;
	lli msts;
	for(i=0;i<n;i++) createSet(i);
	sort(v.begin(), v.end());

	msts = 1;

	for(i=0;i<m;) {
		vector<pair<lli, lli> > edges;

		for(j=i;v[i].first == v[j].first;j++) {
			edges.push_back(make_pair(find(v[j].second.first), find(v[j].second.second)));
		}

		for(j=i;v[i].first == v[j].first;j++) {
			merge(v[j].second.first, find(v[j].second.second));
		}

		map<int, vector<pair<lli, lli> > > ng2edgesInIt;
		for(vector<pair<lli, lli> >::iterator x = edges.begin(); x != edges.end(); x++) {
			ng2edgesInIt[find(x->first)].push_back(*x);
		}
		for(map<int, vector<pair<lli, lli> > >::iterator x = ng2edgesInIt.begin(); x != ng2edgesInIt.end(); x++) {
			map<int, int> toIds;
			for(vector<pair<lli, lli> >::iterator y = x->second.begin(); y != x->second.end(); y++) {
				if(!toIds.count(y->first)) {
					cnt = toIds.size();
					toIds[y->first] = cnt;
				}
				if(!toIds.count(y->second)) {
					cnt = toIds.size();
					toIds[y->second] = cnt;
				}

			}

			vector<vector<lli> > matr (toIds.size(), vector<lli>(toIds.size()));
			for(vector<pair<lli, lli> >::iterator y = x->second.begin(); y != x->second.end(); y++) {
				y->first = toIds[y->first];
				y->second = toIds[y->second];
				matr[y->first][y->second]--;
				matr[y->second][y->first]--;
				matr[y->first][y->first]++;
				matr[y->second][y->second]++;
			}
			msts = (msts*det(removed(matr), mod))%mod;
		}
		i = j;
	}
	return msts;
}

vector<vector<lli> > removed(vector<vector<lli> > v)
{
	int i;
	v.pop_back();
	for(i=0;i<v.size();i++) {
		v[i].pop_back();
	}
	return v;
}

void createSet(lli x)
{
	parent[x] = x;
	height[x] = 1;
	return;
}
 
lli find(lli x)
{
	if(parent[x] == x) return x;
	else return (parent[x] = find(parent[x]));
}
 
lli merge(lli x, lli y)
{
	lli xRank, yRank, xRep, yRep;
	xRep = find(x);
	yRep = find(y);
	xRank = height[xRep];
	yRank = height[yRep];
 
 
	if(xRep == yRep) return xRep;
	else if(xRank < yRank) return (parent[xRep] = yRep);
	else if(xRank > yRank) return (parent[yRep] = xRep);
	else {
		parent[yRep] = xRep;
		height[xRep]++;
		return xRep;
	}
}

lli det(vector<vector<lli> > v, int mod)
{
	int i,j,k;
	lli ans = 1, t, M[MAX][MAX],n=v.size();
	for(i=0;i<n;i++)
		for(j=0;j<n;j++) M[i][j] = v[i][j];
	for(i=0;i<n;i++) {
	  for(j=i+1;j<n;j++) {
		  while(M[j][i]) {
			  ans*=-1;
			  t = M[i][i]/M[j][i];
			  for(k=i;k<n;k++) {
				  M[i][k]=(M[i][k]-M[j][k]*t)%mod;
				  M[i][k]^=M[j][k];
				  M[j][k]^=M[i][k];
				  M[i][k]^=M[j][k];
				}
			}
		}
		if(M[i][i]==0)return 0;
		else ans=(ans*M[i][i])%mod;
	}
	return (ans%mod+mod)%mod;
}
