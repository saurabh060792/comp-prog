#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 110

using namespace std;

typedef long long int lli;

void pour(int i, int j);

int c[3], m[3];

int main() {
    freopen("mixmilk.in", "r", stdin);
    freopen("mixmilk.out", "w", stdout);

    cin>>c[0]>>m[0]>>c[1]>>m[1]>>c[2]>>m[2];
    
    for (int i = 0; i < 100; i++) {
        if(i%3 == 0) pour(0, 1);
        if(i%3 == 1) pour(1, 2);
        if(i%3 == 2) pour(2, 0);
    }

    cout<<m[0]<<endl<<m[1]<<endl<<m[2]<<endl;
    return 0;
}

void pour(int i, int j) {
    if (c[j] - m[j] > m[i]) {
        m[j] += m[i];
        m[i] = 0;
    } else {
        m[i] -= c[j] - m[j];
        m[j] = c[j];
    }
}
