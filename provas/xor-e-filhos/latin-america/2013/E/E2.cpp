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
const ll mod = 1000000007;

char s[N];
int n, zer;
ll memo[105][30][55][2], freq[12];


ll dp (int i, int sum, int par, int f) {
    if(par < 0 || par > n-i) return 0;
    if(i == n-zer) return (!sum) && f;
    ll &me = memo[i][sum][par][f];
    if(me != -1) return me;
    return me = ( ((!f)*dp(i+1,(sum+s[i]-'0')%11,par-1,1))%mod
            + ((par-(!f))*dp(i+1,(sum+s[i]-'0')%11,par-1,f))%mod 
            + ((n-i-par)*dp(i+1,(sum-s[i]+'0')%11,par,f))%mod
            )%mod;
}

ll fat(ll x){
    ll ret = 1;
    while(x) { ret *= x--; ret %= mod; }
    return ret;
}

ll fexp(ll a, ll p) {
    ll t = 1;
    for(;p;p>>=1, a=(a*a)%mod)
        if(p&1) t = (a*t)%mod;
    return t;
}

bool comp (int i, int j){
    return i > j;
}


int main() {
    while(scanf(" %s",s) != EOF) {
        memset(memo,-1,sizeof memo);
        n = strlen(s);
        sort(s,s+n,comp);
        zer = 0;
        for(int i = 0; i < 10; i++) freq[i] = 0;
        for(int i = 0; s[i]; i++) { 
            if(s[i] == '0') zer++; 
            freq[s[i]-'0']++; 
        }
        ll den = 1;
        for(int i = 1; i < 10; i++) { den *= fat(freq[i]); den %= mod; }
        printf("%lld\n",(dp(0,0,(n+1)/2,0)*fexp(den,mod-2))%mod);
    }
}

