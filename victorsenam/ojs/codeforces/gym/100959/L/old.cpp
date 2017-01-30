#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back
int n, m;

char s[5009], t[5009];

bool memo[5009][5009];
bool seen[5009][5009];
bool ok(int i, int j) {
    //printf("ok(%d, %d)\n", i, j);
    if(i == n && j == m) return true;
    bool &r = memo[i][j];
    if(seen[i][j]) return r;
    seen[i][j] = true;
    r = false;
    if(i < n && j < m && s[i] == t[j]) r = r || ok(i + 1, j + 1);
    if(i && j && j < m && t[j] != t[j - 1]) r = r || ok(i, j + 1);
    if(i && j && i - 1 < n && j < m && s[i - 1] != t[j]) r = r || ok(i, j + 1);
    //printf("ok(%d, %d) = %d\n", i, j, r);
    return r;
}

int main () {
    scanf("%s %s", s, t);
    n = strlen(s);
    m = strlen(t);
    if(ok(0, 0)) puts("Yes");
    else puts("No");
}
