#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 1100
#define INF 1000000000

using namespace std;

typedef long long int lli;

bool isSingleWinner(string *ttt, char ch);
bool isDoubleWinner(string *ttt, char ch1, char ch2);

int main() {
    freopen("tttt.in", "r", stdin);
    freopen("tttt.out", "w", stdout);

    int singleWinner = 0, doubleWinner = 0;
    string ttt[3];
    char ch1, ch2;

    for (int i = 0; i < 3; i++) cin>>ttt[i];

    for (ch1 = 'A'; ch1 <= 'Z'; ch1++) if (isSingleWinner(ttt, ch1)) singleWinner++; 
    // Symmetrical Board is tricky ie winner AB is same as BA.
    // So it is preferable to call isDoubleWinner with AB and BA
    // both at the same time rather than running loop with AB and BA
    // ABA
    // BAB
    // ABA
    for (ch1 = 'A'; ch1 <= 'Z'; ch1++)
        for (ch2 = ch1 + 1; ch2 <= 'Z'; ch2++)
            if (isDoubleWinner(ttt, ch1, ch2) || isDoubleWinner(ttt, ch2, ch1))
                doubleWinner++;

    cout<<singleWinner<<endl<<doubleWinner<<endl;
    return 0;
}

bool isSingleWinner(string *ttt, char ch) {
    for (int i = 0; i < 3; i++) {
        if (ttt[i][0] == ttt[i][1] && ttt[i][1] == ttt[i][2] && ttt[i][2] == ch) return true;
        if (ttt[0][i] == ttt[1][i] && ttt[1][i] == ttt[2][i] && ttt[2][i] == ch) return true;
    }
    if (ttt[0][0] == ttt[1][1] && ttt[1][1] == ttt[2][2] && ttt[2][2] == ch) return true;
    if (ttt[0][2] == ttt[1][1] && ttt[1][1] == ttt[2][0] && ttt[2][0] == ch) return true;
    return false;
}

bool isDoubleWinner(string *ttt, char ch1, char ch2) {
    // 112
    for (int i = 0; i < 3; i++) {
        if (ttt[i][0] == ch1 && ttt[i][1] == ch1 && ttt[i][2] == ch2) return true;
        if (ttt[0][i] == ch1 && ttt[1][i] == ch1 && ttt[2][i] == ch2) return true;
    }
    if (ttt[0][0] == ch1 && ttt[1][1] == ch1 && ttt[2][2] == ch2) return true;
    if (ttt[0][2] == ch1 && ttt[1][1] == ch1 && ttt[2][0] == ch2) return true;

    // 121
    for (int i = 0; i < 3; i++) {
        if (ttt[i][0] == ch1 && ttt[i][1] == ch2 && ttt[i][2] == ch1) return true;
        if (ttt[0][i] == ch1 && ttt[1][i] == ch2 && ttt[2][i] == ch1) return true;
    }
    if (ttt[0][0] == ch1 && ttt[1][1] == ch2 && ttt[2][2] == ch1) return true;
    if (ttt[0][2] == ch1 && ttt[1][1] == ch2 && ttt[2][0] == ch1) return true;

    // 211
    for (int i = 0; i < 3; i++) {
        if (ttt[i][0] == ch2 && ttt[i][1] == ch1 && ttt[i][2] == ch1) return true;
        if (ttt[0][i] == ch2 && ttt[1][i] == ch1 && ttt[2][i] == ch1) return true;
    }
    if (ttt[0][0] == ch2 && ttt[1][1] == ch1 && ttt[2][2] == ch1) return true;
    if (ttt[0][2] == ch2 && ttt[1][1] == ch1 && ttt[2][0] == ch1) return true;
    return false;
}
