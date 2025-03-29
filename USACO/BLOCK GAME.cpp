#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 1100
#define INF 1000000000

using namespace std;

typedef long long int lli;

int alphabets[26];

int main() {
    freopen("blocks.in", "r", stdin);
    freopen("blocks.out", "w", stdout);

    int n, freq1[26], freq2[26];
    string s1[MAX], s2[MAX];
    cin>>n;
    for (int i = 0; i < n; i++) cin>>s1[i]>>s2[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26; j++) freq1[j] = freq2[j] = 0;
        for (char ch : s1[i]) freq1[ch - 'a']++;
        for (char ch : s2[i]) freq2[ch - 'a']++;
        for (int j = 0; j < 26; j++) alphabets[j] += max(freq1[j], freq2[j]);
    }
    for (int i = 0; i < 26; i++) cout<<alphabets[i]<<endl;
    return 0;
}
