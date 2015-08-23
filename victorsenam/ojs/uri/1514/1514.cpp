#include <cstdio>
#include <cstring>

int main()
{
    int columns[100], i, j, m, n, lineSum, aux, cond1, cond2, cond3, cond4;

    while(scanf("%d %d", &n, &m) != EOF && n != 0 && m != 0)
    {
        for(i = 0; i < 100 ; i++)
            columns[i] = 0;
        cond1 = cond2 = cond3 = cond4 = 1;
        for(i = 0; i < n; i++)
        {
            lineSum = 0;
            for(j = 0; j < m; j++)
            {
                scanf("%d", &aux);
                lineSum += aux;
                columns[j] += aux;
            }
            cond1 &= (lineSum < m);
            cond4 &= (lineSum > 0);
        }
        for(i = 0; i < m; i++)
        {
            cond2 &= (columns[i] > 0);
            cond3 &= (columns[i] < n);
        }
        printf("%d\n", cond1 + cond2 + cond3 + cond4);
    }
}
