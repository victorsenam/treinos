#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int K = 13;
const int N = (1<<K);
const int corre[3][2] = {
    {0, 2},
    {1, 0},
    {2, 1}
};

int valid[N];
int tmp[2][N];
int qt[3], us[3];
char let[3] = {'R', 'P', 'S'};
int k, n, ts;

bool compare (int i, int j) {
    while (valid[i] == valid[j]) i++, j++;
    if (valid[j] == -1 || let[valid[i]] <= let[valid[j]])
        return 0;
    return 1;
}

void resort (int lo, int hi) {
    if (lo + 1 == hi) return;
    int mid = (lo+hi)/2;
    
    resort(lo, mid);
    resort(mid, hi);
    if (compare(lo, mid))
        for (int i = 0; i + mid < hi; i++)
            swap(valid[lo+i], valid[i+mid]);
}

void upd (int ps) {
    for (int i =0; i < 3; i++)
        us[i] = 0;
    for (int i = 0; tmp[ps][i] != -1; i++)
        us[tmp[ps][i]]++;
    for (int i = 0; i < 3; i++)
        if (us[i] > qt[i])
            return;
    int i;
    for (i = 0; !i || tmp[ps][i-1] != -1; i++) {
        valid[i] = tmp[ps][i];
    }
    assert(i-1 == n);
    resort(0, i-1);
}

int main () {
    scanf("%d", &ts);
    for (int cs = 1; cs <= ts; cs++) {
        scanf("%d", &k);
        n = (1<<k);
        for (int i = 0; i < 3; i++)
            scanf("%d", qt+i);   

        valid[0] = tmp[0][0] = tmp[1][0] = -1;       

        for (int st = 0; valid[0] == -1 && st < 3; st++) {
            tmp[1][0] = st;
            tmp[1][1] = -1;
            for (int q = 0; q < k; q++) {
                int i = 0;
                int j = 0;
                while (tmp[!(q&1)][i] != -1) {
                    tmp[q&1][j] = corre[tmp[!(q&1)][i]][0];
                    tmp[q&1][j+1] = corre[tmp[!(q&1)][i]][1];
                    i++;
                    j+=2;
                }
                tmp[q&1][j] = -1;
            }
            
            upd(!(k&1));
        }
        printf("Case #%d: ", cs);
        if (valid[0] == -1)
            printf("IMPOSSIBLE");
        else {
            for (int i = 0; valid[i] != -1; i++)
                printf("%c", let[valid[i]]);
        }
        printf("\n");
    }
}
