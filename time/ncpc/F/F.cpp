#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200;
const int T = 2e4;
int pos[N][T];
int visi[N][T];
int dt[N];
int ok;
int f, n, t;

int dp (int i, int t) {
    if (t < 0 || t > ::t) return 0;
    if (i == n) return 1;

    int & me= pos[i][t];
    if (visi[i][t])
        return me;
    visi[i][t] = 1;

    me = 0;

    if (dp(i+1, t-dt[i])) return me = 1;
    if (dp(i+1, t+dt[i])) return me = 1;
    return me;
}

int main(){
    scanf(" %d", &f);
    ok = 1;
    while(f--){
        scanf(" %d%d", &t, &n);
        for(int i=0;i<n;i++){
            int ini, fim;
            scanf(" %d%d", &ini, &fim);
            dt[i] = fim-ini;
        }
        memset(visi, 0, sizeof visi);
        ok = 0;
        for(int ct=0;ct<=t;ct++) ok |= dp(0,ct);
        if(!ok){
            printf("impossible\n");
            return 0;
        }
    }
    printf("possible\n");
}
