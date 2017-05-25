#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 3e5+7;

char str[2][N];
char res[N];
int n;

int main () {
    scanf(" %s", str[0]);
    n = strlen(str[0]);
    scanf(" %s", str[1]);

    sort(str[0], str[0] + n);
    sort(str[1], str[1] + n);

    int a[2] = {0, (n+1)/2 - 1};
    int b[2] = {(n+1)/2, n - 1};

    bool t = 0;
    int l = 0, r = n-1;
    while (l <= r) {
        if (!t) {
            if (str[0][a[0]] >= str[1][b[1]]) {
                res[r--] = str[0][a[1]--];
            } else {
                res[l++] = str[0][a[0]++];
            }
        } else {
            if (str[1][b[1]] <= str[0][a[0]]) {
                res[r--] = str[1][b[0]++];
            } else {
                res[l++] = str[1][b[1]--];
            }
        }
        t = !t;
    }
    res[n] = 0;
    printf("%s\n", res);
}
