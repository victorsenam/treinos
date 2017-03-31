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

int v[5][5];

bool a (bool x, bool y)
{ return (x&y); }
bool b (bool x, bool y)
{ return (x^y); }
bool c (bool x, bool y)
{ return (x|y); }

int main () {
    for (int i = 0; i < 4; i++)
        scanf("%d", &v[0][i]);

    v[1][0] = b(v[0][0], v[0][1]);
    v[1][1] = c(v[0][2], v[0][3]);
    v[1][2] = a(v[0][1], v[0][2]);
    v[1][3] = b(v[0][0], v[0][3]);

    v[2][0] = a(v[1][0], v[1][1]);
    v[2][1] = c(v[1][2], v[1][3]);

    printf("%d\n", b(v[2][0], v[2][1]));
}
