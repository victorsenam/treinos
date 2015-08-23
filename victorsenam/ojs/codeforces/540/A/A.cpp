#include <bits/stdc++.h>

using namespace std;

typedef int num;
char fst[1001];
char a;
int n;
int cnt;
int dist;

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) scanf(" %c", &fst[i]);

    cnt = 0;
    for (int i = 0; i < n; i++) {
        scanf(" %c", &a);
        dist = fst[i] - a;
        if (dist < 0) dist = -dist;
        if (dist > 10-dist) dist = 10-dist;
        cnt += dist;
    }
    
    printf("%d\n", cnt);
}
