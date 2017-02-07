#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e3+7;
const ll MOD = 1e9+7;

int a[26];

ll memo[N];
ll m2[N], m3[N];
int n;
char str[N];
int ss[N];

ll pd (int i) {
    if (i == n) return 1;

    ll & me = memo[i];
    if (me != -1)
        return me;

    me = 0;
    m2[i] = n+1;
    m3[i] = 0;

    int l = n;

    for (int j = i; j < l; j++) {
        if (i + a[ss[j]] >= j) {
            l = min(l, i+a[ss[j]]);
        } else {
            l = i+a[ss[j]];
        }
    }


    for (int j = i+1; j <= l; j++) {
        me = (me + pd(j))%MOD;
        m2[i] = min(m2[i], m2[j]+1);
        m3[i] = max(m3[i], ll(j-i));
    }

    return me;
}

int main () {
    memset(memo, -1, sizeof memo);
    scanf("%d", &n);
    scanf(" %s", str);

    for (int i = 0; i < n; i++) {
        ss[i] = str[i] - 'a';
    }

    for (int i = 0; i < 26; i++)
        scanf("%d", &a[i]);
    m2[n] = 0;
    m3[n] = 0;

    printf("%lld\n", pd(0));
    printf("%lld\n", m3[0]);
    printf("%lld\n", m2[0]);

}
