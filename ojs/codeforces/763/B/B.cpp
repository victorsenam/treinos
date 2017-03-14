#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 6e5+7;

int n;
int v[N][4];

int main () {
    scanf("%d", &n);

    printf("YES\n");
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < 4; k++) {
            scanf("%d", &v[i][k]);
        }
        printf("%d\n", abs(v[i][0]%2) + abs(v[i][1]%2)*2 + 1);
    }
}
