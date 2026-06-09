#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> findConfirmedSignal(vector<int>& a1, vector<int>& a2, int d);
void printVector(vector<int> a);

int main() {
    vector<int> a1 = {1, 2, 0, 4, 0};
    vector<int> a2 = {0, 0, 1, 0, 4};
    int d = 3;
    vector<int> ans = findConfirmedSignal(a1, a2, d);
    for (const auto& element : ans) {
        cout << element << " ";
    }
    std::cout << "\n";
    return 0;
}

vector<int> findConfirmedSignal(vector<int>& a1, vector<int>& a2, int d) {
    int i;
    int n1 = a1.size();
    int n2 = a2.size();
    if (n1 > n2) {
        swap(a1, a2);
        swap(n1, n2);
    }

    vector<int> ans, h1(1000, -1), h2(1000, -1);

    // Initialize sliding window.
    for (i = 0; i < min(n1, d); i++) {
        if (a1[i] > 0) h1[a1[i]] = i;
        if (a2[i] > 0) h2[a2[i]] = i;
    }

    // Base
    for (i = 0; i < d; i++) {
        if (a2[i] > 0 && h1[a2[i]] >= 0) ans.push_back(a2[i]);
    }

    for (i = d; i < min(n1+d, n2); i++) {
        // Find
        if (a1[i] > 0 && h2[a1[i]] >= 0) ans.push_back(a1[i]);
        if (a2[i] > 0 && h1[a2[i]] >= 0) ans.push_back(a2[i]);

        // Delete
        h1[a1[i-d]] = -1;
        h2[a2[i-d]] = -1;

        // Insert
        if (a1[i] > 0) h1[a1[i]] = i;
        if (a2[i] > 0) h1[a2[i]] = i;
    }
    return ans;
}

void printVector(vector<int> a) {
    for (int i = 0; i < 10; i++) cout<<a[i]<<" ";
    cout<<endl;
}