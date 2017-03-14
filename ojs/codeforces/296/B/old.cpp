#include <bits/stdc++.h>

using namespace std;
typedef long long int num;

const int N = 100007;
const num MOD = 1000000007ll;

bool g, l;
int n;
char a[N], b[N];
int un, du;

num mod (num a) {
    return (a%MOD + MOD)%MOD;
}

int main ( ){
    scanf("%d", &n);

    scanf(" %s %s", a, b);

    for (int i = 0; i < n ;i++) {
        if (a[i] == '?' && b[i] == '?')
            du++;
        else if (a[i] == '?' || b[i] == '?')
            un++;
        else if (a[i] > b[i])
            g = 1;
        else if (b[i] > a[i])
            l = 1;
    }

    num ue = 1;
    for (int i = 1; i < un; i++)
        ue = mod(ue*26);
    num de = 1;
    for (int i = 1; i < du; i++)
        de = mod(de*26);

    num ans = 0;
    if (g && l) {
        ans = 1;
        if (un)
            ans = mod(ans*mod(ue*26));
        else if (du)
            ans = mod(ans*mod(mod(de*26)*mod(de*26)));
    } else if (g || l) {
        ans = 0;
        for (int i = 0; i < n; i++) {
            num loc = 1;
            if (a[i] == '?' && b[i] == '?') {
                loc = mod(loc*mod(de*de));
                loc = mod(loc*ue);
                if (un)
                    loc = mod(loc*26);
                loc = mod(loc*13*25);
            } else if (a[i] == '?' || b[i] == '?') {
                loc = mod(loc*mod(de*de));
                loc = mod(loc*mod(ue));
                if (du)
                    loc = mod(mod(loc*26)*26);
                
                if (g) {
                    if (a[i] == '?')
                        loc = mod(loc*(b[i]-'a'));
                    else
                        loc = mod(loc*('z'-a[i]));
                } else {
                    if (b[i] == '?')
                        loc = mod(loc*(a[i]-'a'));
                    else
                        loc = mod(loc*('z'-b[i]));
                }
            } else
                continue;
            ans = mod(ans+loc);
        }
    } else {
        ans = 1;
        if (un)
            ans = mod(ans*mod(ue*26));
        else if (du)
            ans = mod(ans*mod(mod(de*26)*mod(de*26)));
        
        num dw = 1;
        num up = 1;
        for (int i = 0; i < n; i++) {
            if (a[i] == '?' && b[i] == '?') {
                dw = mod(dw*13*26);
                up = mod(up*13*26);
            } else if (a[i] == '?') {
                dw = mod(dw*(b[i]-'a'+1));
                up = mod(up*('z'-b[i]+1));
            } else if (b[i] == '?') {
                dw = mod(dw*('z'-a[i]+1));
                up = mod(up*(a[i]-'a'+1));
            }
            printf("%lld %lld\n", dw, up);
        }

        ans = mod(mod(ans-dw)-up);
    }

    printf("%lld\n", ans);
}
