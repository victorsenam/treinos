#include <cstdio>
#include <cstring>

using namespace std;

int main(){
    char digit, input[100], output[100];
    bool onlyzero;
    int i,o;
    while( scanf("%c %100s ", &digit, &input) > 0  && input[0] != '0' ){
        o = 0;
        onlyzero = true;
        memset(output, 0, 100);
        for(i = 0; i < 100 && input[i] != '\0'; i++ )
            if(input[i] != digit){
                if(onlyzero && input[i] != '0')
                    onlyzero = false;
                if(not onlyzero)
                    output[o++] = input[i];
            }
        if(onlyzero)
            output[o++] = '0';

        printf("%s\n", output);
        memset(input, 0, 100);
    }
}
