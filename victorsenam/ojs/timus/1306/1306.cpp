#include <bits/stdc++.h>

using namespace std;

const int N = 250000/2 + 7;

int v[N];
int siz;
int n;

void swimUp (int i) {
    if (i == 1)
        return;

    if (v[i] > v[i/2]) {
        swap(v[i], v[i/2]);
        swimUp(i/2);
    }
}

void sink (int i) {
    if (2*i > siz+1)
        return;
    if (2*i+1 > siz+1)
        v[2*i+1] = -1;
    
    if (v[i] > v[2*i] && v[i] > v[2*i+1])
        return;
    if (v[2*i] >= v[2*i+1]) {
        swap(v[i], v[2*i]);
        sink(2*i);
    } else {
        swap(v[i], v[2*i+1]);
        sink(2*i+1);
    }
}



int main () {
    scanf("%d", &n);
    siz = n/2 + 1;
    v[siz+1] = -1;
    int aux;

    for (int i = 0; i < n; i++) {
        if (i >= siz) {
            scanf("%d", &aux);
            if (aux < v[1]) {
                v[1] = aux;
                sink(1);
            }
        } else {
            scanf("%d", v+i+1);
            swimUp(i+1);
        }
    }
    
    if (n%2) {
        printf("%.1lf\n", (double)v[1]);
    } else {
        printf("%.1lf\n", ((double)v[1]+(double)max(v[2], v[3]))/2.0);
    }
}
