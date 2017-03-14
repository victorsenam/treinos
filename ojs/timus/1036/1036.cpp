#include <bits/stdc++.h>

using namespace std;

#define N 51
#define S 1001
#define BASE 10000

vector<unsigned int> memo[N][S];
int n, s;

void sumBI (vector<unsigned int> * u, unsigned int v, int i) {
    if (!v) return;
    while (u->size() <= i) u->push_back(0u);

    (*u)[i] += v;
    sumBI(u, (*u)[i]/BASE, i+1);
    (*u)[i] %= BASE;
}

void sumB (vector<unsigned int> * u, vector<unsigned int> * v) {
    for (int i = 0; i < v->size(); i++) {
        sumBI(u, (*v)[i], i);
    }
}

// r += u*v*(BASE^i)
void multBI (vector<unsigned int> * r, vector<unsigned int> * u, unsigned int v, int i) {
    for (int j = 0; j < u->size(); j++) {
        sumBI(r, (*u)[j]*v, j+i);
    }
}

void multB (vector<unsigned int> * r, vector<unsigned int> * u, vector<unsigned int> * v) {
    for (int i = 0; i < v->size(); i++) {
            multBI(r, u, (*v)[i], i);
    }
}

void printB (vector<unsigned int> * u) {
    bool ok = 0;

    for (int i = u->size() - 1; i >= 0; i--) {
        if (ok) printf("%04u", (*u)[i]);
        else if ((*u)[i] > 0u) {
            printf("%u", (*u)[i]);
            ok = 1;
        }
    }
    if (!ok) printf("0");
    printf("\n");
}

void calc (int m, int v) {
    if (memo[m][v].size() > 0) return;

    if (!m) memo[m][v].push_back(0u);
    else if (!v) memo[m][v].push_back(1u);
    else if (m == 1) {
        if (v >= 10 || v < 0) memo[m][v].push_back(0u);
        else memo[m][v].push_back(1u);
    } else {
        memo[m][v].push_back(0u);
        for (int i = 0; i <= v; i++) {
            calc(m/2, i);
            calc(m/2+m%2, v-i);
            multB(&memo[m][v], &(memo[m/2][i]), &(memo[m/2+m%2][v-i]));
        }
    }
}

int main () {
    vector<unsigned int> res;
    unsigned int val;

/* Testando BIGINT
    vecotr<unsigned int> prodI, addI, prodB, addB;
    prodI.push_back(1u);
    prodB.push_back(1u);

    while (scanf("%d", &val) && val) {
        sumBI(&addI, val, 0);

        prodI.clear();
        multBI(&prodI, &addI, val, 0);

        sumB(&addB, &addI);

        prodB.clear();
        multB(&prodB, &prodI, &addI);

        printf("AddI: ");
        printB(&addI);
        printf("ProdI: ");
        printB(&prodI);
        printf("AddB: ");
        printB(&addB);
        printf("ProdB: ");
        printB(&prodB);
    }
*/

    scanf("%d %d", &n, &s);

    if (s%2) {
        printf("0\n");
    } else {
        calc(n, s/2);

        multB(&res, &memo[n][s/2], &memo[n][s/2]);
        printB(&res);
    }
}
