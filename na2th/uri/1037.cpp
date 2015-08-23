#include <cstdio>
#include <algorithm>

using namespace std;

int main(){
    float limits[5] = {0,25,50,75,100},
          input, * pos;
    scanf("%f", &input);
    if( input > 100.0 || input < 0 ){
        printf("Fora de intervalo\n");
        return 0;
    }
    pos = lower_bound(limits, limits+5, input);
    printf("%d\n", index);
    if( *pos == 0 )/* fix for 0 */
        pos += 1;
    if( *pos == 25 )/* fix fist interval [ */
        printf("Intervalo [");
    else
        printf("Intervalo (");
    printf("%.0f,%.0f]\n", *(pos -1) , *pos);
}
