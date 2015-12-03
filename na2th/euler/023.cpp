#include <bits/stdc++.h>
using namespace std;
typedef int num;
const int M = 28124;
int d, abd[M], as, tot;

int main()
{
    for(int i=1;i<M;i++)
    {
        d = 1;
        for(int j=2;j*j<=i;j++)
            if(i%j==0) d += j + (j!=i/j)*i/j;
        if(d > i)
            abd[as++] = i;
    }
    for(int i=1;i<M;i++)
    {
        int found = 0;
        for(int j=0;!found && j<as && abd[j] < i;j++)
            found |= binary_search(abd,abd+j+1,i-abd[j]);
        tot += (!found)*i;
    }
    printf("%d\n", tot);
}
