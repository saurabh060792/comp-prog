//Here all the function are O(n^2). For O(n) visit: http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html

#include <iostream>
#include <cstring>
#include <string>

#define MAX 1000

using namespace std;

string longestPalindromeDP(string str);
string expandAroundCenter(string s, int c1, int c2);
string longestPalindromeExpand(string s);

int main()
{
	string str;
	cin>>str;
	//cout<<"DP: "<<longestPalindromeDP(str)<<endl;
	cout<<"By Expanding around the center: "<<longestPalindromeExpand(str)<<endl;

	return 0;
}

string longestPalindromeDP(string s)
{
	int n = s.length(), longestBegin = 0, j, maxLen = 1;
	bool table[MAX][MAX] = {false};
	for (int i = 0; i < n; i++) table[i][i] = true;
	for (int i = 0; i < n-1; i++)
		if (s[i] == s[i+1]) {
			table[i][i+1] = true;
			longestBegin = i;
			maxLen = 2;
		}
	for (int len = 3; len <= n; len++)
		for (int i = 0; i < n-len+1; i++) {
			j = i+len-1;
			if (s[i] == s[j] && table[i+1][j-1]) {
				table[i][j] = true;
				longestBegin = i;
				maxLen = len;
			}
		}
	return s.substr(longestBegin, maxLen);
}

// Consider the case “ababa”. If we already knew that “bab” is a palindrome, it is obvious that “ababa” must be a palindrome since the two left and right end letters are the same.
// P[i,j] = true iff the substring S(i,j) is a palindrome, otherwise false
// P[i,j] = ( P[i+1,j-1] and S[i] == S[j])
// The base cases are:
// P[i,i] = true
// P[i,i+1] = (S[i] == S[i+1])
// Time Complexity = O(n^2)
// Space Complexity = O(n^2)



string expandAroundCenter(string s, int c1, int c2)
{
	int l = c1, r = c2;
	int n = s.length();
	while (l >= 0 && r <= n-1 && s[l] == s[r]) {
		//cout<<s.substr(l,r-l+1)<<endl;  							//for printing all the palindrome
		l--;
		r++;
	}
	return s.substr(l+1, r-l-1);
}
 
string longestPalindromeExpand(string s)
{
	int n = s.length();
	if (n == 0) return "";
	string longest = s.substr(0, 1);
	for (int i = 0; i < n-1; i++) {
		string p1 = expandAroundCenter(s, i, i);
		if (p1.length() > longest.length())
			longest = p1;
 
		string p2 = expandAroundCenter(s, i, i+1);
		if (p2.length() > longest.length())
			longest = p2;
	}
	return longest;
}

// We observe that a palindrome mirrors around its center. Therefore, a palindrome can be expanded from its center, and there are only 2n-1 such centers.
// The center of a palindrome can be in between two letters. Such palindromes have even number of letters (such as “abba”) and its center are between the two ‘b’s.
// Since expanding a palindrome around its center could take O(n) time, the overall complexity is O(n^2). Space Complexity = O(1).


