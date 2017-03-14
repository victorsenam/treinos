#include <cstdio>

unsigned long int database[2][40];

unsigned long int fibonacci (int n, int * p) {
    if ( database[0][n] || !n ) {
        *p += database[1][n] + 1;
        return database[0][n];
    }

    database[0][n] = fibonacci(n-2, p) + fibonacci(n-1, p);
    database[1][n] = *p;
    return database[0][n];
}

int main () {
    int N, n, p;

    database[0][0] = database[1][0] = database[1][1] = 0;
    database[0][1] = 1;
    for (n = 2; n < 40; n++) {
        database[0][n] = 0;
    }

    scanf("%d", &N);
    while ( N > 0 ) {
        scanf("%d", &n);
     
        p = 0;
        printf("%lu ", fibonacci(n, &p));
        printf("%d\n", database[1][n]);

        N--;
    }
}
