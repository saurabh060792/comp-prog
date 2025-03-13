#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

#define MAX 1000006

using namespace std;

int main()
{
	int i,n,x,qType,qSize1,qSize2,size;
	priority_queue<int> Q1;
	priority_queue<int, vector<int>, greater<int> > Q2;
	scanf("%d",&n);
	qSize1 = qSize2 = size = 0;
	while(n--) {
		scanf("%d",&qType);
		if(qType == 1) {
			scanf("%d",&x);
			size++;
			if(size >= 3 && qSize2 < size/3) {							//add2
				if(x >= Q1.top()) Q2.push(x);
				else {
					Q2.push(Q1.top());
					Q1.pop();
					Q1.push(x);
				}
				qSize2++;
			}
			else if(size >= 3 && qSize2 == size/3) {					//replace
				if(x > Q2.top()) {
					Q1.push(Q2.top());
					Q2.pop();
					Q2.push(x);
				}
				else Q1.push(x);
			}
			else if(size < 3) {
				Q1.push(x);
				qSize1++;
			}
		}
		else {
			if(size < 3) printf("No reviews yet\n");
			else printf("%d\n",Q2.top());
		}
	}
	return 0;
}