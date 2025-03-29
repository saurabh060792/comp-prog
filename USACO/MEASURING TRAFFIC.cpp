#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <tuple>

#define MAX 1100
#define INF 1000000000

using namespace std;

typedef long long int lli;

pair<int, int> findPriorFlow(vector<tuple<int, int, int>> sensor, int n);
pair<int, int> findPostFlow(vector<tuple<int, int, int>> sensor, int n);
vector<tuple<int, int, int>> compress(vector<tuple<int, int, int>> sensor, int n);

int main() {
    freopen("traffic.in", "r", stdin);
    freopen("traffic.out", "w", stdout);

    int n, m, l, r;
    vector<tuple<int, int, int>> sensor;
    string s;
    cin>>n;
    for (int i = 0; i < n; i++) {
        cin>>s>>l>>r;
        if (s == "on") sensor.push_back(make_tuple(1, l, r));
        if (s == "off") sensor.push_back(make_tuple(2, l, r));
        if (s == "none") sensor.push_back(make_tuple(3, l, r));
    }

    pair<int, int> prior = findPriorFlow(sensor, n);
    pair<int, int> post = findPostFlow(sensor, n);

    cout<<prior.first<<" "<<prior.second<<endl;
    cout<<post.first<<" "<<post.second<<endl;

    return 0;
}

pair<int, int> findPriorFlow(vector<tuple<int, int, int>> sensor, int n) {
    int l, r, low = 0, high = INF;
    for (int i = n-1; i >= 0; i--) {
        l = get<1>(sensor[i]);
        r = get<2>(sensor[i]);
        if (get<0>(sensor[i]) == 1) {
            low -= r;
            if (low < 0) low = 0;
            high -= l;
            if (high < 0) high = 0;
        }
        if (get<0>(sensor[i]) == 2) {
            low += l;
            high += r;
        }
        if (get<0>(sensor[i]) == 3) {
            low = max(low, l);
            high = min(high, r);
        }
    }
    return make_pair(low, high);
}

pair<int, int> findPostFlow(vector<tuple<int, int, int>> sensor, int n) {
    int l, r, low = 0, high = INF;
    for (int i = 0; i < n; i++) {
        l = get<1>(sensor[i]);
        r = get<2>(sensor[i]);
        if (get<0>(sensor[i]) == 1) {
            low += l;
            high += r;
        }
        if (get<0>(sensor[i]) == 2) {
            low -= r;
            if (low < 0) low = 0;
            high -= l;
            if (high < 0) high = 0;
        }
        if (get<0>(sensor[i]) == 3) {
            low = max(low, l);
            high = min(high, r);
        }
    }
    return make_pair(low, high);
}
