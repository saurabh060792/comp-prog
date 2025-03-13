#include <cstdio>
#include <algorithm>
#include <map>

#define MAX 100005

using namespace std;

typedef long long int lli;

int main()
{
    lli n,k,i,size[2]={},a[MAX];
    map<lli, lli> m;
    scanf("%lld%lld",&n,&k);
    for(i=0;i<n;i++) scanf("%lld",&a[i]);
    sort(a, a+n);
    for(i=0;i<n;i++) {
        //Note that there can be atmost 2 sets
        //because the numbers are distinct we can
        //greedily select the numbers
        if(a[i]%k==0) {
            if(m.count(a[i]/k)) {
                m[a[i]] = m[a[i]/k]==0?1:0;
                size[m[a[i]]]++;
            }
            else {
                m[a[i]] = size[0]>=size[1]?0:1;
                size[m[a[i]]]++;
            }
        }
        else {
            m[a[i]] = size[0]>=size[1]?0:1;
            size[m[a[i]]]++;
        }
    }
    printf("%lld\n",max(size[0], size[1]));
    return 0;
}