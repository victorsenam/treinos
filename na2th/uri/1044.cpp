#include <cstdio>

using namespace std;

void max(int &a, int &b)
{
    if( b > a ){
        int temp = a;
        a = b;
        b = temp;
    }
}

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    max(a,b);   
    if( a%b == 0 )
        printf("Sao Multiplos\n");
    else
        printf("Nao sao Multiplos\n");
}
