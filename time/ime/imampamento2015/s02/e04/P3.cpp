#include <bits/stdc++.h>

using namespace std;

const int N = 1007;

vector<int> sec[N];
int n, k, a, ul, ur, al, ar;
int ans;

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &k);
        for (int j =0 ; j< k; j++) {
            scanf("%d", &a);
            sec[i].push_back(a);
        }
        sort(sec[i].begin(), sec[i].end());
    }

    ans = 0;

    for (int i = 0; i < n; i++) {
        ul = lower_bound(sec[(i+n-1)%n].begin(), sec[(i+n-1)%n].end(), sec[i][0]) - sec[(i+n-1)%n].begin();
        ur = lower_bound(sec[(i+1)%n].begin(), sec[(i+1)%n].end(), sec[i][0]) - sec[(i+1)%n].begin();
        for (int j = 1; j < sec[i].size(); j++) {
            al = lower_bound(sec[(i+n-1)%n].begin(), sec[(i+n-1)%n].end(), sec[i][j]) - sec[(i+n-1)%n].begin();
            ar = lower_bound(sec[(i+1)%n].begin(), sec[(i+1)%n].end(), sec[i][j]) - sec[(i+1)%n].begin();
            if (max(al-ul-ar+ur, ar-ur-al+ul) > 0) ans++;
           // printf("%d %d [%d,%d] e [%d,%d] -> %d\n", i, j, al, ul, ar, ur, max(al-ul-ar+ur, ar-ur-al+ul));
            ul = al;
            ur = ar;
        }
    }

    printf("%d\n", ans);
}
