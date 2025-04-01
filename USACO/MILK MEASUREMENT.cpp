#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <set>
#include <map>

#define MAX 100
#define INF 1000000000

using namespace std;

typedef long long int lli;

struct log_entry {
    int day, diff;
    string name;
};

struct log_entry_comparator {
    bool operator()(log_entry a, log_entry b) {
        return a.day < b.day;
    }
};

int main() {
    freopen("measurement.in", "r", stdin);
    freopen("measurement.out", "w", stdout);

    int n, ic = 7, num_change = 0, leader_production = 7, max_production;
    set<string> leaders = {"Elsie", "Bessie", "Mildred"};
    map<string, int> production = {{"Elsie", 7}, {"Bessie", 7}, {"Mildred", 7}};
    cin>>n;
    log_entry logs[MAX];
    for (int i = 0; i < n; i++) cin>>logs[i].day>>logs[i].name>>logs[i].diff;
    sort(logs, logs + n, log_entry_comparator());
    for (int i = 0; i < n; i++) {
        production[logs[i].name] += logs[i].diff;
        if (production[logs[i].name] < leader_production) {
            if (leaders.size() > 1 && leaders.find(logs[i].name) != leaders.end()) {
                num_change++;
                leaders.erase(logs[i].name);
            }
            else if (leaders.size() == 1 && leaders.find(logs[i].name) != leaders.end()) {
                max_production = -1;
                set<string> new_leaders;
                for (auto it : production) max_production = max(max_production, it.second);
                for (auto it : production) if (it.second == max_production) new_leaders.insert(it.first);
                leader_production = max_production;
                if (leaders != new_leaders) { 
                    num_change++;
                    leaders = new_leaders;
                }
            }
        }
        else if (production[logs[i].name] == leader_production) {
            if (leaders.find(logs[i].name) == leaders.end()) {
                num_change++;
                leaders.insert(logs[i].name);
            }
        } else {
            if (leaders.size() > 1 || leaders.find(logs[i].name) == leaders.end()) {
                num_change++;
                leaders.clear();
                leaders.insert(logs[i].name);
            }
            leader_production = production[logs[i].name];
        }
    }
    cout<<num_change<<endl;
    return 0;
}
