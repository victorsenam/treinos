#include <cstdio>

using namespace std;

void maxPos(int * a, int* b){
    int temp;
    if( *a < 0 )
        *a *= -1;
    if( *b < 0 )
        *b *= -1;
    if(*b > *a){
        temp = *a;
        *a = *b;
        *b = temp;
    }
}

int gcd(int a, int b){
    maxPos(&a, &b);
    int * restos = new int [a];
    int t, temp;
    t = 0;
    restos[t++] = a;
    restos[t++] = b;
    while( (temp = restos[t-2]%restos[t-1]) != 0 )
        restos[t++] = temp;
    return restos[--t];
}

int main()
{
    int exp, n1,n2,d1,d2, na, da, d;
    char op;
    scanf("%d ", &exp);

    for (; exp > 0 ; exp--) {
        scanf("%d /%d %c %d /%d ", &n1,&d1,&op,&n2,&d2);    
        switch(op){
            case '*':
                na = n1*n2;
                da = d1*d2;
                break;
            case '/':
                na = n1*d2;
                da = d1*n2;
                break;
            case '+':
                na = (n1*d2 + n2*d1);
                da = d1*d2;
                break;
            case '-':
                na = (n1*d2 - n2*d1);
                da = d1*d2;
                break;
        }
        if(da < 0){
            na *= -1;
            da *= -1;
        }
        printf("%d/%d = ", na, da);
        d = gcd(na,da);
        printf("%d/%d\n", na/d, da/d);
    }
}
