// WA

#include <bits/stdc++.h>

using namespace std;

const int N = 207;
const int S = 87;

int n, a, b, ss, t;
char temp[S];
string ori[N];
string des[N];
int ord[N][2];
map<string, int> mp;

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf("\n%[a-zA-Z .]s", temp);
            ori[n-i-1] = temp;
        }
        for (int i = 0; i < n; i++) {
            scanf("\n%[a-zA-Z .]s", temp);
            des[n-i-1] = temp;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (ori[i] == des[j]) {
                    ord[i][0] = j;
                    break;
                }
            }
            printf("%d ", ord[i][0]);
        }
        printf("\n");

        bool t = 0;
        while (42) {
            int mini = n;
            for (int i = 1; i < n; i++)
                if (ord[i][t] < ord[i-1][t])
                    mini = min(mini, ord[i-1][t]);
            
            if (mini == n)
                break;

            printf("%s\n", des[mini].c_str());

            int j = 0;
            ord[0][!t] = mini;
            for (int i = 1; i < n; i++) {
                if (ord[i][t] != mini)
                    ord[j++][!t] = ord[i][t];
            }
        }
    }
}
