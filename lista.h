#ifndef LISTA_H
#define LISTA_H

using namespace std;

typedef struct ListNode
{
    ListNode *prev;
    int indice;
    ListNode *prox;
} ListNode;

class Lista
{
  public:
    Lista();
    ~Lista();

    ListNode *push(int i);
    void erase(ListNode *no);

    bool vazia();
    int getTamanho();

    ListNode *getInicio();
    ListNode *getFim();

  protected:
  private:
    int tamanho;
    ListNode *inicio;
    ListNode *fim;
};

#endif //LISTA_H