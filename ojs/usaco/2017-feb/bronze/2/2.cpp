#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

char str[100];
int n = 52;
int mp[600][2];

int main () {
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);
    scanf(" %s", str);

    for (int i = 0; i < n; i++) {
        swap(mp[str[i]][0], mp[str[i]][1]);
        mp[str[i]][0] = i;
    }

    for (int i = 'A'; i <= 'Z'; i++) {
        if (mp[i][0] > mp[i][1])
            swap(mp[i][0], mp[i][1]);
    }

    int res = 0;

    for (int i = 'A'; i <= 'Z'; i++)
        for (int j = i+1; j <= 'Z'; j++) {
            bool cr = 0;

            for (int k = 0; k < 2; k++)
                cr ^= (mp[i][0] <= mp[j][k] && mp[j][k] <= mp[i][1]);
            res += cr;
        }

    printf("%d\n", res);
}
