#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;
typedef pair<int, int> pii;
#define pb push_back
char s[110];
ll memo[100][20][2][2];
int seen[100][20][2][2], tempo;
ll solve(int i, int lst, bool up, bool pre) {
    if(!s[i]) return 1;
    ll &r = memo[i][lst][up][pre];
    if(seen[i][lst][up][pre] == tempo) return r;
    seen[i][lst][up][pre] = tempo;
    r = 0;
    for(int d = 0; d < 10; d++) {
        if(pre && d > (s[i] - '0')) break;
        if(d > lst && !up) continue;
        r += solve(i + 1, d, up && (d >= lst), pre && (d == s[i] - '0'));
    }
    return r;
}

int main() {
    int i, t;
    ios::sync_with_stdio(0);
    cin.tie(0);
    scanf("%d", &t);
    while(t--) {
        tempo++;
        scanf("%s", s);
        bool up = true;
        for(i = 1; s[i]; i++) {
            if(s[i] == s[i - 1]) continue;
            else if(s[i] > s[i - 1]) {
                if(!up) break;
            } else {
                up = false;
            }
        }
        if(s[i]) { puts("-1"); continue; }
        printf("%lld\n", solve(0, 0, true, true) - 1ll);
    }
}
