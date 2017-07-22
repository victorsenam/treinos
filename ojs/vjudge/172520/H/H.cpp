#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1123456;
pii tr[N << 2];
pii tr2[N << 2];

int A[N];

bool cmpA(int i, int j) { if(A[i] != A[j]) return A[i] < A[j]; else return i < j; }

struct tri {
    int a[3];
    bool operator < (tri o) const {
        if(A[a[0]] != A[o.a[0]]) return A[a[0]] < A[o.a[0]];
        if(A[a[1]] != A[o.a[1]]) return A[a[1]] < A[o.a[1]];
        return A[a[2]] < A[o.a[2]];
    }
    tri() {}
    tri(int x, int y, int z) { a[0] = x; a[1] = y; a[2] = z; }
};

vector<tri> ans;

void build(int i, int l, int r) {
    if(l == r) { (tr[i] = pii(A[l], l)); tr2[i] = pii(A[l], -l); return; }
    int m = (l + r) / 2;
    build(2 * i, l, m);
    build(2 * i + 1, m + 1, r);
    tr[i] = min(tr[2 * i], tr[2 * i + 1]);
    tr2[i] = min(tr2[2 * i], tr2[2 * i + 1]);
}

pii get(int i, int l, int r, int ql, int qr) {
    if(l > qr || r < ql) return pii(INT_MAX, INT_MAX);
    if(l >= ql && r <= qr) return tr[i];
    int m = (l + r) / 2;
    return min(get(2 * i, l, m, ql, qr), get(2 * i + 1, m + 1, r, ql, qr));
}

pii get2(int i, int l, int r, int ql, int qr) {
    if(l > qr || r < ql) return pii(INT_MAX, INT_MIN);
    if(l >= ql && r <= qr) return tr2[i];
    int m = (l + r) / 2;
    return min(get2(2 * i, l, m, ql, qr), get2(2 * i + 1, m + 1, r, ql, qr));
}

int n;

void solve(int l, int r) {
    if(r - l <= 1) return;
    int imin = get(1, 0, 2 * n - 1, l + 1, r - 1).second;
    int imin2 = -get2(1, 0, 2 * n - 1, l + 1, r - 1).second;
    if(A[r] >= A[l]) imin = imin2;
    ans.pb(tri(l, imin, r));
    solve(l, imin);
    solve(imin, r);
}

int p[N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int i;
    cin >> n;
    for(i = 0; i < n; i++)
        cin >> A[i];
    for(i = n; i < 2 * n; i++)
        A[i] = A[i - n];
    build(1, 0, 2 * n - 1);
    int a = get(1, 0, 2 * n - 1, 0, n - 1).second;
    int b = (a + 1) % n, c = -1;
    for(i = 1; i < n - 1; i++)
        if(A[(a + i) % n] < A[b])
            b = (a + i) % n;
    for(i = 1; i < n - 1; i++)
        if((b + i) % n != a && (c == -1 || A[(b + i) % n] < A[c]))
            c = (b + i) % n;
    int p[3] = {a, b, c};
    sort(p, p + 3);
        
    ans.pb(tri(p[0], p[1], p[2]));
    solve(p[0], p[1]);
    solve(p[1], p[2]);
    solve(p[2], p[0] + n);
    for(tri &t : ans)
        sort(t.a, t.a + 3, cmpA);
    sort(ans.begin(), ans.end());
    for(tri t : ans)
        cout << (t.a[0] % n) + 1 << ' ' << (t.a[1] % n) + 1 << ' ' << (t.a[2] % n) + 1 << '\n';
}
