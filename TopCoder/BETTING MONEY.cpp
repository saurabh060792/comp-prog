#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class BettingMoney {
public:
	int moneyMade(vector <int>, vector <int>, int);
};

int BettingMoney::moneyMade(vector <int> amounts, vector <int> centsPerDollar, int finalResult) {
	int i,gain,loss;
	gain = 0;
	loss = centsPerDollar[finalResult] * amounts[finalResult];
	for(i=0;i<amounts.size();i++)
		if(finalResult != i) gain += amounts[i];
	return gain*100 - loss;
}


//Powered by [KawigiEdit] 2.0!
