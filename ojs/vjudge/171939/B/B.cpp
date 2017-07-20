#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 2e7+2;
const int M = 1e4;

int x[M];
int pr[N];
int n;
ll v[M], q[M], vs;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x[i];
        pr[x[i]]++;
    }
    
    ll res = 0;
    for (int i = 0; i < N; i++) {
        if (pr[i]) {
            v[vs] = i;
            q[vs] = pr[i];
            vs++;
        }
        pr[i] = 0;
    }

    for (int i = 0; i < vs; i++) {
        if (v[i]+v[i] < N)
            pr[v[i]+v[i]] += q[i]*(q[i]-1)/2;
        for (int j = i+1; j < vs; j++) {
            if (v[i]+v[j] < N)
                pr[v[i]+v[j]] += q[i]*q[j];
        }
    }

    for (int i = vs-1; i >= 0; i--) {
        ll cs = 0, qtd = 0;
        int k = 0;
        for (int j = i-1; j >= 0; j--) {
            while (k < i && v[j] + v[k] < v[i])
                k++;
            if (j < k) break;
            if (v[j] + v[k] != v[i]) continue;
            if (j == k) {
                qtd += cs * q[j] * (q[j]-1)/2;
                qtd += q[j]*(q[j]-1)*(q[j]-2)*(q[j]-3)/24;
            } else {
                qtd += cs * q[j] * q[k] + q[j] * (q[j] - 1) * q[k] * (q[k] - 1) / 4;
                cs += q[j] * q[k];
            }
        }
        res += qtd * q[i] * (q[i]-1) / 2;
    }

    memset(pr, 0, sizeof pr);
    sort(x, x+n, greater<int>());
    for (int i = n-1; i >= 0; i--) {
        //cout << "=== " << i << endl;
        int ls = 0;
        ll qt = 0;
        for (int k = 0; ls != x[i] && k <= i; k++) {
            if (k == i || x[k] != ls) {
                if (ls) {
                    //cout << "com " << ls << "[" << k << "] (" << qt << " choose " << 3 << ") * " << ls-x[i] << ":" << pr[ls-x[i]] << endl;
                    res += (qt * (qt - 1) * (qt - 2) / 6) * pr[ls - x[i]];
                }
                ls = x[k];
                qt = 1;
            } else {
                qt++;
            }
        }
        
        for (int j = i+1; j < n; j++)
            pr[x[i] + x[j]]++;
    }

    cout << res << endl;
}
