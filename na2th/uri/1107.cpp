#include <cstdio>

using namespace std;

int caso(int alt, int comp){
    int i, n = 0, anterior = alt, atual;
    for (i = 0; i < comp; i++) {
        scanf("%d", &atual);
        if (atual < anterior) n = n + anterior - atual;
        anterior = atual;
    }
    return n;
}

int main(){
    int A, C, R;
    while(scanf("%d %d", &A, &C) && (A != 0 && C != 0)) {
        R = caso(A, C);
        printf("%d\n", R);
    }
    return 0;
}
