#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = (1<<10);

int memo[N][N][2][2][2][10];
int visi[N][N][2][2][2][10], turn;
char str[11];
int n;

int isvalid (int a, int m, int l) {
    if (a < 0 || a >= 10) return -1;
    if (!a && !l) return m;
    if (m&(1<<a)) return -1;
    return (m|(1<<a));
}

int pd (int ma, int mb, bool cr, bool la, bool lb, int i) {
    if (i == n)
        return (cr == 0);

    int & me = memo[ma][mb][cr][la][lb][i];
    if (visi[ma][mb][cr][la][lb][i] == turn)
        return me;
    visi[ma][mb][cr][la][lb][i] = turn;

    int v = str[i] - '0' + 10*cr;
    me = 0;
    for (int a = 0; !me && a < 10; a++) {
        int nma = isvalid(a,ma,la);
        if (nma == -1) continue;
        for (int b = v - a - 1; !me && b <= v - a; b++) {
            int nmb = isvalid(b,mb,lb);
            if (nmb == -1) continue;
            me = pd(nma,nmb,(a+b!=v),(la||a),(lb||b),i+1);
        }
    }
    return me;
}

void build (int ma, int mb, bool cr, bool la, bool lb, int i, bool w) {
    assert(pd(ma, mb, cr, la, lb, i));
    if (i == n)
        return;

    int v = str[i] - '0' + 10*cr;
    for (int a = 0; a < 10; a++) {
        int nma = isvalid(a,ma,la);
        if (nma == -1) continue;
        for (int b = v - a - 1; b <= v - a; b++) {
            int nmb = isvalid(b,mb,lb);
            if (nmb == -1) continue;
            if (pd(nma,nmb,(a+b!=v),(la||a),(lb||b),i+1)) {
                if (w) {
                    if (a || la)
                        cout << a;
                } else {
                    if (b || lb)
                        cout << b;
                }
                build(nma,nmb,(a+b!=v),(la||a),(lb||b),i+1,w);
                return;
            }
        }
    }
}

bool isbeau () {
    int msk = 0;
    for (int i = 0; i < n; i++)
        msk |= (1<<(str[i]-'0'));
    return (__builtin_popcount(msk) == n);
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        turn++;
        cin >> str;
        n = strlen(str);

        if (isbeau()) {
            cout << "1 " << str << endl;
        } else if (!pd(0,0,0,0,0,0)) {
            cout << "FAIL " << str << endl;
        } else {
            cout << "2 " << endl;
            build(0,0,0,0,0,0,1);
            cout << " ";
            build(0,0,0,0,0,0,0);
            cout << endl;
        }
    }
}
