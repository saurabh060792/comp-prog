#include <iostream>
#include <cstdlib>
#include <assert.h>
  
#define MAX 10000000
#define ONE 1
#define EIGHTYNINE 89
#define UNEXPLORED 0
  
using namespace std;
 
int calculateSequence(int n);
int calculateNext(int n);
  
int main() {
    int *status, result1 = 0, result89 = 0, i;
    status = (int*) malloc(MAX * sizeof(int));
    for (i = 1; i < MAX; i++) status[i] = UNEXPLORED;
    for (i = 1; i < 100; i++) status[i] = calculateSequence(i);
    for (i = 100; i < MAX; i++) status[i] = status[calculateNext(i)];
    for (i = 1; i < MAX; i++) {
        assert(status[i] != UNEXPLORED);
        if (status[i] == ONE) result1++;
        if (status[i] == EIGHTYNINE) result89++;
    }
    cout<<result1<<endl<<result89<<endl;
    return 0;
}
 
int calculateSequence(int n) {
    int i = n;
    while ( i != ONE && i != EIGHTYNINE) {
        i = calculateNext(i);
    }
    return i;
}
 
int calculateNext(int n) {
    int result = 0, i = n, rem, div;
    while(i !=0) {
        rem = i % 10;
        div = i / 10;
        result += rem * rem;
        i = div;
    }
    return result;
}