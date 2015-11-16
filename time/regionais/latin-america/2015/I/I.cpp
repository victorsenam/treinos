#include <bits/stdc++.h>

using namespace std;

int main () {
    int n;
    while (scanf("%d", &n) != EOF) {

        int res =0 ;
        int a;
        for (int i = 0 ; i < 5; i++) {
            scanf("%d", &a);
            if (a == n)
                res++;
        }
        printf("%d\n", res);
    }
}
