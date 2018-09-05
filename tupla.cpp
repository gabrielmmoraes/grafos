#include "tupla.h"

using namespace std;

Tupla::Tupla(){}

Tupla::Tupla(int e1, int e2){
    elem1 = e1;
    elem2 = e2;
}

Tupla::~Tupla(){}

bool Tupla::operator>(Tupla t){
    return elem2 > t.elem2 ? elem2 : t.elem2;
}

bool Tupla::operator <(Tupla t){
    return elem2 < t.elem2 ? elem2 : t.elem2;
}
