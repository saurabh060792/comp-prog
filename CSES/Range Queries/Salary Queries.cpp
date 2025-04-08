#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>

#define MAX 200010
#define INF 1000000010

using namespace __gnu_pbds;
using namespace std;

typedef long long int lli;
typedef tree<
    pair<int, int>,
    null_type,
    less<pair<int, int>>,
    rb_tree_tag, tree_order_statistics_node_update> ordered_set;

// https://codeforces.com/blog/entry/11080
int main() {
    int n, q, a, b, res, arr[MAX];
    char q_type;
    ordered_set t;
    cin>>n>>q;

    for (int i = 0; i < n; i++) {
        cin>>arr[i];
        t.insert({arr[i], i});
    }

    // Printing tree
    // for (auto it: t) {
    // 	cout<<it.first<<" "<<it.second<<endl;
    // }

    while(q--) {
        cin>>q_type>>a>>b;
        if (q_type == '?') {
            // Count number of elements between [a, b] inclusive.
            res = t.order_of_key({b+1, -INF}) - t.order_of_key({a, -INF});
            cout<<res<<endl;
        } else {
        	  a--;
            t.erase({arr[a], a});
            t.insert({b, a});
            arr[a] = b;
        }
    }
    return 0;
}
