#include <bits/stdc++.h>

using namespace std;

#define N 1048578
#define natural unsigned long int

int cross[N], inpu[N], sums[N];
natural st, t, n;
vector<natural> finals, starts;

int main () {
    scanf("%lu", &t);

    while(t--) {
        scanf("%lu", &n);
        starts.clear();
        finals.clear();

        st = 0lu;
        for (natural i = 0; i < n; i++) {
            sums[i] = cross[i] = 0;
            scanf("%d", &inpu[i]);

            for (natural j = st; j <= i; j++) {
                sums[j] += inpu[i];

//                printf("? (%d,%d) -> %d \n", j, i, sums[j]);
                if (sums[j] == 42) {
                    starts.push_back(j);
                    finals.push_back(i);
                    st = j+1;

/*
                    for (int k = starts.size()-2; k >= 0; k--) {
                        if (finals[k] >= j) {
                            olaps[j]++;
                            olaps[starts[k]]++;
                        } else break;
                    }
*/
                } else if (sums[j] > 42) st = j+1;
            }
        }

        st = 0lu;
        for (natural i = starts.size(); i > 0; i--) {
            if (cross[i-1]) continue;
            for (natural j = i; j > 0lu && finals[j-1] >= starts[i-1]; j--) cross[j-1] = 1;
            st++;
        }
        
/*
        for (int i = 0; i < starts.size(); i++) {
            printf("! (%d,%d) laps %d \n", starts[i], finals[i], olaps[starts[i]]);
            if (olaps[starts[i]] < olaps[starts[st]]) st = i;
        }
*/

        printf("%lu\n", st);
    }
}
