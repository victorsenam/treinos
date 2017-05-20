#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

char str[10];

bool query (int a, int b) {
    printf("%d %d\n", a, b);
    fflush(stdout);
    scanf("%s", str);
    return (str[0] == 'T');
}

int main () {
    int n, k;

    scanf("%d %d", &n, &k);

    int a = 1, b = n;

    while (a < b) {
        int md = (a+b)/2;

        if (query(a,b))
            b = md;
        else
            a = md+1;
    }

    
}
