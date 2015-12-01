#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

num calc (num x, num m, num w) 
{ return max(num(75)*x, (250-m)*x-12500*w); }

const num t[6] = {500, 1000, 1500, 2000, 2500};

num m[6], w;

int main () {
    for (int i = 0; i < 5; i++) {
        scanf("%I64d", m+i);
    }

    num ans = 0;
    for (int i = 0 ; i < 5; i++) {
        scanf("%I64d", &w);
        ans += calc(t[i], m[i], w);
    }

    scanf("%I64d", &w);
    ans += num(100*250)*w;
    scanf("%I64d", &w);
    ans -= num(50*250)*w;
    printf("%I64d\n", ans/num(250));
}
