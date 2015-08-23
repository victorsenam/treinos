#include <cstdio>

using namespace std;

int abs(int a, int b)
{
    if(a < b)
        return b-a;
    else
        return a-b;
}

int main()
{
    int a,b,c;
    scanf("%d %d %d", &a, &b, &c);
    
    a = 0.5*(a+b+abs(a,b));
    c = 0.5*(a+c+abs(a,c));

    printf("%d eh o maior\n", c);
}
