#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>

#define MAX 100005

using namespace std;

void createSet(int *parent, int *rank, int x);
int find(int *parent, int *rank, int x);
int merge(int *parent, int *rank, int x, int y);

int main()
{
	int i, *parent, *rank;

	parent = (int*)malloc(MAX*sizeof(int));
	rank = (int*)malloc(MAX*sizeof(int));

	for(i=1;i<10;i++) createSet(parent, rank, i);
	merge(parent, rank, 1, 2);
	merge(parent, rank, 3, 2);
	merge(parent, rank, 4, 8);
	merge(parent, rank, 4, 7);
	merge(parent, rank, 7, 5);
	merge(parent, rank, 8, 5);
	merge(parent, rank, 5, 6);

	for(i=1;i<10;i++) cout<<parent[i]<<" ";
	cout<<endl;


	return 0;
}

void createSet(int *parent, int *rank, int x)
{
	parent[x] = x;
	rank[x] = 1;
	return;
}

int find(int *parent, int *rank, int x)
{
	if(parent[x] == x) return x;
	else return (parent[x] = find(parent, rank, parent[x]));
}

int merge(int *parent, int *rank, int x, int y)
{
	int xRank, yRank, xRep, yRep;
	xRep = find(parent, rank, x);
	yRep = find(parent, rank, y);
	xRank = rank[xRep];
	yRank = rank[yRep];


	if(xRep == yRep) return xRep;
	else if(xRank < yRank) return (parent[xRep] = yRep);
	else if(xRank > yRank) return (parent[yRep] = xRep);
	else {
		parent[yRep] = xRep;
		rank[xRep]++;
		return xRep;
	}
}