#ifndef LISTA_H
#define LISTA_H

#include "tupla.h"

using namespace std;

typedef struct ListNode{
    ListNode* prev;
    Tupla<int, float> elemento;
    ListNode* prox;
} ListNode;

class Lista{
    public:
        Lista();
        ~Lista();

        ListNode* push(int i, float w=0);
        void erase(ListNode* no);

        bool vazia();
        int getTamanho();

        ListNode* getInicio();
        ListNode* getFim();
    protected:
    private:
        int tamanho;
        ListNode* inicio;
        ListNode* fim;
};

#endif //LISTA_H