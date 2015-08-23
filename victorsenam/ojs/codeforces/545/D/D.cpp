#include <bits/stdc++.h>

using namespace std;

typedef int num;

#define N 100000

int n;
num v[N];
num sum;
int cnt;

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n ; i++) scanf("%d", &v[i]);
    sort(v, v+n);

    sum = 0;
    cnt = 0;
    for (int i = 0; i < n; i++) {
        if (sum <= v[i]) {
            sum += v[i];
            cnt++;
        }
    }        

    printf("%d\n", cnt);
}
