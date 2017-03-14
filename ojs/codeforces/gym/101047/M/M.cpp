#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5+7;

int t;
int n;
int l;
char c;
int r[N], rs;
bool ch;
int ls;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        rs = 0;
        ls = -1;
        ch = 0;
        
        for (int i = 0; i < n; i++) {
            scanf(" %c", &c);

            if ((c=='D')^(ls == i)) {
                for (int j = i; j >= ls && j >= 0; j--)
                    r[rs++] = j;
                ls = i+1;
            }
        }

        if (ls == n) {
            printf("Y\n");
            for (int i = 0; i < n; i++)
                printf("%d ", r[i]+1);
            printf("\n");
        } else {
            printf("N\n");
        }
    }
}
