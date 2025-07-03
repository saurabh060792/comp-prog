#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pll;

vector<int> prefix_function(string s);

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=396
int main() {
    int t, n;
    string s, rev_s;
    scanf("%d", &t);
    while (t--) {
        cin >> s;
        rev_s = s;
        reverse(rev_s.begin(), rev_s.end());
        s += "#";
        s += rev_s;
        vector<int> pi = prefix_function(s);
        n = s.length();
        int i = n - 1, max_pi = -1;
        while (s[i] != '#') max_pi = max(max_pi, pi[i--]);
        cout << s.substr(n - max_pi , max_pi) << "\n";
    }
    return 0;
}


// The prefix function pi[i] is the length of the longest
// proper prefix of s[0..i] which is also suffix of s[0..i].
// Eg
// 0 1 2 3 4           10
// a b a b x y z a b a b x y z
// |_____|       |_____|
//                  pi[10] = 4
vector<int> prefix_function(string s) {
    int n = s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];

        // When s[i] doesn't match with s[j], we s[i] = s[j]
        // with j = pi[pi[i - 1]] then pi[pi[pi[i - 1]]]
        //
        // For example
        // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21
        // a b a x y a b a x y  z  a  b  a  x  y  a  b  a  b  b  c
        // |_____________| j       |____________________|  i
        // Lets say we are i = 19 and j = pi[18] = 8
        // (s[i] = s[19] = b) != (s[j] = s[pi[18]] = s[8] = x)
        //
        // So, in 2nd iteration we focus on s[0..pi[i-1]-1] = s[0..7]
        // because the answer to appending s[i] to s[11..18] will be
        // same as s[0..7]. For 2nd iteration,
        // j = pi[j - 1] = pi[7] = 3 and we can just think of string as
        // 0 1 2 3 4 5 6 7  19
        // a b a x y a b a   b
        // |_____________| s[i]
        // (s[i] = s[19] = b) != (s[j] = s[3] = x)
        //
        // So again, we go to 3rd iteration, and here we will focus
        // on s[0..2] as answer to appending s[i] to s[0..7] will be
        // same as s[0..2]. For 3nd iteration,
        // j = pi[j - 1] = pi[2] = 1 and we can just think of string as
        // 0 1 2  19
        // a b a   b
        // |___| s[i]
        // (s[i] = s[19] = b) == (s[j] = s[1] = b)
        // So in this case we will break from the while loop and j will
        // be incremented by 1. Hence pi[19] = 2.
        //
        // Note that in this while loop j is decreasing and it gets
        // incremented just once in the if condition below. And in
        // next iteration j start with the same value as the current
        // iteration. Hence j can only increase at most n times hence
        // this while loop will only run at most O(n) times overall.
        // Hence the complexity of computing the prefix function is
        // O(n). If we initialize j with i instead of pi[i-] at the
        // start of the loop then our complexity will become O(n^2)
        // which happens in the naive implementation of prefix 
        // function automaton.
        // https://cp-algorithms.com/string/prefix-function.html#building-an-automaton-according-to-the-prefix-function
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];

        // We initialize j with pi[i - 1] that is we want to
        // see longest suffix of s[0..i-1] which is also a
        // prefix. Then if s[i] matches with s[pi[i-1]] (aka
        // s[j]), we set pi[i] = j + 1.
        //
        // For our above example, when i = 10 we initialize
        // j = pi[9] = 3. And we see that s[10] = s[3]
        // so we set pi[10] = 4.
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
