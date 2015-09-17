#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 1000007;
const num MOD = 1000000009ll;

int t;
int s[3];
char str[3][N];
num memo1[N][2][2];
num memo2[N][2];
num memo3[N];
int visi1[N][2][2];
int visi2[N][2];
int visi3[N];
int turn;

num pd2 (int p, int f1)

num pd1 (int p, int f1, int f2) {
    if (p >= s[0])
        return pd(p, f2);

    num & me = memo1[p][f1][f2];

    if (visi1[p][f1][f2] == turn)
        return me;

    me = 0;
    for (char i = 'a'; i <= 'z'; i++) {
        if (
        for (char j = 'a'; j <= 'z'; j++) {
            for (char k = 'a'; k <= 'z'; k++) {
            }
        }
    }
}
