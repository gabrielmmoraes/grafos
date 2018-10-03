#ifndef TUPLA_H
#define TUPLA_H

using namespace std;

// Definindo Tupla para marcação de vértice pai
template <class num1, class num2>
  class Tupla {
      public:
        Tupla();
        Tupla(num1 e1, num2 e2);
        ~Tupla();

        bool operator >(Tupla t);
        bool operator <(Tupla t);

        num1 elem1;
        num2 elem2;
  };

#include "tupla_impl.h"
#endif //TUPLA_H
