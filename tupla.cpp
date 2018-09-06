#include "tupla.h"

using namespace std;

Tupla::Tupla(){}

// Overload de construtor da Tupla
// Inicializa tupla com os dois parâmetros passados
Tupla::Tupla(int e1, int e2)
{
    elem1 = e1;
    elem2 = e2;
}

Tupla::~Tupla(){}

// Overload de operador criado para a Tupla poder ser usada no heap do STL
bool Tupla::operator>(Tupla t)
{
    return elem2 > t.elem2 ? elem2 : t.elem2;
}

// Overload de operador criado para a Tupla poder ser usada no heap do STL
bool Tupla::operator <(Tupla t)
{
    return elem2 < t.elem2 ? elem2 : t.elem2;
}