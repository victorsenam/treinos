#include <cstdio>
#include <vector>

#define LIMIT 10000
#define PRINT_N "%u"
#define PRINT_T "%04u"


typedef unsigned int BigDigit;
typedef std::vector<BigDigit> BigInt;

void printBigInt(BigInt* bi) {
    char ok = 0;

    for (BigInt::reverse_iterator it = bi->rbegin(); it != bi->rend(); it++) {
        if (ok) printf(PRINT_T, *it);
        else if (*it > 0) {
            printf(PRINT_N, *it);
            ok = 1;
        }
    }
    if (!ok) printf("0");
    printf("\n");
}

void sumBigInt(BigInt* a, BigDigit b, int house) {
    BigDigit carry;

    if (b == 0) return;
    while (a->size() <= house) a->push_back(0);

    (*a)[house] += b;
    carry = (*a)[house]/LIMIT;
    (*a)[house] %= LIMIT;

    sumBigInt(a, carry, house+1);
}

void sumBigInt(BigInt* a, BigInt* b, int house) {
    for (BigInt::iterator it = b->begin(); it != b->end(); it++) {
        sumBigInt(a, *it, house++);
    }
}

void multBigInt(BigInt* a, BigDigit b, BigInt* res) {
    int i = 0;
    res->clear();
    
    for (BigInt::iterator it = a->begin(); it != a->end(); it++) {
        sumBigInt(res, (*it)*b, i++);
    }
}

void multBigInt(BigInt* a, BigInt* b, BigInt* res) {
    BigInt aux;
    int i = 0;
    res->clear();
    
    for (BigInt::iterator it = b->begin(); it != b->end(); it++) {
        multBigInt(a, *it, &aux);
        sumBigInt(res, &aux, i++);
    }
}

int main () {
    BigInt n, a, b, aux;
    BigDigit c, v1, v2;
    
    while (scanf(PRINT_N, &c) != EOF && c) {
        if (c == 1) {
            n.clear();
        } else if (c == 2) {        // Passa n pra a
            a.clear();
            sumBigInt(&a, &n, 0);
        } else if (c == 3) {        // Passa n pra b
            b.clear();
            sumBigInt(&b, &n, 0);
        } if (c == 10) {            // Soma
            scanf(PRINT_N, &v1);
            scanf(PRINT_N, &v2);
            sumBigInt(&n, v1, v2);
        } else if (c == 11) {       // Multiplicaçao
            scanf(PRINT_N, &v1);
            multBigInt(&n, v1, &aux);
            n.clear();
            sumBigInt(&n, &aux, 0);
        } else if (c == 21) {       // Acrescenta a em n
            sumBigInt(&n, &a, 0);
        } else if (c == 22) {       // Acrescenta b em n
            sumBigInt(&n, &b, 0);
        } else if (c == 23) {       // Multiplica b em a
            multBigInt(&a, &b, &aux);
            a.clear();
            sumBigInt(&a, &aux, 0);
        }
        
        printBigInt(&n);
    }
}
