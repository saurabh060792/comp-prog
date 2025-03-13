#include <cstdio>
#include <algorithm>

#define MAX 5003

using namespace std;

pair<int, int> day[MAX];

int main()
{
	int i,ans,n;
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%d%d",&day[i].first,&day[i].second);
	sort(day, day+n);
	ans = day[0].second;
	for(i=1;i<n;i++) {
		if(day[i].second < ans) ans = day[i].first;
		else ans = day[i].second;
	}
	printf("%d\n",ans);
	return 0;
}