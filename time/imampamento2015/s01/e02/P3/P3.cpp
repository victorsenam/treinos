#include <bits/stdc++.h>

using namespace std;

#define M 1024
#define N 101

int n, rq, aq, ans, a[12];
bool ok;
char memo[N][M];

int one (int val, int mask) {
    int a = (1<<(val%10))*(val!=0);
    int b = (1<<(val/10))*(val/10!=0);

    if (a == b)
        return 0;
    if ((a|b)&mask != (a|b)) 
        return 0;

    return (a|b)+1;
}

int two (int val, int mask) {
    int rr;
    for (int i = 1; i <= val/2 + 1; i++) {
        int a = i;
        int b = val - i;
        rr = one(a, mask);
        if (!rr) 
            continue;
        if (one(b, mask-(rr-1))) 
            return 1;
    }
    return 0;
}

char fill (int val, int mask) {
    if (memo[val][mask] != -1)
        return memo[val][mask];

    if (one(val, mask))
        return memo[val][mask] = 1;
    if (two(val, mask))
        return memo[val][mask] = 1;

    return memo[val][mask] = 0;
}

int main () {
    memset(memo, -1, sizeof(memo));
    
    int c = 1;
    while (scanf("%d", &n) != EOF && n) {
        for (int i = 0; i < n; i++)
            scanf("%d", a+i);

        ans = M-1;
        aq = 10;
        for (int i = 0; i < M; i++) {
            rq = 0;
            for (int j = i; j != 0; j /= 2)
                rq += j%2;

            ok = 1;
            for (int j = 0; j < n && ok; j++)
                ok = ok && fill(a[j], i);
            
            if (!ok) continue;

            aq = rq;
            ans = i;
        }

        printf("Case %d:", c++);
        for (int i = 9; i >= 0; i--) 
            if (((1<<i)&ans)) 
                printf(" %d", i);
        printf("\n");
    }
}
