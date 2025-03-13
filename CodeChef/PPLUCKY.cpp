#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>

#define MAXARRAY 100005
#define MAXTREE 500005

using namespace std;

typedef long long int lli;

lli queryBIT(int idx);
void updateBIT(int idx ,int val);
int queryST(int node, int low, int high, int a, int b);
void updateST(int node, int low, int high, int position, int newValue);

char s[MAXARRAY];
int n, T[MAXARRAY], S[MAXTREE];
lli bit[MAXARRAY];

int main()
{
	int t,i,u,v;
	lli ans;
	scanf("%d",&t);
	while(t--) {
		stack<int> st;
		scanf("%d",&n);
		for(i=0;i<=n+1;i++) bit[i] = 0;
		for(i=0;i<=2*n+5;i++) S[i] = 0;
		scanf("%s",s);
		ans = 0;
		for(i=0;i<n;i++) {
			if(s[i] == '4') st.push(i);
			else if(s[i] == '7' && !st.empty()) {
				u = st.top();
				st.pop();
				v = i;
				if(v-u==1){
					T[u] = T[v] = 1;
					updateST(0, 0, n-1, u, 1);
					updateST(0, 0, n-1, v, 1);
				}
				else {
					T[u] = T[v] = queryST(0, 0, n-1, u+1, v-1) + 1;
					updateST(0, 0, n-1, u, T[u]);
					updateST(0, 0, n-1, v, T[v]);
				}
			}
			else T[i] = n+1;
		}
		while(!st.empty()) {
			u = st.top();
			st.pop();
			T[u] = n+1;
		}

		for(i=0;i<n;i++) {
			if(T[i] == n+1) updateBIT(T[i], 1);
			else if(s[i] == '4') {
				updateBIT(T[i], 1);
				ans += queryBIT(n+1) - queryBIT(T[i]-1);
			}
			else if(s[i] == '7') updateBIT(T[i], 1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}

lli queryBIT(int idx)
{
	lli sum = 0;
	while(idx > 0) {
		sum += bit[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

void updateBIT(int idx ,int val)
{
	while(idx <= n+1){
		bit[idx] += val;
		idx += (idx & -idx);
	}
}

int queryST(int node, int low, int high, int a, int b)
{
	int mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2,r1,r2;
	if(a>high || b<low) return 0;
	if(a<=low && high<=b) return S[node];

	r1 = queryST(lNode, low, mid, a, b);
	r2 = queryST(rNode, mid + 1, high, a, b);
	return max(r1, r2);
}

void updateST(int node, int low, int high, int position, int newValue)
{
	int mid = (low+high)/2,lNode = 2*node + 1,rNode = 2*node + 2;
	if(low == high) {
		S[node] = newValue;
		return;
	}
	else if(position <= mid) updateST(lNode, low, mid, position, newValue);
	else updateST(rNode, mid+1, high, position, newValue);
	S[node] = max(S[lNode], S[rNode]);
}