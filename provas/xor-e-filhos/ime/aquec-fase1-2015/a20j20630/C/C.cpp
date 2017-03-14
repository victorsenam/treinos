#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

num att;
num a;
int t;
int n;

int main () {
    scanf("%d", &t);
    
    while (t--) {
        scanf("%d", &n);

        att = 0;
        for (int i = 0; i < n; i++) {
            scanf("%llu", &a);
            if (a%2llu)
            {
                while (true)
                {
                    if (a%2llu == 0) break;
                    else
                        a /= 2llu;
                }
            }
            a /= 2llu;
            att ^= a;
        }
        if (att)
            printf("YES\n");
        else
            printf("NO\n");
    }
}
