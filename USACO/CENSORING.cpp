#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <random>

#define MAX 6000
#define INF 1000000000

using namespace std;

typedef long long int lli;

int main() {
    freopen("censor.in", "r", stdin);
    freopen("censor.censored", "w", stdcensored);

    string s, t;
    cin>>s>>t;
    string censored = "";

    for (int i = 0; i < s.length(); i++) {
        censored += s[i];
        if ((censored.length() >= t.length()) &&
            censored.substr(censored.length() - t.length()) == (t))
            censored.resize(censored.size() - t.size());
    }

    cout<<censored<<endl;
}
