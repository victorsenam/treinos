#define SIZE 12
#include <cstdio>
#include <iostream>

using namespace std;

int main(){
    float M[SIZE][SIZE], ans;
    char op;
    int counter;

    cin >> op;
    ans = 0;

    for( counter = 0 ; counter < SIZE*SIZE ; counter++ )
        cin >> M[counter/SIZE][counter%SIZE];

    for( counter = 0 ; counter < SIZE*SIZE ; counter++ )
        if( (counter/SIZE > counter%SIZE) && (counter/SIZE + counter%SIZE < SIZE-1) ){
            ans +=M[counter/SIZE][counter%SIZE];
        }

    if( op == 'M' ) ans /= 66;

    printf("%.1f\n", ans);
}
