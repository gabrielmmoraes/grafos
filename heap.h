#ifndef HEAP_H
#define HEAP_H

using namespace std;

class Heap{
    public:
        Heap(int t_max, bool max);
        Heap(Tupla<int,float>** vetor, int t_vetor, int t_max, bool max);
        ~Heap();

        bool empty();

        void swap(int i, int j);
    
        void insert(Tupla<int,float>* novo_item);
        Tupla<int,float>* getRoot();
        Tupla<int,float>* extract();
        void change(int no, float novo_valor);
        int getIndex(Tupla<int,float>* tupla);

        Tupla<int,float>** buffer;
        int* buffer_index;
        int ultimo;

    protected:
    private:
        int tamanho_max;
        bool e_max_heap;
};

#include "heap_impl.h"
#endif //HEAP_H