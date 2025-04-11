#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>

#define MAX 200010

using namespace __gnu_pbds;
using namespace std;

typedef long long int lli;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
    int n, k;
    ordered_set t;
    cin>>n;

    for (int i = 0; i < n; i++) {
        scanf("%d", &k);
        t.insert({i, k});
    }

    while(n--) {
        cin>>k;
        auto it = t.find_by_order(k - 1);
        cout<<(*it).second<<" ";
        t.erase({(*it).first, (*it).second});
    }
    cout<<endl;
    return 0;
}
