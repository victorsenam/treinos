#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 52;

int n;
int ts;
int c[N][N];
int dead[N];
queue<int> qu;

bool check () {
    bool ok = 0;
    for (int i = 0; i < n; i++) {
        if (dead[i]) continue;
        set<int> s;
        for (int j = 0; j < n; j++) {
            if (dead[j] || i == j) continue;
            s.insert(c[i][j]);
        }
        if (s.size() < 2) {
            dead[i] = 1;
            ok = 1;
        }
    }
    return ok;
}

int main () {
    scanf("%d", &ts);
    
    while (ts--) {
        scanf("%d", &n);
        
        for (int i = 0; i < n; i++) {
            dead[i] = 0;
            for (int j = 0; j < n; j++)
                scanf("%d", &c[i][j]);
        }

        while (check());

        int res = 0;
        for (int i = 0; i < n; i++)
            res += (!dead[i]);
        printf("%d\n", res);
    }
}
