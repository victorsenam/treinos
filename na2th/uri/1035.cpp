#include <cstdio>

using namespace std;

int main(){
    int a,b,c,d;
    bool select = true;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    select &= (a%2 == 0);
    select &= (c + d > a+ b);
    select &= (d > a);
    select &= (b > c);
    if(select)
        printf("Valores aceitos\n");
    else
        printf("Valores nao aceitos\n");
}
