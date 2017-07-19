#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<ll,ll> pii;

const int M = 15;
int mn = INT_MAX;

int a[3][3], g[3][3];
int has[10];

void gen(int i, int j) {
    if(i == 2 && a[0][j - 1] + a[1][j - 1] + a[2][j - 1] != M)
        return;
    if(j == 3) {
        if(a[i][0] + a[i][1] + a[i][2] != M) return;
        i++;
        j = 0;
        if(i == 3) {
            for(i = 0; i < 3; i++)
                if(a[i][0] + a[i][1] + a[i][2] != M)
                    return;
            for(j = 0; j < 3; j++)
                if(a[0][j] + a[1][j] + a[2][j] != M)
                    return;
            if(a[0][0] + a[1][1] + a[2][2] != M)
                return;
            if(a[2][0] + a[1][1] + a[0][2] != M)
                return;
            int cur = 0;
            for(i = 0; i < 3; i++)
                for(j = 0; j < 3; j++)
                    cur += abs(a[i][j] - g[i][j]);
            mn = min(mn, cur);
            return;
        }
    }
    for(int d = 1; d <= 9; d++)
        if(!has[d]) {
            has[d] = 1;
            a[i][j] = d;
            gen(i, j + 1);
            has[d] = 0;
        }
}

int main () {
    int i, j;
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            cin >> g[i][j];
    gen(0, 0);
    printf("%d\n", mn);
}
