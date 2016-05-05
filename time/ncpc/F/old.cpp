#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 200;
int ini[N], fim[N];
int ok, bad, foi;
int f,n,t;

int main(){
    ok = 1;
    scanf(" %d", &f);
    while(f--){
        scanf(" %d%d", &t, &n);
        for(int i=0;i<n;i++) scanf(" %d%d", ini+i, fim+i);

        foi = 0;
        for(int _i=0;_i<=t;_i++){
            int c = _i;
            bad = 0;
            for(int i=0;!bad && i<n;i++){
                int dt = fim[i]-ini[i];
                if(dt > max(c,t-c)) bad = 1;
                else c = max(c-dt, t-c-dt);
            }
            foi |= (!bad);
        }
        ok &= foi;
    }
    if(!ok) printf("impossible\n");
    else    printf("possible\n");
}
