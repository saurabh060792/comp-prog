#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 110

using namespace std;

typedef long long int lli;

string amplyfy(string s, int k);

int main() {
    freopen("cowsignal.in", "r", stdin);
    freopen("cowsignal.out", "w", stdout);

    int m, n, k;
    string s[MAX], result[MAX], amplyfied;
    cin>>m>>n>>k;
    
    for (int i = 0; i < m; i++) cin>>s[i];

    for (int i = 0; i < m; i++) {
        amplyfied = amplyfy(s[i], k);
        for (int j = 0; j < k; j++) {
            result[i * k + j] = amplyfied;
        }    
    }

    for (int i = 0; i < k * m; i++)
        cout<<result[i]<<endl;
    return 0;
}

string amplyfy(string s, int k) {
    string result = "";
    for (char ch: s) for (int i = 0; i < k; i++) result += ch;
    return result;
}
