// WA

#include <bits/stdc++.h>

using namespace std;

const int N = 207;
const int S = 87;

int n, a, b, ss, t;
char temp[S];
string ori[N];
string des[N];
int ord[N];
map<string, int> mp;

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf(" %[a-zA-Z .]s", temp);
            ori[n-i-1] = temp;
        }
        for (int i = 0; i < n; i++) {
            scanf(" %[a-zA-Z .]s", temp);
            des[n-i-1] = temp;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (ori[i] == des[j]) {
                    ord[i] = j;
                    break;
                }
            }
        }

        while (42) {
            for (int i = 1; i < n; i++) {
                if (ord[i-1] > ord[i]) {
                    printf("%s
                }
            }
        }
    }
}
