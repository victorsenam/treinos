#include <cstring>
#include <cstdio>

using namespace std;

int main(){
    int n, i, leds;
    char input[100];
    scanf("%d ", &n);
    for(; n > 0 ; n--){
        leds = 0;
        memset(input, 0, 100);
        scanf("%s ", input);
        for( i = 0 ; i < 100 && input[i] != 0 ; i++ ){
            switch(input[i]){
                case '1':
                    leds += 2;
                    break;
                case '7':
                    leds += 3;
                    break;
                case '4':
                    leds += 4;
                    break;
                case '2':
                case '3':
                case '5':
                    leds += 5;
                    break;
                case '6':
                case '9':
                case '0':
                    leds += 6;
                    break;
                case '8':
                    leds += 7;
                    break;
            }
        }
        printf("%d leds\n", leds);
    }
}
