#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define ff first
#define ss second
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const double l = 1e-9;
const int inf = INT_MAX;
//////////////
const int N = 104;
const ll modn = 1000000007;

char s[N];
int n, is, ps, vp[N], vi[N];
int memo[105][30][55], f[12][2];


int dp (int i, int sum, int par) {
    if(par < 0 || par > n-i) return 0;
    int &me = memo[i][sum][par];
    if(me != -1) return me;
    if(i == n) return me = !sum;
    if(dp(i+1,(sum+s[i]-'0')%11,par-1)) return me = 1;
    if(dp(i+1,(sum-s[i]+'0'+11)%11,par)) return me = 1;
    return me = 0;
}

void build (int i, int sum, int par) {
    if(i == n) return;
    if(memo[i+1][(sum+s[i]-'0')%11][par-1] == 1){
        vp[ps++] = s[i]-'0';
        build(i+1,(sum+s[i]-'0')%11,par-1);
    }
    else {
        vi[is++] = s[i]-'0';
        build(i+1,(sum-s[i]+'0'+11)%11,par);
    }
}

ll fac (ll x) {
    ll ret = 1;
    while(x) {
        ret *= x--;
        ret %= modn;
    }
    return ret;
}

ll fexp (ll a, ll e)
{
    ll t = 1;
    for(;e;e>>=1, a = (a*a)%modn)
        if(e&1) t = (a*t)%modn;
    return t;
}

ll choose (ll a, ll b) {
    ll res = fac(a);
    ll den = (fac(a-b)*fac(b))%modn;
    res = (res*fexp(den, modn-2))%modn;
    return res;
}

int main() {
    while(scanf(" %s",s) != EOF) {
        is = ps = 0;
        memset(memo,-1,sizeof memo);
        n = strlen(s);
        if(dp(0,0,(n+1)/2)) build(0,0,(n+1)/2);
        else {
            puts("0");
            continue;
        }
        for(int i = 0; i < 10; i++) f[i][0] = f[i][1] = 0;
        for(int i = 0; i < ps; i++) f[vp[i]][0]++;
        for(int i = 0; i < is; i++) f[vi[i]][1]++;
        
        /*
        printf("par: ");
        for(int i = 0; i < ps; i++) printf("%d ",vp[i]);
        putchar('\n');
        printf("impar: ");
        for(int i = 0; i < is; i++) printf("%d ",vi[i]);
        putchar('\n');
        */

        ll a, b, imp, par;
        a = (fac(is)*fac(ps))%modn; b = 1;
        for(int i = 0; i < 10; i++) { b *= fac(f[i][1]+f[i][0]); b %= modn; }
        ll res = (a * fexp(b,modn-2))%modn;
        
    
        if(f[0][0]) {
            f[0][0]--;
            a = (fac(is)*fac(ps-1))%modn; b = 1;
            for (int i = 0; i < 10; i++) { b *= fac(f[i][1]+f[i][0]); b %= modn; }
            a = (a*(f[0][0]+f[0][1]+1))%modn;
            res = (modn+res-(a*fexp(b,modn-2))%modn)%modn;

            /*
            f[0][0]--;
            a = fac(ps-1);
            b = 1;
            for(int i = 0; i < 10; i++) { b *= fac(f[i][0]); b %= modn; }
            par -= a * fexp(b,modn-2);
            */
        }


        printf("%lld\n",res);
    }
}

