#include <bits/stdc++.h>

using namespace std;

#define MAX 100000

vector<int> posi;
vector<int>::iterator it, jt;
int n, l, mini, aux;

int main () {
    while (scanf("%d %d", &n, &l) != EOF && n && l) {
        posi.clear();

        for (int i = 0; i < l; i++) {
            scanf("%d", &aux);
            posi.push_back(aux);
        }

        mini = n;
        for (it = posi.begin(); it < posi.end(); it++) {
            jt = lower_bound(posi.begin(), posi.end()-1, (*it)+n-1);
            if (*jt > *it+n-1) jt--;
            aux = n-(jt-it)-1; 
            if (mini > aux) mini = aux;
            // printf("[%d,%d(%d)] %d\n", *it, (*it)+n-1, *jt, aux);
        }

        printf("%d\n", mini);
    }
}
