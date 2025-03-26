#include <iostream>
#include <vector>

#define M1 1000000006
#define M2 1000000007

using namespace std;

typedef long long int lli;

lli gcd(lli a,lli b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    lli t, g;
    cin>>t;
    while(t--) {
        string str;
        cin>>str;
        bool isRational = false;
        lli num=0, den=1;
        for(int i = 0; i < str.length(); i++) {
            if(isRational)
                den *= 10 ;
            if(str[i] == '.') {
                isRational = true;
                continue;
            }
            num = num * 10 + (str[i] - '0');
        }
        g = gcd(num,den);
        cout<<(den/g)<<endl;
    }
    return 0;
}
