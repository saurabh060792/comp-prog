#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <set>
#include <map>

#define MAX 1000010

using namespace std;

typedef long long int lli;

int main() {
    int maximum = 0, maximum_index, open = 0, close = 0;
    string s;
    // Contains possible maximum and correspoinding index.
    map<int, set<pair<int, int>>> max_indices;
    cin>>s;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') open++;
        else if (s[i] == ')') close++;
        if (open == close) {
            if (2 * close >= maximum) {
                maximum = 2 * close;
                maximum_index = i;
            }
        }
        if (close > open || i == s.size() - 1) {
            open = close = 0;
            if (maximum > 0) 
                max_indices[maximum].insert(make_pair(maximum_index - maximum + 1, maximum_index));
        }
    }

    // Right to left to consider cases like "(((()" which 
    // Left to right will not catch.
    open = close = 0;
    // Reset it such that maximum and maximum_index of Left to Right traversal doesn't affect
    // Right to Left traversal when populating max_indices. 
    maximum_index = -1; 
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == '(') open++;
        else if (s[i] == ')') close++;
        if (open == close) {
            if (2 * close >= maximum) {
                maximum = 2 * close;
                maximum_index = i;
            }
        }
        if (open > close || i == 0) {
            open = close = 0;
            if (maximum > 0 && maximum_index >= 0)
                max_indices[maximum].insert(make_pair(maximum_index, maximum_index + maximum - 1));
        }
    }

    if (maximum == 0) {
        cout<<"0 1"<<endl;
    } else {
        cout<<maximum<<" "<<max_indices[maximum].size()<<endl;
    }
    return 0;
}
