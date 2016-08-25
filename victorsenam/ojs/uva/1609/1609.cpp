#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1024+7;

struct spb {
    int w;
    int p;
    int a, b;

    bool operator < (const spb & ot) const {
        if (p != ot.p)
            return p > ot.p;

        if (w != ot.w)
            return w > ot.w;

        if (b - a != ot.b - ot.a)
            return b - a < ot.b - ot.a;

        if (a != ot.a)
            return a < ot.a;
    }
};

bitset<N> adj[N];
bitset<N> usd;
char str[N];
set<spb> st;
spb aux;
int n;
int r[N];

void inverse (char * s, char * t) {
    int n = t - s;

    for (int i = 0; i < n/2; i++)
        swap(s[i], s[n-i-1]);
}

void solve (spb s) {
    DEBUG("[%d,%d) : %d\n", s.a, s.b, s.w+1);
    if (s.b == s.a + 1) {
        r[s.a] = s.w;
        return;
    }

    int t = s.b - s.a;

    aux.w = s.w;
    aux.a = s.a;
    aux.b = (s.a + s.b)/2;
    aux.p = s.p;
    st.insert(aux);

    bitset<N> opp = (~(usd|adj[s.w]));

    for (int i = 0; i < n; i++) {
        DEBUG("%d\n", i+1);
        if (usd[i]) continue;
        DEBUG("not used\n");
        if (!adj[s.w][i]) continue;
        int cnt = (adj[i] & opp).count();
        DEBUG("achiavable %d on %d\n", cnt, t);
        if (cnt < t/4 || cnt >= t/2) continue;
        DEBUG("good\n");

        adj[i] &= opp;
        usd[i] = 1;
        aux.w = i;
        aux.a = (s.a + s.b)/2;
        aux.b = s.b;
        aux.p = s.p+1;
        st.insert(aux);        
        break;
    }
}

int main () {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            str[i] = '0';
            r[i] = -1;
        }
        usd = bitset<N>(str);
        usd[0] = 1;
        for (int i = 0; i < n; i++) {
            scanf(" %s", str);
            inverse(str, str+n);
            adj[i] = bitset<N>(str);
        }
        
        st.clear();
        aux.w = aux.a = 0;
        aux.b = n;
        aux.p = 0;
        st.insert(aux);

        while (st.size()) {
            aux = *(st.begin());
            st.erase(st.begin());

            solve(aux);
        }

        int l = 0;

        for (int i = 0; i < n; i++) {
            if (r[i] == -1) {
                while (usd[l] || !(adj[0][l])) l++;
                r[i] = l++;
            }
            printf("%d ", r[i]+1);
        }
        printf("\n");
    }
}
