#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 100;

int n, k;
int v[N];
int cr;
char str[10];

int main () {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < k-1; i++)
        v[i] = cr++;

    for (int i = k-1; i < n; i++) {
        scanf(" %s", str);

        if (str[0] == 'Y')
            v[i] = cr++;
        else
            v[i] = v[i-k+1];
    }

    for (int i = 0; i < n; i++)
        printf("%c%c ", 'A' + (v[i]/26), 'a' + (v[i]%26));
    printf("\n");
}
