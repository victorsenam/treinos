#include <cstdio>

using namespace std;

int main()
{
    char op;
    float matrix[12][12], ans;
    int line, i;
    scanf("%d %c", &line, &op);

    for (i = 0; i < 12*12; i++) 
        scanf("%f", &matrix[i/12][i%12]);

    ans = 0;
    for (i = 0; i < 12; i++) 
        ans += matrix[line][i];

    if(op == 'M') ans/=12;
    printf("%.1f\n", ans);
}
