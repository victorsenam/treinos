#include <iostream>

using namespace std;

int main()
{
    int shour = 0,
        ehour = 0,
        smin = 0,
        emin = 0,
        min,
        hour;

    cin >> shour;
    cin >> smin;
    cin >> ehour;
    cin >> emin;

    hour = (ehour-shour)%24;
    min = (emin-smin)%60;

    if( hour == 0 )
        emin > smin ? hour = 0 : hour = 24 ;
    else if( hour < 0 )
        hour = 24 + hour;

    if( min < 0 )
    {
        min = 60 + min;
        hour--;
    }
    cout << "O JOGO DUROU " << hour  <<" HORA(S) E " << min << " MINUTO(S)" << endl;
}
