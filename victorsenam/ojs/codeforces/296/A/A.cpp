#include <bits/stdc++.h>

using namespace std;
typedef int num;

const int N = 1002;

int n;
int a;
int f[N];

int main ( ){
    scanf("%d", &n);

    for (int i  =0 ; i < n; i++){
        scanf("%d", &a);
        f[a]++;
        if (f[a] > (n+1)/2) {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
}
