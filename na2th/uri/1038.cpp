#include <cstdio>

using namespace std;

int main(int argc, const char *argv[])
{
    float prices[5] = {4.00, 4.50 , 5.00, 2.00, 1.50},
          price;
    int product, quantity;
    scanf("%d %d", &product, &quantity);
    price = quantity*(prices[product-1]);
    printf("Total: R$ %.2f\n", price);
}
