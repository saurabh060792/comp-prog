#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>


using namespace std;

typedef long long int lli;

int pointer; //Keeps track of the best line from previous query
vector<lli> M; //Holds the slopes of the lines in the envelope
vector<lli> B; //Holds the y-intercepts of the lines in the envelope

//Returns true if line l2 is bad
bool bad(int l1,int l2,int l3)
{
	/*
	l3 is the new new line to be inserted
	intersection(l1,l2) has x-coordinate (b1-b2)/(m2-m1)
	intersection(l1,l3) has x-coordinate (b1-b3)/(m3-m1)
	set the former greater than the latter, and cross-multiply to
	eliminate division
	*/
	return (B[l3]-B[l1])*(M[l1]-M[l2]) < (B[l2]-B[l1])*(M[l1]-M[l3]);
}

//Adds a new line (with lowest slope) to the structure
void add(lli m, lli b)
{
	M.push_back(m);
	B.push_back(b);
	//If the penultimate is now made irrelevant between the antepenultimate
	//and the ultimate, remove it. Repeat as many times as necessary
	while((M.size()>=3) && bad(M.size()-3, M.size()-2, M.size()-1))
	{
		M.erase(M.end()-2);
		B.erase(B.end()-2);
	}
}

//Returns the minimum y-coordinate of any intersection between a given vertical
//line and the lower envelope
lli query(lli x)
{
	//If we removed what was the best line for the previous query, then the
	//newly inserted line is now the best for that query
	if (pointer >= M.size()) pointer = M.size() - 1;
	//Any better line must be to the right, since query values are
	//non-decreasing
	while(pointer < M.size()-1 && M[pointer+1]*x + B[pointer+1] < M[pointer]*x + B[pointer]) pointer++;
	return M[pointer]*x + B[pointer];
}


int main()
{
	int m,n,i;
	lli cost;
	pair<int,int> a[50000];                    //height = a[].first
	pair<int,int> rect[50000];                //width = a[].second
	scanf("%d",&m);
	for (i=0; i<m; i++)
		scanf("%d %d",&a[i].first,&a[i].second);

	sort(a,a+m);
	for (i=0,n=0; i<m; i++)
	{
		/*
		When we add a higher rectangle, any rectangles that are also
		equally thin or thinner become irrelevant, as they are
		completely contained within the higher one; remove as many
		as necessary
		*/
		while (n>0&&rect[n-1].second<=a[i].second) n--;
		rect[n++]=a[i];
	}

	add(rect[0].second,0);
	pointer=0;
	for(i=0;i<n;i++)
	{
		cost=query(rect[i].first);
		if (i<n)
			add(rect[i+1].second, cost);
	}
	printf("%lld\n",cost);
	return 0;
}