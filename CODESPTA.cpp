#include <iostream>

using namespace std;

uint64_t powbits[33] = {0};

void init_powbits();
int noOfBits(uint32_t n);
uint64_t countbitu(uint32_t n);
uint64_t countbits(int64_t n);
uint64_t subbits(int32_t a, int32_t b);


int main()
{
	init_powbits();
	int t;
	cin >> t;
	
	while (t--) {
		int64_t a, b;
		cin >> a >> b;
		cout << subbits(a, b) << endl;
	}

	return 0;
}

void init_powbits()
{
	//counts the number of 1's in the numbers less than equal to 2^i-1
	//Note that 2^i-1 is of the form 11....111
	//It can easily proved by induction
	//powbits[n] = f(n)
	//f(n) = 2f(n-1) + 2^(n-1)
	//     = 2((n-1)<<(n-2)) + 2^(n-1)
	//     = (n-1)<<(n-1) + 2^(n-1)
	//     = n<<(n-1)
	//QED
	for (int i=1; i<33; i++) powbits[i] = (uint64_t)i << (i-1);
}

int noOfBits(uint32_t n)
{
	int ret = 0;
	while (n) {
		ret++;
		n >>= 1;
	}
	return ret;
}

uint64_t countbitu(uint32_t n)
{
	if (n == 0) return 0;
	int h = noOfBits(n) - 1;
	int over = n - (1 << h);
	return powbits[h] + over + countbitu(over) + 1;
}

uint64_t countbits(int64_t n)
{
	int64_t nn = -n;
	if (n >= 0) return countbitu(n);
	return nn * 32 - countbitu(nn - 1);
}

uint64_t subbits(int32_t a, int32_t b)
{
	if (a == 0 || b == 0) return countbits(a) + countbits(b);
	if (a < 0 && b > 0) return countbits(a) + countbits(b);
	if (a < 0 && b < 0) return countbits(a) - countbits(b+1);
	if (a > 0 && b > 0) return countbits(b) - countbits(a-1);
	return 0;
}
