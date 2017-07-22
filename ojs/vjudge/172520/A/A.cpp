#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 112345;
int S[N], sz[N], swp[N];

int ch[N * 80], cn;
inline int find(int i) {
    while(S[i] != i) i = S[i];
    return i;
}

int get_c(int);

#define printf(args...) ((void) 0)

bool join(int a, int b) {
    printf("join(%d, %d)\n", a, b);
    int sw = (get_c(a) == get_c(b));
    if((a = find(a)) == (b = find(b))) return false;
    printf("okjoin\n");
    if(sz[a] < sz[b]) swap(a, b);
    assert(cn < N * 30);
    ch[cn++] = b;
    printf("%d->%d\n", b, a);
    S[b] = a;
    swp[b] = sw;
    sz[a] += sz[b];
    return true;
}

int get_c(int i) {
    int c = 0;
    printf("color of %d is ", i);
    while(S[i] != i) { c = (c ^ swp[i]); i = S[i]; }
    printf("%d\n", c);
    return c;
}

inline void rollback() {
    int u = ch[--cn];
    printf("%d-/>%d\n", u, S[u]);
    sz[S[u]] -= sz[u];
    S[u] = u;
}


int ok[N];
int l[N], r[N], a[N], b[N], p[N];
int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, q, i, j, g;
    cin >> n >> m >> q;
    for(i = 0; i < m; i++) {
        cin >> a[i] >> b[i]; a[i]--; b[i]--;
    }
    for(i = 0; i < q; i++) {
        cin >> l[i] >> r[i]; l[i]--; r[i]--;
        p[i] = i;
    }
    int sq = sqrt(m);
    printf("sq %d\n", sq);
    sort(p, p + q, [sq](int i, int j) {
        int bli = l[i] / sq, blj = l[j] / sq;
        if(bli != blj) return bli < blj;
        return r[i] < r[j];
    });
    int pr = -1, R;
    bool bad = false;
    for(int i_ = 0; i_ < q; i_++) {
        i = p[i_];
        printf("[%d]query(%d, %d)\n", i, l[i], r[i]);
        if(pr != (l[i] / sq)) {
            printf("REMAKE\n");
            pr = l[i] / sq;
            for(j = 0; j < n; j++) S[j] = j, sz[j] = 1;
            cn = 0;
            R = (pr + 1) * sq;
            bad = false;
        }
        int M = cn; // rollback
        if(r[i] < (pr + 1) * sq) {
            for(g = l[i]; g <= r[i]; g++) {
                if(!join(a[g], b[g]) && get_c(a[g]) == get_c(b[g])) { printf("this\n"); break; }
            }
            printf("g %d\n", g);
            if(g <= r[i]) ok[i] = 0;
            else ok[i] = 1;
            while(cn > M) rollback();
        } else {
            while(!bad && R <= r[i]) {
                printf("exp R %d\n", R);
                if(!join(a[R], b[R]) && get_c(a[R]) == get_c(b[R])) bad = true;
                R++;
            }
            if(bad) ok[i] = 0;
            else {
                M = cn;
                for(g = (pr + 1) * sq - 1; g >= l[i]; g--) {
                    if(!join(a[g], b[g]) && get_c(a[g]) == get_c(b[g])) break;
                }
                if(g >= l[i]) ok[i] = 0;
                else ok[i] = 1;
                while(cn > M) rollback();
            }
        }
        printf("ans = %d\n", ok[i]);
    }
    for(i = 0; i < q; i++)
        if(ok[i])
            cout << "Possible\n";
        else
            cout << "Impossible\n";
}
