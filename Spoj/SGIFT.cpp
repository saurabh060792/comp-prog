#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define MAX 100010

using namespace std;

typedef long long int lli;

lli range_query(int l, int r);
lli prefix_query(int x);
void point_update(int x, lli delta);

lli bit[MAX], arr[MAX];
pair<lli, lli> queries[MAX];
vector<lli> all_numbers;
map<lli, int> cc;

int main() {
    int n, q, a, b, index;
    lli temp;
    cin>>n;
    for (int i = 0; i < n; i++) {
        cin>>arr[i];
        all_numbers.push_back(arr[i]);
    }
    cin>>q;
    for (int i = 0; i < q; i++) {
        cin>>a>>b;
        queries[i] = {a, b};
        all_numbers.push_back(a);
        all_numbers.push_back(b);
    }

    // Coordinate Compression.
    sort(all_numbers.begin(), all_numbers.end());
    // 1 Based Indexing since our BIT is 1 Based.
    cc[all_numbers[0]] = 1;
    index = 2;
    for(int i = 1; i < all_numbers.size(); i++)
        if(all_numbers[i] != all_numbers[i-1]) cc[all_numbers[i]] = index++;
    
    for(int i = 0; i < n; i++) point_update(cc[arr[i]], arr[i]);
    for (int i = 0; i < q; i++) {
        a = queries[i].first;
        b = queries[i].second;
        cout<<range_query(cc[a], cc[b])<<endl;
    }
    return 0;
}

lli range_query(int l, int r) {
    return prefix_query(r) - prefix_query(l - 1);
}

lli prefix_query(int x) {
    lli res = 0;
    for (int i = x; i > 0; i -= i&(-i)) res += bit[i];
    return res;
}

void point_update(int x, lli delta) {
    for (int i = x; i <= MAX; i += i&(-i)) bit[i] += delta;
}
