#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <set>

using namespace std;

double** powerMat(double **A, int n, int pow);
double** multMat(double **A, double **B, int p, int q, int r);

string word,s;
set<string> f;

int main()
{
	int t, n, k, i, j;
	double **p, ans, temp;
	p = new double*[30];
	for(i=0;i<30;i++) p[i] = new double[30];
	cin >> t;
	while(t--){
		cin >> n >> k;
		cin >> word;
		for(i=0;i<26;i++) for(j=0;j<26;j++) cin >> p[i][j];
		for(i=0;i<n;i++) {
			cin >> s;
			if(s.length() != word.length()) continue;
			f.insert(s);
		}
		p = powerMat(p, 26, k);
		ans = 0.0;
		for(set<string>::iterator it=f.begin();it!=f.end();it++) {
			temp = 1.0;
			for(j=0;j<word.length();j++){
				temp *= p[word[j]-'a'][(*it)[j]-'a'];
			}
			ans += temp;
		}
		printf("%.10lf\n", ans);
		f.clear();
	}
	return 0;
}

double** multMat(double **A, double **B, int p, int q, int r)
{
	int i, j, k;
	double temp, **mult;
	mult=(double**)malloc(sizeof(double*)*p);
	for(i=0; i<p; i++){
		mult[i]=(double*)malloc(sizeof(double)*r);
		for(j=0; j<r; j++){
			temp=0;
			for(k=0; k<q; k++){
				temp = (temp + (A[i][k]*B[k][j]));
			}
			mult[i][j]=temp;
		}
	}
	return mult;
}

double** powerMat(double **A, int n, int pow)
{
	double **t1, **t2;
	if(pow == 1){
		t2 = A;
	}
	else if(pow %2) {
		t1 = powerMat(A, n, pow-1);
		t2 = multMat(A, t1, n, n, n);
	}
	else {
		t1 = powerMat(A, n, pow/2);
		t2 =  multMat(t1, t1, n, n, n);
	}
	return t2;
}

