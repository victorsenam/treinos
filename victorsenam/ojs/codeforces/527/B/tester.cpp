#include <cstdio>
int main() {
    printf("200000\n");
    for (int i = 0; i < 100000; i++) printf("a");
    for (int i = 0; i < 100000; i++) printf("b");
    printf("\n");
    for (int i = 0; i < 100000; i++) printf("b");
    for (int i = 0; i < 100000; i++) printf("a");

}


