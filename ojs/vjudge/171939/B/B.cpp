#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<ll,ll> pii;

const int M = 1e7+2;
const int N = 1e4;

int x[N];
int pr[N];
int n;
ll v[N], q[N], vs;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x[i];
        pr[x[i]]++;
    }
    
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

    ll res = 0;
    for (int i = vs-1; i >= 0; i--) {
        ll cs = 0, qtd = 0;
        int k = 0;
        for (int j = i-1; j >= 0; j--) {
            while (k < i && v[j] + v[k] < v[i])
                k++;
            if (j < k) break;
            if (j == k) {
                qtd += cs * q[j] * (q[j]-1)/2;
                qtd += q[j]*(q[j]-1)*(q[j]-2)*(q[j]-3)/4;
            } else {
                qtd += cs * q[j] * q[k];
                cs += q[j] * q[k];
            }
        }
        res += qtd * q[i] * (q[i]-1) / 2;

        qtd = 0;
        for (int j = i-1; j >= 0; j--) {
            int b = v[i] - v[j];
            if (b > v[j]) break;
            qtd += q[j] * pr[b];
        }
        res += qtd * q[i] * (q[i]-1) * (q[i]-2) / 6;
    }
    cout << res << endl;
}
