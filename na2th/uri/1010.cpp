#include <cstdio>

using namespace std;

int main()
{
    int cod, quant;
    float price, total;
    scanf("%d %d %f", &cod, &quant, &price);
    total += price*quant;
    scanf("%d %d %f", &cod, &quant, &price);
    total += price*quant;
    printf("VALOR A PAGAR: R$ %.2f\n", total);
}
