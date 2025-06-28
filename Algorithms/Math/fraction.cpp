#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long int lli;

class fraction
{
	public:
	lli n, d;

	//constructors
	fraction(lli n, lli d):n(n), d(d){}
	fraction():n(1), d(1){}
	fraction(lli n):n(n), d(1){}

	//operators
	fraction operator+(const fraction& b)
	{
		fraction f(n*b.d+b.n*d, d*b.d);
		f.normalize();
		return f;
	}

	fraction operator-(const fraction& b)
	{
		fraction f(n*b.d-b.n*d, d*b.d);
		f.normalize();
		return f;
	}

	fraction operator*(const fraction& b)
	{
		fraction f(n*b.n, d*b.d);
		f.normalize();
		return f;
	}
	
	fraction operator/(const fraction& b)
	{
		fraction f(n*b.d, d*b.n);
		f.normalize();
		return f;
	}
	

	void normalize()
	{
		lli g = this->gcd(n, d);
		n /= g;
		d /=g;
	}
	
	lli gcd(lli a, lli b)
	{
		if(a > b) return gcd(b, a);
		if(a < 0) return gcd(-a, b);	
		if(a == 0) return b;
		else return gcd(b%a, a);
	}

	void printFraction()
	{
		if(d < 0) {
			d*=-1;
			n*=-1;
		}
		printf("%lld/%lld", n, d);
	}
};
