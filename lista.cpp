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
    // Define ponteiro para o início da lista
    ListNode *no = inicio;

    // Se o início não for NULL, ou seja, se a lista não estiver vazia
    if(inicio)
    {
        // Loop que percorre a lista até o último elemento
        while (inicio->prox != NULL)
        {
            // Atribui elemento do início da lista ao nó
            no = inicio;

            // Novo início da lista é o próximo elemento
            inicio = inicio->prox;

            // Deleta nó
            free(no);
        }

        // Deleta último elemento da lista
        free(inicio);
    }
}


// Função que adiciona elemento ao final da lista encadeada
ListNode *Lista::push(int i, float w)
{
    // Aloca memória para o nó a ser adicionado
    ListNode *no = (ListNode *)malloc(sizeof(ListNode));

    // Inicializa o nó com o índice e o peso passados como argumentos
    no->elemento.elem1 = i;
    no->elemento.elem2 = w;

    // Define próximo elemento da lista como NULL
    // pois o elemento a ser adicionado será o último
    no->prox = NULL;

    // Se a lista estiver inicialmente vazia
    if (inicio == NULL)
    {
        // O elemento anterior o que será adicionado é NULL
        no->prev = NULL;

        // O ponteiro de inicio da lista passa a apontar para o nó
        inicio = no;
    }

    // Caso a lista não esteja inicialmente vazia
    else
    {
        // O elemento anterior ao nó é o atual elemento final da lista
        no->prev = fim;

        // O elemento próximo ao final da lista passa a ser o nó adicionado
        fim->prox = no;
    }
    
    // Define novo final da lista como o nó criado
    fim = no;
    
    // Incrementa tamanho da lista
    tamanho++;

    // Retorna ponteiro para o nó criado
    return no;
}

// Função que deleta o elemento da lista apontado pelo parâmetro
void Lista::erase(ListNode *no)
{
    // Se o elemento a ser deleta for o último da lista
    if (no==inicio && no==fim)
    {
        // Definimos início e fim da lista como NULL
        inicio = NULL;
        fim = NULL;

        // Decrementa tamanho
        tamanho--;

        // Libera memória usada pelo elemento deletado
        free(no);

        // Finaliza a execução da função
        return;
    }
    
    // Se o nó for o primeiro da lista
    if (no==inicio)
    {
        // Aponta o ponteiro inicio para o elemento posterior ao que será deletado
        inicio = no->prox;

        // Aponta o ponteiro prev do nó posterior para NULL
        // pois ele passa a ser o primeiro elemento
        no->prox->prev == NULL;

        // Decrementa tamanho
        tamanho--;

        // Libera memória usada pelo elemento deletado
        free(no);

        // Finaliza a execução da função
        return;
    }

    // Se o nó for o último da lista
    if (no==fim)
    {
        // Aponta o ponteiro fim para o elemento anterior ao que será deletado
        fim = no->prev;

        // Aponta o ponteiro prox do nó anterior para NULL
        // pois ele passa a ser o último elemento
        no->prev->prox == NULL;
        
        // Decrementa tamanho        
        tamanho--;

        // Libera memória usada pelo elemento deletado
        free(no);

        // Finaliza a execução da função
        return;
    }
    
    // Redefine ponteiros dos nós anterior e próximo
    no->prev->prox = no->prox;    
    no->prox->prev = no->prev;

    // Decrementa tamanho
    tamanho--;

    // Libera memória usada pelo elemento deletado
    free(no);
}

// Se o ponteiro de início estiver em NULL, a lista está vazia
bool Lista::vazia()
{
    return inicio == NULL;
}

// Retorna tamanho da lista
int Lista::getTamanho()
{
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