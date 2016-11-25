// Convex Trick para Otimizar PDs onde as escolhas de estado são retas com coeficiente angular crescente (basta inverter o ângulo caso seja decrescente) e busca-se maximizar o valor alcançado (fácil de adaptar para mínimo)
// Caso se inverta o ângulo, deve procurar o mínimo ao invés do máximo e vice-versa
// Inserção O(n) amortizado
// Busca O(log(n))
// Alterações pra gerar o caso mínimo estão marcadas com MIN
// http://wcipeg.com/wiki/Convex_hull_trick
#include <bits/stdc++.h>

using namespace std;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {} {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); }
#else
#define DEBUG(...) {}
#endif

const int N = 1e5+7;

typedef double num;
typedef long long ll;

struct cvx {
    num sa[N], sb[N], st[N];
    int ss;

    inline num numdiv (num a, num b)
    { return (a+b-1)/b; } // MIN: a/b

    inline num inter (int i) {
        if (!i)
            return -1./0.; // MIN: LLONG_MAX

        return numdiv(sb[i]-sb[i-1], sa[i-1]-sa[i]);
    }

    int insert (num a, num b) {
        if (ss && sa[ss-1] == a) {
            if (sb[ss-1] >= b) // MIN: <=
                return -1;

            ss--;
        }

        sa[ss] = a;
        sb[ss] = b;
        st[ss] = inter(ss);

        while (ss && st[ss] <= st[ss-1]) { // MIN: >=
            sa[ss-1] = sa[ss];
            sb[ss-1] = sb[ss];
            ss--;
            st[ss] = inter(ss);
        }

        DEBUG("insert (%f,%f) at %f\n", a, b, st[ss]);
        return ss++;
    }

    inline void reset()
    { ss = 0; }

    num get (num x) { // da pra deixar linear se os x forem ordenados
        int l = upper_bound(st, st+ss, x) - st - 1; // MIN: comparar decrescente
        DEBUG("get %d (%f,%f) for %f\n", l, sa[l], sb[l], x);
        return sa[l]*x + sb[l];
    }
};

int n;
ll v[N][2][2];
int r[N][2];
int p[N];
int k;
cvx trk[2];

bool cmp_t (int i, int j) {
    if (v[i][k][0] == v[j][k][0])
        return v[i][k][0] > v[j][k][0];
    if (v[i][k][1] == v[j][k][1])
        return v[i][k][1] > v[j][k][1];
    return i < j;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i] = i;
        for (int k = 0; k < 2; k++) {
            for (int j = 1; j >= 0; j--) {
                scanf("%lld", &v[i][k][j]);
                if (k)
                    v[i][k][j] = -v[i][k][j];
            }
        }
    }

    for (k = 0; k < 2; k++) {
        DEBUG("== %d =========\n", k);
        sort(p, p+n);

        for (int _i = 0; _i < n; _i++) {
            int i = p[_i];

            r[i][k] = trk[k].insert(v[i][k][0], v[i][k][1]);
            if (v[i][k][0] == v[p[_i-1]][k][0] && v[i][k][1] == v[p[_i-1]][k][1])
                r[i][k] = -1;
        }
        trk[k].st[trk[k].ss] = 1./0.;
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        bool ok = 1;
        double mi = 0.;
        double ma = 1./0.;

        DEBUG("-- %d --\n", i);
    
        for (int k = 0; k < 2; k++) {
            DEBUG("%d\n", r[i][k]);
            if (r[i][k] == -1) ok = 0;
            else if (trk[k].ss <= r[i][k]) ok = 0;
            else if (trk[k].sa[r[i][k]] == v[i][k][0] && trk[k].sb[r[i][k]] == v[i][k][1]) ok = 0;
            else {
                mi = max(mi, trk[k].st[r[i][k]]);
                ma = min(ma, trk[k].st[r[i][k]+1]);       
            }
        }

        DEBUG("[%d] [%f %f]\n", ok, mi, ma);

        if (ok && mi < ma) {
            res++;
        }
    }

    printf("%d\n", res);
}
