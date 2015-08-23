#include <cstdio>

using namespace std;

int main()
{
    int start, end, ans;
    scanf("%d %d", &start, &end);
    ans = end-start;
    if( ans < 0 )
        ans += 24;
    printf("O JOGO DUROU %d HORA(S)\n", ans);
}
