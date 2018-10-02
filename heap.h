#ifndef HEAP_H
#define HEAP_H

using namespace std;

template<class T>
struct No{
    No* pai;
    T chave;
    No* esquerda;
    No* direita;
};

template <class T>
class Heap{
    public:
        Heap(bool max);
        Heap(T *vetor, int t, bool max);
        ~Heap();

        void insert(T novo_item);
        T extract();

        void max_heapfy();
        void min_heapfy();

        No<T>* raiz;
        No<T>* ultimo;


    protected:
    private:
        int tamanho;
        bool e_max_heap;
};

#include "heap_impl.h"
#endif //HEAP_H