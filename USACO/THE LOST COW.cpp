#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAXLOG 21

using namespace std;

typedef long long int lli;

int main() {
    freopen("lostcow.in", "r", stdin);
    freopen("lostcow.out", "w", stdout);

    int x, y, total = 0, prev_location = 0, location = 0;
    cin>>x>>y;
    y -= x;
    x = 0;

    for (int i = 0; i < MAXLOG; i++) {
        if (i%2 == 0) {
            total += abs(location - (1<<i));
            location = (1<<i);
        } else {
            total += location + (1<<i);
            location = (1<<i) * (-1);
        }

        if ((prev_location < location && location >= y && y > prev_location) ||
            (prev_location > location && location <= y && y < prev_location)) {
            cout<<total - abs(location - y)<<endl;
            break;
        }
        prev_location = location;
    }
    
    return 0;
}
