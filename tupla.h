#ifndef TUPLA_H
#define TUPLA_H

using namespace std;

// Definindo Tupla para marcação de vértice pai
template <class num>
  class Tupla{
      public:
        Tupla();
        Tupla(int e1, num e2);
        ~Tupla();

        bool operator >(Tupla t);
        bool operator <(Tupla t);
        int elem1;
        num elem2;
  };

  #endif //TUPLA_H
