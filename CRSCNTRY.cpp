#include <cstdio>

int read()
{
	char c;
	int n = 0;

	while ((c = getchar_unlocked ()) < 48);
	n += (c - '0');
	
	while ((c = getchar_unlocked ()) >= 48)
	  n = n * 10 + (c - '0');
	
	return n;
}

int max(int a, int b)
{ 
	return a > b ? a : b;
}

int getLCSLength (int agnes[], int a, int tom[], int t)
{
	int LCS[a+1][t+1];
	for (int i = 0; i <= a; i++)
		LCS[i][0] = 0;
	for (int i = 0; i <= t; i++)
		LCS[0][i] = 0;
	for (int i = 1; i <= a; i++) {
		for (int j = 1; j <= t; j++) {
			if (agnes[i-1] == tom[j-1])
				LCS[i][j] = LCS[i-1][j-1] + 1;
			else
				LCS[i][j] = max (LCS[i-1][j], LCS[i][j-1]);
		}
	}
	return LCS[a][t];
}

int main()
{
	int d = read ();
	while (d--) {
		int agnes[2001], m = 0;
		int temp = 1, a = 0;
		while (temp) {
			temp = read ();
			agnes[a++] = temp;
		}
		while(true) {
			int tom[2001], t = 1;
			temp = read ();
			if (temp == 0)
				break;
			tom[0] = temp;
			temp = 1;
			while (temp) {
				temp = read();
				tom[t++] = temp;
			}			
			m = max(m, getLCSLength(agnes, a-1, tom, t-1));
		}
		printf("%d\n",m);
	}
	return 0;
}
