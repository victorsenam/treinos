#include <bits/stdc++.h>
using namespace std;

int n, v[10];
bool ok;
set<vector<int> > s;
vector<int> a;
int f;

void checa (bool v, int t){
    if (!v) printf("ERRÔ %d\n", t);
}

void printa () {
    for(int i = 0; i < n; i++) {
        if (ok) checa((i && v[i] == a[i-1]) || (i < n-1 && v[i] == a[i+1]) || (v[i] == a[i]), 0);
        printf("%d ",v[i]+1);
    }
    ok = 1;
    putchar('\n');
}

void troca (int i, int j) {
    a.clear();

    swap(v[i], v[j]);

    for (int k = 0; k < n; k++)
        a.push_back(v[k]);
    checa(s.find(a) == s.end(), 1);
    s.insert(a);
    swap(a[i], a[j]);

    printa();
    f--;
}

int main(){
    scanf("%d",&n);
    for(int i = 0; i < n; i++) v[i] = i;
    f = 1;
    for(int i = 1; i <= n; i++) f *= i;

    troca(0,0);

    for (int i = 0; i < n-1; i++) {
        for (int j = n-1; j > 0; j--)
            for (int k = 0; k < j; k++)
                troca(k, k+1);
        if (i < n-1)
            troca(n-2, n-1);
    }
    checa(!f, 2);
}

