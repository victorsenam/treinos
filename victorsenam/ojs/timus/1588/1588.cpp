#include <bits/stdc++.h>

using namespace std;

const int N = 10007;

int x[N], y[N];
int pa[N], pl[N];
double res;
int n;
int anc;

inline int cross (int i, int j) {
    return (x[i]*y[j] - x[j]*y[i]);
}

inline int inner (int i, int j)
{ return (y[i]-y[j])*(y[i]-y[j]) + (x[i]-x[j])*(x[i]-x[j]); }

bool cmp_ang (int i, int j)
{ return cross(i,anc) < cross(j,anc); }

bool cmp_lex (int i, int j) {
    if (x[i] == x[j])
        return y[i] < y[j];
    return x[i] < x[j];
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d %d", x+i, y+i);

    sort(pl, pl+n, cmp_lex);

    for (int i = 0; i < n; i++) {
        anc = i;

        sort(pa+1, pa+n, cmp_ang);
        for (int j = 0; j < n; j++) {
            
        }
    }
}
