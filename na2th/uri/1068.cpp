#include <cstdio>
#include <cstring>

using namespace std;

int main(int argc, const char *argv[])
{
    char input[1000];
    int open = 0, n;
    memset(input, 0, 1000);
    while( scanf("%[^\n]%*.c", input) > 0 ){
        for (n = 0; n < 1000 && input[n] != 0; n++) {
            if(input[n] == '(')
                open++;
            else if(input[n] == ')')
                open--;

            if(open < 0) break;
        }

        if(open == 0)
            printf("correct\n");
        else
            printf("incorrect\n");
        memset(input, 0, 1000);
        open = 0;
    }
    return 0;
}
