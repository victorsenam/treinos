#include <cstdio>
#include <map>

using namespace std;

int main()
{
    float input, payment, range;
    map<float, float>::iterator pos, ant;
    map<float, float> imposto;
    imposto[0] = 0;
    imposto[2000] = 0;
    imposto[3000] = 0.08;
    imposto[4500] = 0.18;

    scanf("%f", &input);
    payment = 0;

    pos = ant = imposto.begin();
    pos++;

    for( ; pos != imposto.end() ; pos++, ant++){
        range = pos->first -ant->first;
        if( input >= range )
        {
            input -= range;
            payment += range*pos->second;
        }else
        {
            payment += input*pos->second;
            input = 0;
            break;
        }

    }
    payment += input*0.28;
    printf("R$ %.2f\n", payment);
}
