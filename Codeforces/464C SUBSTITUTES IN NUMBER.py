MOD = 10**9+7

s = raw_input()
n = int(raw_input())
query = [['',s]]+[raw_input().split('->') for i in range(n)]

value = {}
pow10 = {}

for i in range(10):
	value[str(i)] = i
	pow10[str(i)] = 10

for i in range(n,-1,-1):
	newValue = 0
	newPow10 = 1
	for d in query[i][1]:
		newValue = (newValue*pow10[d] + value[d])%MOD
		newPow10 = (newPow10 * pow10[d])%MOD
	value[query[i][0]], pow10[query[i][0]] = (newValue, newPow10)

print value['']

"""
There are two things we need to keep track of for each digit:
the value it will eventually turn into, which we can keep
modulo 10^9+7, and the length of the number. With just these
two values, we can apply rules efficiently. Keep track of these
in two arrays val, len

Our base case is just that each digit goes to itself and has length 1.
(i.e. val[i] = i, len[i] = 1).

Now, let's focus on applying a single rule of the form p -> d_1d_2...d_n
The new length of p is len[d_1]+...+len[d_n]
The new value of p is
val[d_n] + 10^(len[d_n])*val[d_(n-1)] + 10^(len[d_n]+len[d_(n-1)])*val[d_(n-2)] + ... + 10^(len[d_n]+len[d_(n-1)]+...+len[d_2])*val[d_1]

In this program instead of storing length we store 10^length
"""