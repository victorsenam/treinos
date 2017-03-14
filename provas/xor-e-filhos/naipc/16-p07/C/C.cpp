#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

const int S = 4e6;
const int N = 102;
char P[S];
string T, a, b, c;
int k, ps, n;
int kmp[S];
ll g[N], cte[2];

void build(){
    int k = kmp[0] = -1;
    for(int i=1;i<ps+1;i++){
        while(k >= 0 && P[k+1] != P[i]) k = kmp[k];
        kmp[i] = ++k;
    }
}
ll solve(){
    ll cnt = 0;
    int j = 0;
    for(int i=0;i<T.length();i++){
        while(j >= 0 && T[i] != P[j+1]) j = kmp[j];
        cnt += (++j == ps);
    }
    return cnt;
}

int tc;
int main(){
    while(scanf(" %d", &n) == 1){
        memset(g,0,sizeof g);
        scanf(" %s", P+1);
        ps = strlen(P+1);
        build();

        if(n == 0) g[0] = (P[1] == '0' && ps == 1);
        else if(n < 3){
            a = '0'; b = '1';
            for(k=1;k<n;k++){
                c = b + a;
                a = b; b = c;
            }
            T = b;
            g[n] = solve();
        }
        else{
            a = '0'; b = '1';
            for(k=1;b.length() < ps && k < n;k++){
                c = b + a;
                a = b; b = c;
            }
            T = b;
            g[k] = solve();
            for(int i=0;i<2;i++){
                c = b + a;
                a = b; b = c;
                T = b;
                g[++k] = solve();
            }

            T = b + b;
            cte[k&1] = solve() - ll(2)*g[k];

            T = a + a;
            cte[(k+1)&1] = solve() - ll(2)*g[k-1];

            for(;k<n;k++) g[k+1] = g[k] + g[k-1] + cte[k&1];
        }
        printf("Case %d: %llu\n", ++tc, g[n]);
    }
}

