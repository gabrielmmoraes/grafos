#include "lista.h"
#include <stdlib.h>

using namespace std;

// Inicializa lista vazia
Lista::Lista()
{
    inicio = NULL;
    fim = NULL;
    tamanho = 0;
}

// Libera memória usada pela lista
Lista::~Lista()
{
    ListNode *no = inicio;
    if(inicio){
        while (inicio->prox != NULL)
        {
            no = inicio;
            inicio = inicio->prox;
            free(no);
        }
        free(inicio);
    }
}

ListNode *Lista::push(int i)
{
    ListNode *no = (ListNode *)malloc(sizeof(ListNode));
    no->indice = i;
    no->prox = NULL;
    if (inicio == NULL)
    {
        no->prev = NULL;
        inicio = no;
    }
    else
    {
        no->prev = fim;
        fim->prox = no;
    }
    fim = no;
    tamanho++;

    return no;
}

void Lista::erase(ListNode *no)
{
    if (no==inicio && no==fim)
    {
        inicio = NULL;
        fim = NULL;
        tamanho--;
        free(no);
        return;
    }
    
    if (no==inicio)
    {
        inicio = no->prox;
        no->prox->prev == NULL;
        tamanho--;
        free(no);
        return;
    }
    if (no==fim)
    {
        fim = no->prev;
        no->prev->prox == NULL;
        tamanho--;
        free(no);
        return;
    }
    no->prev->prox = no->prox;
    no->prox->prev = no->prev;
    tamanho--;
    free(no);
}

// Se o ponteiro de início estiver em NULL, a lista está vazia
bool Lista::vazia()
{
    return inicio == NULL;
}

// Retorna tamanho da lista
int Lista::getTamanho(){
    return tamanho;
}

// Retorna ponteiro para o início da lista
ListNode *Lista::getInicio()
{
    return inicio;
}

// Retorna ponteiro para o fim da lista
ListNode *Lista::getFim()
{
    return fim;
}