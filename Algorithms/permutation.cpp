#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

#define MAX 10

using namespace std;

void swap(char*, int, int);
void permuation1(char*, int, int);
void permuation2(char*);

int main()
{
	char str[MAX];
	cin>>str;
	cout<<endl;
	permuation1(str, 0, strlen(str)-1);
	cout<<endl;
	permuation2(str);
	return 0;
}

void swap(char *str, int i, int j)
{
	char temp;
	temp = str[i];
	str[i] = str[j];
	str[j] = temp;
}

void permuation1(char *str, int i, int n)
{
	int j, visited[255] = {};
	if(i==n) {
		cout<<str<<endl;
		return;
	}
	else {
		for(j=i;j<=n;j++)
			if(!visited[str[j]]) {
				swap(str, i, j);
				permuation1(str, i+1, n);
				swap(str, i, j);
				visited[str[j]] = 1;
			}
	}
	return;
}

void permuation2(char *str)
{
	string a = str;
	do {
        cout <<a<<endl;
    } while (next_permutation(a.begin(), a.end()));
}


// The algorithm basically works on this logic:

// All permutations of a string X is the same thing as all permutations of each 
// possible character in X, combined with all permutations of the string X without 
// that letter in it.

// That is to say, all permutations of "abcd" are

// "a" concatenated with all permutations of "bcd"
// "b" concatenated with all permutations of "acd"
// "c" concatenated with all permutations of "bad"
// "d" concatenated with all permutations of "bca"
// This algorithm in particular instead of performing recursion on substrings, 
// performs the recursion in place on the input string, using up no additional 
// memory for allocating substrings. The "backtracking" undoes the changes to 
// the string, leaving it in its original state.