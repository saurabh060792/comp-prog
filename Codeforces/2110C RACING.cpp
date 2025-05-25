#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
#include <climits>

#define MAX 500010

using namespace std;

typedef long long int lli;

int d[MAX], low[MAX], high[MAX];

int main() {
    int t, n, lowest, highest;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", &d[i]);
        for (int i = 0; i < n; i++) scanf("%d%d", &low[i], &high[i]);

        // Lowest: lowest height if we fill all unknown indices with 0.
        // Hightest: highest height if we fill all unknow indices with 1.
        int lowest = highest = 0;
        vector<int> unknown_idx;
        bool possible = true;
        for (int i = 0; i < n; i++) {
            if (d[i] == -1) {
                unknown_idx.push_back(i);
                // We fill unknown index with 1 when calculating highest
                // so highest will increment by 1. Lowest will remain the
                // same.
                highest++;
            }
            else  lowest += d[i], highest += d[i];

            // If lowest we can reach is below the low of obstacle then we need
            // to fill up some of the unknown indices with 1's. That will
            // affect the lowest that we can go. As we are filling d[index]
            // with 1, lowest will be incremented by 1. Highest will remain
            // the same.
            //
            // Note that by filling d[index] with 1, we dont have to worry about
            // some other index j between [index, i] getting higher than high[j]
            // because when processing j, we made sure that highest (which is
            // filling all unknown indics < j with 1's) is less than high[j]
            while (lowest < low[i]) {
                if (unknown_idx.empty()) {
                    possible = false;
                    break;
                }
                d[unknown_idx.back()] = 1;
                lowest++;
                unknown_idx.pop_back();
            }

            // If highest we can reach is above high of obstacle then we need
            // need to fill up some unknown indices with 0's. That will bring
            // down the highest we can go. Lowest will be unaffected.
            while (highest > high[i]) {
                if (unknown_idx.empty()) {
                    possible = false;
                    break;
                }
                d[unknown_idx.back()] = 0;
                highest--;
                unknown_idx.pop_back();
            }
        }

        // If some d[i] are not filled then just fill it with anything (0 or 1). It
        // shouldn't matter.
        if (possible) for (int i = 0; i < n; i++) printf("%d ", d[i] == -1 ? 1 : d[i]);
        else printf("-1");
        printf("\n");
    }
    return 0;
}
