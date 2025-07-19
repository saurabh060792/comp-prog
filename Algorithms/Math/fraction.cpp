#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long int lli;

struct fraction {
    lli n, d;

    fraction(lli a, lli b): n(a), d(b) {}
    fraction(): n(1), d(1) {}
    fraction(lli a): n(a), d(1) {}
    fraction(const fraction& b) = default;

    fraction& operator=(const fraction& b) {
        if (this == &b) return *this;
        n = b.n;
        d = b.d;
        return *this;
    }

    fraction operator+(const fraction& b) {
        fraction f(n * b.d + b.n * d, d * b.d);
        f.normalize();
        return f;
    }

    fraction operator-(const fraction& b) {
        fraction f(n * b.d - b.n * d, d * b.d);
        f.normalize();
        return f;
    }

    fraction operator*(const fraction& b) {
        fraction f(n * b.n, d * b.d);
        f.normalize();
        return f;
    }

    fraction operator/(const fraction& b) {
        fraction f(n * b.d, d * b.n);
        f.normalize();
        return f;
    }

    bool operator<(const fraction& b) const {
        return n * b.d < b.n * d;
    }

    void normalize() {
        lli g = __gcd(n, d);
        n /= g;
        d /= g;
    }

    void printFraction() {
        if (d < 0) {
            d *= -1;
            n *= -1;
        }
        printf("%lld/%lld", n, d);
    }
};
