#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 412345;

const ll modn = 1000000007;
const ll modn2 = 1000000009;
inline ll mod(ll x) { return x % modn; }
inline ll mod2(ll x) { return x % modn2; }
#define fst first
#define snd second

ll pB[N], pB2[N];
const ll B = 263;
const ll B2 = 257;
pii H[N];
int len[N];
map<int, multiset<pii>> mp;

bool ok(const string &s) {
    pii h(0, 0);
    vector<pii> hs;
    for(int i = 0; i < int(s.size()); i++) {
        h.fst = mod(h.fst * B + s[i]);
        h.snd = mod2(h.snd * B2 + s[i]);
        hs.pb(h);
        for(const auto &e : mp) {
            if(i < e.fst - 1) continue;
            pii hh = h;
            if(i >= e.fst) {
                hh.fst = mod(hh.fst - mod(hs[i - e.fst].fst * pB[e.fst]) + modn);
                hh.snd = mod2(hh.snd - mod2(hs[i - e.fst].snd * pB2[e.fst]) + modn2);
            }
            if(e.snd.find(hh) != e.snd.end())
                return true;
        }
    }
    return false;
}

int main () {
    int op;
    ios::sync_with_stdio(0);
    cin.tie(0);
    int i, n, Q;
    pB[0] = pB2[0] = 1;
    for(i = 1; i < N; i++)
        pB[i] = mod(pB[i - 1] * B),
        pB2[i] = mod2(pB2[i - 1] * B2);
    string s;
    cin >> n >> Q;
    for(i = 0; i < n; i++) {
        cin >> s;
        pii h(0, 0);
        for(char c : s) {
            h.fst = mod(h.fst * B + c);
            h.snd = mod2(h.snd * B2 + c);
        }
        len[i] = s.size(); H[i] = h;
        mp[len[i]].insert(h);
    }
    int LAST = 0;
    for(int q = 0; q < Q; q++) {
        cin >> op;
        if(op == 2) {
            int al;
            cin >> i >> al;
            i = (i + LAST) % n;
            al = ((al + LAST) % 26) + 'a';
            mp[len[i]].erase(mp[len[i]].find(H[i]));
            if(mp[len[i]].empty()) mp.erase(len[i]);
            len[i]++;
            H[i].fst = mod(H[i].fst * B + al);
            H[i].snd = mod2(H[i].snd * B2 + al);
            mp[len[i]].insert(H[i]);
        } else {
            cin >> s;
            for(i = 0; i < int(s.size()); i++)
                s[i] = (((s[i] - 'a') + LAST) % 26) + 'a';
            if(ok(s)) {
                puts("YES");
                LAST = q;
            } else
                puts("NO");
        }
    }
}
