#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 107;
const int S = 257;
const int M = 10007;
const string ender = "***END***";
const num MOD = 1000000007llu;
const num B = 307llu;

int lins[N];
string code[N][M];
char name[N][S];
char temp[S];
int n;
int res[N];
int ss;
int maxi;
num lia[M], lib[M];
num pta[M], ptb[M];
num kla[M], klb[M];

inline num mod (num a) {
    return (a%MOD + MOD)%MOD;
}

bool solve (int c, int k) {
    int qta, qtb;

    if (lins[c] < k)
        return 0;
    if (lins[n] < k)
        return 0;

    for (int i = 0; i < lins[c]; i++) {
        pta[i] = 1llu;
        lia[i] = 0;
        for (int j = 0; j < code[c][i].length(); j++) {
            lia[i] = mod(lia[i] + mod(code[c][i][j]*pta[i]));
            pta[i] = mod(pta[i]*B);
        }
    }

    for (int i = 0; i < lins[n]; i++) {
        ptb[i] = 1llu;
        lib[i] = 0;
        for (int j = 0; j < code[n][i].length(); j++) {
            lib[i] = mod(lib[i] + mod(code[n][i][j]*ptb[i]));
            ptb[i] = mod(ptb[i]*B);
        }
    }

    for (int i = 0; i < lins[c] - k; i++) {
        num p = 1llu;
        kla[i] = 0;
        for (int j = 0; j < k; j++) {
            kla[i] = mod(kla[i] + mod(p*lia[i+j]));
            p = mod(p*pta[i+j]);
        }
    }

    for (int i = 0; i < lins[n] - k; i++) {
        num p = 1llu;
        klb[i] = 0;
        for (int j = 0; j < k; j++) {
            klb[i] = mod(klb[i] + mod(p*lib[i+j]));
            p = mod(p*ptb[i+j]);
        }
    }

    sort(kla, kla+lins[c]-k);
    sort(klb, klb+lins[n]-k);

    int ia, ib;
    ia = ib = 0;

    while (ia < lins[c]-k && ib < lins[n]-k) {
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
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i <= n; i++) {
            lins[i] = 0;
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
                code[i][lins[i]++] = temp;
            }
        }

        maxi = 0;
        ss = 0;

        for (int i = 0; i < n; i++) {
            int lo = max(maxi-1, 0);
            int hi = min(lins[i], lins[n]);
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
