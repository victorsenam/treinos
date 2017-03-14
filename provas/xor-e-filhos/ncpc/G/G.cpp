#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef long long ll;

const int Y = 2e4;
int k[Y<<1], tree[Y<<1], lazy[Y], pend[Y];
void force(int p, int x){
    tree[p] = k[p]*x;
    if(p < Y) lazy[p] = x, pend[p] = 1;
}
void update(int p){
    if(p < 1) return;
    if(p < Y){
        if(pend[p]) tree[p] = k[p]*lazy[p];
        else tree[p] = tree[p<<1] + tree[p<<1|1];
    } update(p>>1);
}
void unlazy(int p){
    if(p < 1) return;
    unlazy(p>>1);
    if(p < Y){
        if(pend[p]) force(p<<1, lazy[p]), force(p<<1|1, lazy[p]);
        pend[p] = 0;
    }
}
void force(int l, int r, int x){
    int il = l+Y, ir = r+Y;
    unlazy(il); unlazy(ir-1);
    for(l+=Y,r+=Y;l<r;l>>=1,r>>=1){
        if(l&1) force(l++, x);
        if(r&1) force(--r, x);
    } update(il); update(ir-1);
}
int query(int l, int r){
    int ans = 0;
    int il=l+Y,ir=r+Y;
    unlazy(il); unlazy(ir-1);
    for(l+=Y,r+=Y;l<r;l>>=1,r>>=1){
        if(l&1) ans += tree[l++];
        if(r&1) ans += tree[--r];
    } return ans;
}

const int P = 2e5;
int x[P], y[P], r[P], seen[P];
int g, m, ss, ans;
vector<int> gob[Y];
set<pair<int,int> > ini, fim;
set<int> curr;
inline ll sqr(ll x) { return x*x; }

int main(){
    int i, j;
    for(int i=Y;i<(Y<<1);i++) k[i] = 1;
    for(int i=Y-1;i;--i) k[i] = k[i<<1]+k[i<<1|1];

    scanf(" %d", &g);
    for(int i=0;i<g;i++) scanf(" %d%d", x+i, y+i);
    scanf(" %d", &m);
    for(int i=g;i<g+m;i++) scanf(" %d%d%d", x+i, y+i, r+i);
    for(int i=g;i<g+m;i++){
        ini.insert(mp(x[i]-r[i],i));
        fim.insert(mp(x[i]+r[i],i));
    }
    for(int i=0;i<g;i++){
        gob[x[i]].push_back(y[i]);
        seen[ss++] = x[i];
    }
    sort(seen, seen+ss);
    ss = unique(seen,seen+ss) - seen;
    for(int i=0;i<ss;i++){
        force(0,Y,0);
        int x = seen[i];
        while(!ini.empty() && ini.begin()->first <= x){
            curr.insert(ini.begin()->second);
            ini.erase(ini.begin());
        }
        while(!fim.empty() && fim.begin()->first < x){
            curr.erase(fim.begin()->second);
            fim.erase(fim.begin());
        }
        for(int c: curr){
            double dy = sqrt(sqr(r[c])-sqr(::x[c]-x));
            force(ceil(y[c]-dy),floor(y[c]+dy)+1,1);
        }
        for(int y: gob[x]) ans += query(y,y+1);
    }
    printf("%d\n", g-ans);
}
