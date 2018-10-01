#include "tupla.h"

using namespace std;

template <class num1, class num2>
Tupla<num1, num2>::Tupla(){}

// Overload de construtor da Tupla
// Inicializa tupla com os dois parâmetros passados
template <class num1, class num2>
Tupla<num1, num2>::Tupla(num1 e1, num2 e2)
{
    elem1 = e1;
    elem2 = e2;
}

template <class num1, class num2>
Tupla<num1, num2>::~Tupla(){}

// Overload de operador criado para a Tupla poder ser usada no heap do STL
template <class num1, class num2>
bool Tupla<num1, num2>::operator>(Tupla t)
{
    return elem2 > t.elem2 ? elem2 : t.elem2;
}

// Overload de operador criado para a Tupla poder ser usada no heap do STL
template <class num1, class num2>
bool Tupla<num1, num2>::operator <(Tupla t)
{
    return elem2 < t.elem2 ? elem2 : t.elem2;
}
