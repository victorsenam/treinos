#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

int ts;
int n, m;
char str[100];

int main () {
    scanf("%d", &ts);

    while (ts--) {
        scanf("%d %d", &m, &n);
        scanf(" %s", str);
            
        int x = 0, y = 0;
        int lx[2] = {0,0}, ly[2] = {0,0};

        for (int i = 0; str[i]; i++) {
            if (str[i] == 'R')
                x++;
            else if (str[i] == 'L')
                x--;
            else if (str[i] == 'U')
                y--;
            else
                y++;
            lx[0] = min(lx[0], x);
            lx[1] = max(lx[1], x);
            ly[0] = min(ly[0], y);
            ly[1] = max(ly[1], y);
        }

        if (n >= abs(lx[1] - lx[0] + 1) && m >= abs(ly[1] - ly[0] + 1))
            printf("safe\n");
        else
            printf("unsafe\n");
    }
}
