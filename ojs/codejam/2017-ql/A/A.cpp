#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e3+7;

int ts;
char str[N];
bool b[N];
int k;

int main () {
    scanf("%d", &ts);

    for (int tt = 1; tt <= ts; tt++) {
        printf("Case #%d: ", tt);
        scanf(" %s %d", str, &k);
        int n = strlen(str);
        for (int i = 0; i < n; i++)
            b[i] = (str[i] == '+');

        int c = 0;
        for (int i = 0; i + k <= n; i++) {
            if (b[i]) continue;
            for (int j = i; j < i+k; j++)
                b[j] = !b[j];
            c++;
        }

        for (int i = n - 1; i + k > n; i--)
            if (!b[i]) c = -1;

        if (c == -1)
            printf("IMPOSSIBLE\n");
        else
            printf("%d\n", c);
    }
}
