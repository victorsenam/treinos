#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

ll res;
int n, k;
ll v[N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> k;
    ll mn = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        mn = min(mn, v[i]);
    }

    ll cur = 0;
    stack<int> st;
    for (int i = 0; i < k; i++) {
        cur += v[i];
        st.push(i);
    }

    for (int i = k; i <= n; i++) {
        while (cur >= 0) { 
            if (v[st.top()] == mn) {
                st.pop();
            } else {
                ll ls = min(v[st.top()] - mn, cur + 1);
                v[st.top()] -= ls;
                cur -= ls;
                res += ls;
            }
        }

        cur += v[i];
        cur -= v[i-k];
        st.push(i);
    }

    cout << res << endl;
    for (int i = 0; i < n; i++)
        cout << v[i] << " ";
    cout << endl;
}
