#include <bits/stdc++.h>

using namespace std;

const int N = 200007;

char str[N];
char ind[256];
char mp[256];
char a, b;
int n, m;

int main () {
    scanf("%d %d", &n, &m);
    scanf(" %s", str);

    for (int i = 'a'; i <= 'z'; i++) {
        mp[i] = i;
        ind[i] = i;
    }

    for (int i = 0; i < m; i++) {
        scanf(" %c %c", &a, &b);
        
        swap(ind[a], ind[b]);
        mp[ind[a]] = a;
        mp[ind[b]] = b;
    }

    for (int i = 0; i < n; i++)
        printf("%c", mp[str[i]]);
    printf("\n");
}
