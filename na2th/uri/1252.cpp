#include <cstdio>
#include <algorithm>

using namespace std;

class Compare
{
    int m;
    public:
    Compare(int a) : m(a) {}
    bool operator() (int a, int b)
    {
        if(a%m == b%m)
        {
            if(!(a&1u) && !(b&1u))
                return a < b;
            else if( (a&1u) && (b&1u) )
                return a > b;
            else
                return (a&1);
        }
        else
            return a%m < b%m;
    }
};;

int main()
{
    int m, n, numbers[10000], i;
    while ( scanf("%d %d", &n, &m) > 0 && ( m!=0 && n!=0 ) )
    {
        for( i = 0 ; i < n ; i++)
            scanf("%d ", numbers+i);

        sort(numbers, numbers+n, Compare(m));

        printf("%d %d\n", n, m);
        for( i = 0 ; i < n ; i++)
            printf("%d\n", numbers[i]);
    }printf("0 0\n");
}
