#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100007

int n, p, res, a, b;
char str[N];
int val[N];

int main () {
    scanf("%d %d", &n, &p);
    scanf(" %s", str);

    res = 0;
    p--;
    p = min(p, n-p-1);

    for (int i = 0; i < n/2 + n%2; i++) {
        a = max(str[n-i-1], str[i]);
        b = min(str[n-i-1], str[i]);
        val[i] = min(a - b, 'z'-'a'+1+b-a);
        res += val[i];
    }
    
    a = b = 0;
    for (int i = p; i < n/2 + n%2; i++)
        if (val[i]) 
            a = max(a, i-p);
    
    for (int i = p; i >= 0; i--)
        if (val[i])
            b = max(b, p-i);

    res += min(2*a+b, 2*b+a);

    printf("%d\n", res);
}
