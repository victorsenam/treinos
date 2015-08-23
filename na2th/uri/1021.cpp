#include <cstdio>

using namespace std;

int main()
{
    int big,small,cents, money[12] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 25, 10, 5, 1}, n;

    scanf("%d.%d", &big, &small);
    cents = 100*big + small;

    printf("NOTAS:\n");
    for( n = 0 ; n < 6 ; n++)
    {
        printf("%d nota(s) de R$ %.2f\n", cents/money[n], (float)money[n]/100 );
        cents %= money[n];
    }
    printf("MOEDAS:\n");
    for( n = 6 ; n < 12 ; n++)
    {
        printf("%d moeda(s) de R$ %.2f\n", cents/money[n], (float)money[n]/100 );
        cents %= money[n];
    }
}
