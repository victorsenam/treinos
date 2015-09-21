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

inline num mod (num a) {
    return (a%MOD + MOD)%MOD;
}

int lin[N];
char name[N][S];
char temp[S];
int n;
int res[N];
int ss;
int maxi;
num code[N][M];
num pot[S];
num kla[M], klb[M];

bool solve (int c, int k) {
    num p = 1llu;

    if (lin[c] - k <= 0)
        return 0;
    if (lin[n] - k <= 0)
        return 0;

    kla[0] = code[c][0];
    klb[0] = code[n][0];
    for (int i = 1; i < k; i++) {
        kla[0] = mod(mod(kla[0]*pot[S]) + code[c][i]);
        klb[0] = mod(mod(klb[0]*pot[S]) + code[n][i]);
        p = mod(p*pot[S]);
    }

    for (int i = 1; i <= lin[c]-k; i++)
        kla[i] = mod(mod(mod(kla[i-1] - mod(p*code[c][i-1]))*pot[S]) + code[c][i+k-1]);
    for (int i = 1; i <= lin[n]-k; i++)
        klb[i] = mod(mod(mod(klb[i-1] - mod(p*code[n][i-1]))*pot[S]) + code[n][i+k-1]);

/*
    printf("k = %d\n", k);
    printf("%s\n", name[c]);
    for (int i = 0; i <= lin[c]-k; i++)
        printf("[%d,%d] -> %llu\n", i, i+k-1, kla[i]);
    printf("%s\n", name[n]);
    for (int i = 0; i <= lin[n]-k; i++)
        printf("[%d,%d] -> %llu\n", i, i+k-1, klb[i]);
*/

    sort(kla, kla+lin[c]-k+1);
    sort(klb, klb+lin[n]-k+1);

    int ia, ib;
    ia = ib = 0;
    while (ia <= lin[c]-k && ib <= lin[n]-k) {
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
            else {
                name[i][0] = 'M';
                name[i][1] = '\0';
            }

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
