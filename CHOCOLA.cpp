#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#define MAX 1000006
#define MOD 1000000007

using namespace std;

long long int t,i,k,j,n,m,x[MAX],y[MAX],mulr,mulc,cost;

int main() {
    cin>>t;
    while(t--) {
        cin>>m>>n;
        for(i=0;i<m-1;i++) cin>>y[i];
        for(i=0;i<n-1;i++) cin>>x[i];
        k=j=cost=0;
        mulr=mulc=1;
        sort(y,y+m-1,greater<int>());
        sort(x,x+n-1,greater<int>());
        for(i=0;i<n+m-2;i++) {
            if(j<m-1 && k<n-1) {
                if(y[j]>x[k]) {
                    cost = (cost + (y[j]*mulc))%MOD;
                    mulr++;
                    j++;
                }
                else {
                    cost = (cost + (x[k]*mulr))%MOD;
                    mulc++;
                    k++;
                }
            }
            else if(j<m-1 && k>=n-1) {
                cost = (cost + (y[j]*mulc))%MOD;
                j++;
            }
            else if(j>=m-1 && k<n-1) {
                cost = (cost + (x[k]*mulr))%MOD;
                k++;
            }
        }
        cout<<cost<<endl;
    }
    return 0;
}
