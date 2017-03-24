#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;

int n, q;
int vl[26][4*N];
int lz[26][4*N];
int st[26][4*N];
int lm[4*N][2];
int qt[26];
char str[N];

void build (int u, int l, int r) {
    lm[u][0] = l; lm[u][1] = r;
    if (l == r)
        return;
    int md = (l+r)/2;
    build(2*u, l, md);
    build(2*u+1, md+1, r);
}

void refresh (int k, int u) {
    if (st[k][u]) vl[k][u] = 0;
    vl[k][u] += lz[k][u] * (lm[u][1] - lm[u][0] + 1);

    if (lm[u][0] != lm[u][1]) {
        st[k][2*u] |= st[k][u];
        lz[k][2*u] += lz[k][u];
        st[k][2*u+1] |= st[k][u];
        lz[k][2*u+1] += lz[k][2*u+1];
    }
    st[k][u] = lz[k][u] = 0;
}

int add (int k, int u, int l, int r, int x, int db = 1) {
    refresh(k,u);
    if (l <= lm[u][0] && lm[u][1] <= r) {
        lz[k][u] += x;
        refresh(k,u);
        return vl[k][u];
    } else if (lm[u][0] > r || lm[u][1] < l) {
        return vl[k][u];
    }
    
    return vl[k][u] = add(k, 2*u, l, r, x) + add(k, 2*u+1, l, r, x);
}

int reset (int k, int u, int l, int r) {
    refresh(k,u);
    if (l <= lm[u][0] && lm[u][1] <= r) {
        st[k][u] = 1;
        refresh(k,u);
        return vl[k][u];
    } else if (lm[u][0] > r || lm[u][1] < l) {
        return vl[k][u];
    }

    return vl[k][u] = reset(k, 2*u, l, r) + reset(k, 2*u+1, l, r);
}

int get (int k, int u, int l, int r) {
    refresh(k,u);
    if (l <= lm[u][0] && lm[u][1] <= r)
        return vl[k][u];
    else if (lm[u][0] > r || lm[u][1] < l)
        return 0;
    return get(k, 2*u, l, r) + get(k, 2*u+1, l, r);
}

int main () {
    scanf("%d %d", &n, &q);
    scanf(" %s", str);

    build(1, 1, n);

    for (int i = 1; i <= n; i++)
        add(str[i-1]-'a', 1, i, i, 1);
    
    for (int i = 0; i < q; i++) {
        int l, r, k;
        scanf("%d %d %d", &l, &r, &k);

        for (int j = 0; j < 26; j++) {
            qt[j] = get(j, 1, l, r);
            reset(j, 1, l, r);
        }
        int curr = l;
        if (k == 0) {
            for (int j = 0; j < 26; j++) {
                add(j, 1, curr, curr + qt[j] - 1, 1);
                curr += qt[j];
            }
        } else {
            for (int j = 25; j >= 0; j--) {
                add(j, 1, curr, curr + qt[j] - 1, 1);
                curr += qt[j];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            if (get(j, 1, i, i)) {
                putchar('a'+j);
                break;
            }
        }
    }
    putchar('\n');
}
