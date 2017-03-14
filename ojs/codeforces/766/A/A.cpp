#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N =1e5+7;
char str[2][N];
int n[2];

int main () {
    scanf(" %s %s", str[0], str[1]);

    n[0] = strlen(str[0]);
    n[1] = strlen(str[1]);

    if (n[0] != n[1] || strcmp(str[0], str[1]) != 0) {
        printf("%d\n", max(n[0], n[1]));
    } else {
        printf("-1\n");
    }
}
