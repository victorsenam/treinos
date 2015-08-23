#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;
typedef long long int ll;
const int P = 22;

num n, a;
int turn;
num memo[P][2][187];
int vis[P][2][187];
char str[P];

num solve (int pos, bool pre, int sum) {
    if (str[pos] == '\0')
        return sum;
    
    num & m = memo[pos][pre][sum];
    if (vis[pos][pre][sum] == turn)
        return m;
    vis[pos][pre][sum] = turn;
    
    m = 0;
    for (int i = 0; i < 10; i++) {
        if (pre && i > str[pos] - '0')
            break;
        m += solve(pos+1, (i == str[pos]-'0')&&pre, sum+i);
    }

    return m;
}

num ss() {
    turn++;
    sprintf(str, "%I64u\0", n);
    return solve(0, 1, 0);
}

num countDig (num n) {
    num res = 0;
    while (n) {
        res += n%10;
        n /= 10;
    }
    return res;
}

int main () {
    scanf("%I64u", &a);
    num lo = 1ull;
    num hi = 100000000000000000ull;
    num ans = 0;

    while (lo < hi) {
        n = (hi+lo)/2;
        ans = ss();
        //printf("%llu: %llu\n", n, ans);
        if (ans >= a)
            hi = n;
        else
            lo = n+1;
    }

    hi = lo;
    n = lo;
    ans = ss()%a;
    ll res = ans;
    lo = 1ull;

    //printf("[%llu, %llu] %lld\n", lo, hi, res);
    while (res) {
        if (res > 0)
            res -= countDig(lo++);
        else
            res += countDig(++hi);
    }

    printf("%I64u %I64u\n", lo, hi);
}
