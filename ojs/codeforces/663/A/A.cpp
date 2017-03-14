#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 107;

int p, l;
int n;
int vp, vl;
char c;
bool isp[N];

void fail () {
    printf("Impossible\n");
    exit(0);
}

int main () {
    p = 1;
    int q = 0;
    isp[q++] = 1;
    while (scanf(" ? %c", &c) != EOF) {
        if (c == '+')
            p++;
        else if (c == '-')
            l++;
        else
            break;
        isp[q++] = (c=='+');
    }

    scanf("%d", &n);
    if (n > n*p-l || n < p-n*l)
        fail();

    int curr = n;
    int att;

    printf("Possible\n");
    for (int i = 0; i < q; i++) {
        if (isp[i]) {
            p--;
            att = max(1, min(n, curr-p+l));
            curr -= att;
            if (i) 
                printf("+ ");
        } else {
            l--;
            att = max(1, min(n, -curr+p-l));
            curr += att;
            printf("- ");
       }
       printf("%d ", att);
    }

    printf("= %d", n);
}
