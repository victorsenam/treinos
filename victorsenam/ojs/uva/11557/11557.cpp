// WA e TLE
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 107;
const int S = 257;
const int P = 254;
const int M = 10007;
const string ender = "***END***";
const num MOD = 1000000007llu;
const num B = 307llu;

int lin[N];
num code[N][M];
char name[N][S];
char temp[S];
int n;
int res[N];
int ss;
int maxi;
num pot[S];
num kla[M], klb[M];

inline num mod (num a) {
    return (a%MOD + MOD)%MOD;
}

bool solve (int c, int k) {
    int m;
    num p = 1llu;

    m = min(lin[c], lin[n]) - k;
    if (m <= 0)
        return 0;

    for (int i = 0; i < k; i++) {
        kla[0] = mod(mod(kla[0]*pot[S]) + code[c][i]);
        klb[0] = mod(mod(klb[0]*pot[S]) + code[n][i]);
        if (i)
            p = mod(p*pot[S]);
    }

    for (int i = 1; i < m; i++) {
        kla[i] = mod(mod(mod(kla[i-1] - p*(kla[i-1]))*pot[S]) + kla[i+k]);
        klb[i] = mod(mod(mod(klb[i-1] - p*(klb[i-1]))*pot[S]) + klb[i+k]);
    }

    sort(kla, kla+m);
    sort(klb, klb+m);

    int ia, ib;
    ia = ib = 0;

    while (ia < m && ib < m) {
        if (kla[ia] == klb[ib])
            return 1;
        else if (kla[ia] < klb[ib])
            ia++;
        else
            ib++;
    }

    return 0;
}

int main () {
    pot[0] = 1llu;
    for (int i = 1; i <= S; i++)
        pot[i] = mod(pot[i-1]*B);

    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i <= n; i++) {
            lin[i] = 0;
            if (i < n)
                scanf(" %[ -~]", name[i]);

            while (scanf(" %[ -~]", temp) && strcmp(temp, ender.c_str())) {
                int k = 0;
                for (int j = 0; temp[j] != '\0'; j++)
                    if (temp[j] != temp[j+1] || temp[j] != ' ')
                        temp[k++] = temp[j];
                temp[k++] = '\0';
                if (k == 1)
                    continue;

                code[i][lin[i]] = 0llu;
                for (int j = 0; j < k; j++)
                    code[i][lin[i]] = mod(code[i][lin[i]] + mod(pot[S-j-1]*temp[j]));
                lin[i]++;
            }
        }

        maxi = 0;
        ss = 0;

        for (int i = 0; i < n; i++) {
            int lo = max(maxi-1, 0);
            int hi = min(lin[i], lin[n]);
            int mid = (lo+hi+1)/2;

            while (lo < hi) {
                mid = (lo+hi+1)/2;
                
                if (solve(i, mid)) {
                    lo = mid;
                } else {
                    hi = mid-1;
                }
            }
            mid = lo;
            
            if (mid == maxi)
                res[ss++] = i;
            else if (mid > maxi) {
                maxi = mid;
                ss = 0;
                res[ss++] = i;
            }
        }

        printf("%d", maxi);
        if (!maxi)
            ss = 0;
        for (int i = 0; i < ss; ++i)
            printf(" %s", name[res[i]]);
        printf("\n");
    }
}
