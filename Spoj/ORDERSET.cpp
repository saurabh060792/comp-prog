#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>

#define MAX 100010

using namespace __gnu_pbds;
using namespace std;

typedef long long int lli;
typedef tree<lli, null_type, less<lli>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

// https://codeforces.com/blog/entry/11080
int main() {
    int q;
    char q_type;
    lli num;
    ordered_set t;
    cin>>q;
    while(q--) {
        cin>>q_type>>num;
        if (q_type == 'I') {
            t.insert(num);
        } else if (q_type == 'D') {
            t.erase(num);
        } else if (q_type == 'K') {
            if (num > t.size()) cout<<"invalid"<<endl;
            else {
                // Kth smallest element.
                auto it = t.find_by_order(num - 1);
                cout<<*it<<endl;
            }
        // Number of elements strictly smaller than num.
        } else cout<<t.order_of_key(num)<<endl;
    }
    return 0;
}
