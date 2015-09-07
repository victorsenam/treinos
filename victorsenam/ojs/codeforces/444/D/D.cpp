#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 50007;
const int S = 6;
const num MOD = 100000007llu;
const num B = 37llu;

pair<num, int> hash[S][N];
pair<num, int> auxa, auxb;
num h[2];
char str[N];
char cmp[2][S];
int s[2];
int n, q;

int main () {
    scanf(" %s", str);
    n = strlen(str);

    for (int i = 0; i < n; i++) {
        hash[0][i].first = 0llu;
        for (int j = 1; j <= 4 && i+j <= n; j++) {
            hash[j][i].first = ((hash[j-1][i].first*B)%MOD + (str[i+j-1]-'a'))%MOD;
            hash[j][i].second = i;
        }
    }

    for (int j = 1; j <= 4; j++)
        sort(hash[j], hash[j]+max(0, n-j+1));
    
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        scanf(" %s %s", cmp[0], cmp[1]);
        s[0] = strlen(cmp[0]);
        s[1] = strlen(cmp[1]);
        h[0] = 0;
        for (int i = 0; i < s[0]; i++)
            h[0] = ((h[0]*B)%MOD + (cmp[0][i]-'a'))%MOD;
        
        h[1] = 0;
        for (int i = 0; i < s[1]; i++)
            h[1] = ((h[1]*B)%MOD + (cmp[1][i]-'a'))%MOD;

        
        int mini = INT_MAX;
        for (int k = 0; k < 2; k++) {
            auxa.first = h[k];
            auxa.second = 0;
            auxb.first = h[!k];

            int a = lower_bound(hash[s[k]], hash[s[k]] + n - s[k] + 1, auxa) - hash[s[k]];
            for (;a <= n - s[k] && hash[s[k]][a].first == auxa.first; a++) {
                int pa = hash[s[k]][a].second;
                auxb.second = pa;
                int b = lower_bound(hash[s[!k]], hash[s[!k]] + n - s[!k] + 1, auxb) - hash[s[!k]];
                if (b > n - s[!k] || hash[s[!k]][b].first != auxb.first)
                    continue;
                int pb = hash[s[!k]][b].second;
                //printf("%s[%d] and %s[%d] ", cmp[k], hash[s[k]][a].second, cmp[!k], hash[s[!k]][b].second);
                //printf("-> (%d-%d) = ", max(pa+s[k], pb+s[!k]), min(pa, pb));
                //printf("%d\n", max(pa+s[k], pb+s[!k]) - min(pa, pb));
                mini = min(mini, max(pa+s[k], pb+s[!k]) - min(pa, pb));
            }
        }

        if (mini == INT_MAX)
            printf("-1\n");
        else
            printf("%d\n", mini);
    }
}
