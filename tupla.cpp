#include "tupla.h"

using namespace std;

template <class num>
Tupla<num>::Tupla(){}

// Overload de construtor da Tupla
// Inicializa tupla com os dois parâmetros passados
template <class num>
Tupla<num>::Tupla(int e1, num e2)
{
    elem1 = e1;
    elem2 = e2;
}

template <class num>
Tupla<num>::~Tupla(){}

// Overload de operador criado para a Tupla poder ser usada no heap do STL
template <class num>
bool Tupla<num>::operator>(Tupla t)
{
    return elem2 > t.elem2 ? elem2 : t.elem2;
}

// Overload de operador criado para a Tupla poder ser usada no heap do STL
template <class num>
bool Tupla<num>::operator <(Tupla t)
{
    return elem2 < t.elem2 ? elem2 : t.elem2;
}
