#include <cstdio>
#include <vector>

#define MAX 151
#define LIMIT 10000

typedef unsigned int BigDig;
typedef std::vector<BigDig> BigInt;
BigInt memo[MAX];
char used[MAX];

void sumBigInt (BigInt * a, BigDig b, int house) {
    if (!b) return;
    while (a->size() <= house) a->push_back(0u);
    
    (*a)[house] += b;
    sumBigInt(a, (*a)[house]/LIMIT, house+1);
    (*a)[house] %= LIMIT;
}

void sumBigInt (BigInt * a, BigInt * b, int house) {
    for (BigInt::iterator it = b->begin(); it != b->end(); it++) {
        sumBigInt(a, *it, house++);
    }
}

void multBigInt (BigInt * a, BigDig b, BigInt * res) {
    int i = 0;

    res->clear();
    for (BigInt::iterator it = a->begin(); it != a->end(); it++) sumBigInt(res, (*it)*b, i++);
}

void multBigInt (BigInt * a, BigInt * b, BigInt * res) {
    int i = 0;
    BigInt aux;

    res->clear();
    for (BigInt::iterator it = b->begin(); it != b->end(); it++) {
        multBigInt(a, *it, &aux);
        sumBigInt(res, &aux, i++);
    }
}

void printBigInt (BigInt * a) {
    char ok = 0;
    for (BigInt::reverse_iterator it = a->rbegin(); it != a->rend(); it++) {
        if (ok) printf("%04u", *it);
        else if (*it > 0) {
            printf("%u", *it);
            ok = 1;
        }
    }
    if (!ok) printf("0");
}

void seq (int k) {
    if (used[k]) return;
    used[k] = 1;
    memo[k].clear();

    BigInt aux;
    
    for (int i = 0; i < k; i++) {
        seq(i);
        seq(k-i-1);

        multBigInt(&memo[i], &memo[k-i-1], &aux);
        sumBigInt(&memo[k], &aux, 0);
    }
}

int main () {
    int n;

    for (int i = 0; i < MAX; i++) used[i] = 0;
    used[0] = used[1] = 1;
    memo[0].push_back(1);
    memo[1].push_back(1);

    while (scanf("%u", &n) != EOF && n != -1) {
        seq(n);
        printBigInt(&memo[n]);
        printf("\n");
    }
}
