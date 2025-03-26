#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

#define MAX 102

using namespace std;

typedef long long int lli;

lli parent[MAX], height[MAX];

vector<vector<lli> > removed(vector<vector<lli> > vector);
lli det(vector<vector<lli> > vector);
void createSet(lli x);
lli find(lli x);
lli merge(lli x, lli y);
lli gcd(lli a, lli b);


int main()
{
	int n, m, i, j, cnt;
	lli all, msts, g, a, b, w;

	scanf("%d%d",&n,&m);
	vector<vector<lli> > mat(n, vector<lli>(n, 0));
	vector<pair<lli, pair<lli, lli> > > v;
	for(i=0;i<n;i++) createSet(i);
	for(i=0;i<m;i++) {
		scanf("%lld%lld%lld",&a,&b,&w);
		--a;
		--b;
		--mat[a][b];
		--mat[b][a];
		++mat[a][a];
		++mat[b][b];
		v.push_back(make_pair(w, make_pair(a,b)));
	}

	all = det(removed(mat));

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
			msts *= det(removed(matr));
		}
		i = j;
	}
	g = gcd(msts, all);
	printf("%lld/%lld\n",(msts/g), (all/g));

	return 0;
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

lli gcd(lli a, lli b)
{
	if(a<b) return gcd(b, a);
	else if(b==0) return a;
	else return gcd(b, a%b);
}

lli det(vector<vector<lli> > mat) {
	int col, row, n = mat.size(), j, i;
	lli del, res;
	if(n == 0) return 1;

	for(col=0;col<n;col++) {
		bool found = false;
		for(row=col;row<n;row++) {
			if(mat[row][col]) {
				mat[row].swap(mat[col]);
				found = true;
				break;
			}
		}
		
		if(!found) return 0;
		
		for(row=col + 1;row<n;row++) {
			while(true) {
				del = mat[row][col] / mat[col][col];
				for(j=col;j<n;j++) {
					mat[row][j] -= del * mat[col][j];
				}
				if(mat[row][col] == 0) break;
				else mat[row].swap(mat[col]);
			}
		}
	}

	res = 1;
	for(i=0;i<n;i++) res *= mat[i][i];
	return abs(res);
}