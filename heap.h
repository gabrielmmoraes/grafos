#ifndef HEAP_H
#define HEAP_H

using namespace std;

template <class T>
class Heap{
    public:
        Heap(int t_max, bool max);
        Heap(T *vetor, int t_vetor, int t_max, bool max);
        ~Heap();

        void swap(int i, int j);
    
        void insert(T novo_item);
        T getRoot();
        T extract();
        void change(int no, T novo_valor);

    protected:
    private:
        T* buffer;
        int ultimo;
        int tamanho_max;
        bool e_max_heap;
};

#include "heap_impl.h"
#endif //HEAP_H