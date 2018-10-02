#include "heap.h"
#include "stdlib.h"
#include <stack>
#include <queue>

using namespace std;

template <class T>
Heap<T>::Heap(bool max){
    tamanho = 0;
    e_max_heap = max;
    raiz = NULL;
    ultimo = NULL;
}

template <class T>
Heap<T>::Heap(T *vetor, int t, bool max){
    No<T>* no;
    No<T>* fesq;
    No<T>* fdir; 
    tamanho = t;
    e_max_heap = max;

    raiz = (No<T>*) malloc(sizeof(No<T>));
    raiz->pai = NULL;
    raiz->chave = vetor[0];

    ultimo = (No<T>*) malloc(sizeof(No<T>));
    ultimo->esquerda = NULL;
    ultimo->direita = NULL;

    queue<No<T>* > Q;
    Q.push(raiz);

    int i = 0;
    while(!Q.empty()){
        no = Q.front();
        Q.pop();

        if(2*i+1<t){
            fesq = (No<T>*) malloc(sizeof(No<T>));
            fesq->pai = no;
            fesq->chave = vetor[2*i+1];
            no->esquerda = fesq;
            Q.push(fesq);
        } else{
            ultimo->pai = no;
            no->esquerda = ultimo;
        }

        if(2*i+2<t){
            fdir = (No<T>*) malloc(sizeof(No<T>));
            fdir->pai = no;
            fdir->chave = vetor[2*i+2];
            no->direita = fdir;
            Q.push(fdir);
        }else{
            ultimo->pai = no;
            no->direita = ultimo;
        } 

        i++;
    }
}

template <class T>
Heap<T>::~Heap(){
    No<T>* no;
    stack<No<T>* > S;
    S.push(raiz);

    while(!S.empty()){
        no = S.top();
        
        S.pop();
        if(no->direita) S.push(no->direita);

        if(no->esquerda) S.push(no->esquerda);
        
        free(no);
    }
}

template <class T>
void Heap<T>::insert(T novo_item){
    No<T>* no = (No<T>*) malloc(sizeof(No<T>));
    no->chave = novo_item;
    no->esquerda = NULL;
    no->direita = NULL;

    if(raiz == NULL){
        no->pai = NULL;
        raiz = no;
        raiz->esquerda = ultimo;
        ultimo->pai = raiz;
    }
    else{
        no->pai = ultimo->pai;
        if(no->pai->esquerda == ultimo){ 
            no->pai->esquerda = no;
            no->pai->direita = ultimo;
        }
        if(no->pai->direita == ultimo){
            no->pai->direita = no;
        }
    }
}

template <class T>
T Heap<T>::extract(){
    
}

template <class T>
void Heap<T>::max_heapfy(){}

template <class T>
void Heap<T>::min_heapfy(){}