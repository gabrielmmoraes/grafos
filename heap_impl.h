#include "heap.h"
#include <stdlib.h>
#include <stdio.h>


using namespace std;

// Inicializa uma heap vazia de tamanho t_max.
// O valor booleano max determina se a heap é máxima ou mínima. Se true, heap máxima. 
template <class T>
Heap<T>::Heap(int t_max, bool max){    
    // Define o tamanho máximo da heap
    tamanho_max = t_max; 
    // Aloca a memória para a heap
    buffer = (T*) malloc(sizeof(T)*tamanho_max);
    // Define o índice referente ao final do heap ocupado, 0 para a heap vazia 
    ultimo = 0; 
    // Define o tipo de heap
    e_max_heap = max;
}

//Inicializa uma heap de tamanho t_max, a partir de um vetor de tamanho t_vetor
template <class T>
Heap<T>::Heap(T *vetor, int t_vetor, int t_max, bool max){
    // Define o tamanho máximo da heap
    tamanho_max = t_max;
    // Aloca a memória para a heap
    buffer = (T*) malloc(sizeof(T)*tamanho_max);
    // Define o índice referente ao final do heap ocupado, 0 para a heap vazia
    ultimo = 0;
    // Define o tipo de heap
    e_max_heap = max;

    //Neste ponto a heap está vazia

    //Insere todos os elementos do vetor na heap
    for(int i=0;i<t_vetor;i++){
        insert(vetor[i]);
    }
}

//Destrutor da heap
template <class T>
Heap<T>::~Heap(){
    //Libera a memória ocupada pela heap
    free(buffer);
}

//Retorna true sse a heap estiver vazia
template <class T>
bool Heap<T>::empty(){
    return ultimo<=0;
}

//Troca de posição os elementos indexados por i e j
template<class T>
void Heap<T>::swap(int i, int j){
    // Variável temporária com o valor de i
    T tmp = buffer[i];
    // Move o valor de j para posição i
    buffer[i] = buffer[j];
    // Move variável temporária (valor de i) para posição j
    buffer[j] = tmp;
}

//Insere um novo elemento à heap
template <class T>
void Heap<T>::insert(T novo_item){

    // Se a heap não está totalmente ocupada
    if(ultimo<tamanho_max){ 
        //Insere novo elemento no final da heap
        buffer[ultimo] = novo_item;
        //Incrementa o índice referente ao final ocupado
        ultimo++;
    }
    // Se a heap está totalmente ocupada
    else{ 
        // Informa e termina a função
        printf("A heap está cheia. Não é possível inserir.\n");
        return;
    }

    // Variáveis temporárias para reordenação da heap
    // no é o elemento inserido
    int no = ultimo-1;
    // pai é o seu pai na árvore da heap
    int pai;

    // Até o pai ser a raiz
    while(pai>=0){
        // Recalcula o índice do pai
        pai = (no-1)/2;
        // Se a heap é máxima
        if(e_max_heap){
            // Se o valor do no for maior que o valor do seu pai
            if(buffer[no] > buffer[pai]){
                // Troca o no com o pai
                swap(no, pai);
                // Redefine o no como sendo o pai
                no = pai;
            }
            // Se o no for menor que o pai, interrompe o loop
            else break;
        // Se a heap é máxima
        }else{
            // Se o valor do no for menor que o valor do seu pai
            if(buffer[no] < buffer[pai]){
                // Troca o no com o pai
                swap(no, pai);
                // Redefine o no como sendo o pai
                no = pai;
            } 
            // Se o no for maior que o pai, interrompe o loop
            else break;
        }
    }
}

// Retorna a raiz da heap
template <class T>
T Heap<T>::getRoot(){
    return buffer[0];
}

// Retorna e retira a raiz da heap
template <class T>
T Heap<T>::extract(){

    // Se a heap está vazia
    if(ultimo<=0){
        // Informa o usuário 
        printf("A heap está vazia.\n");
    }
    // Pega a raiz da heap
    T raiz = buffer[0];
    // Se a heap não está vazia
    if(ultimo>=0){
        // Passa o último elemento para a raiz
        buffer[0] = buffer[ultimo-1];
        // Decrementa o índicedo final da heap
        ultimo--;
    }

    // Define variáveis temporárias para reordenação da heap
    // no é o elemento que foi passado para a raiz
    int no = 0;
    // tmp é uma temporária para comparação
    int tmp;
    // filhos a esquerda e a direita do no
    int esquerda, direita;

    // Até o no estar no final da heap
    while(no<ultimo){
        tmp = no;
        // Redefine filhos 
        esquerda = 2*no+1;
        direita = 2*no+2;
        // Se a heap for máxima
        if(e_max_heap){
            // Se o filho a esquerda for maior que o o no 
            if(esquerda<ultimo && buffer[tmp] < buffer[esquerda]){
                // Define o filho a esquerda como o maior 
                tmp = esquerda;
            }
            // Se o filho a direita for maior que o maior
            if(direita<ultimo && buffer[tmp] < buffer[direita]){
                // Define o filho a direita como o maior
                tmp = direita;
            }
            // Se o no não for o maior 
            if(no!=tmp){
                // Troca o no com o maior 
                swap(no, tmp);
                // Redefine a posição do no
                no = tmp;
            }
            // Se o no for o maior, interrompe o loop
            else break;
        // Se a heap for mínima
        }else{
            // Se o filho a esquerda for menor que o no
            if(esquerda<ultimo && buffer[tmp] > buffer[esquerda]){
                // Define o filho a esquerda como o menor
                tmp = esquerda;
            }
            // Se o filho a direita for menor que o menor
            if(direita<ultimo && buffer[tmp] > buffer[direita]){
                // Define o filho a direita como o menor
                tmp = direita;
            }
            // Se o no não for o menor
            if(no!=tmp){
                // Troca o no com o menor
                swap(no, tmp);
                // Redefine a posição do no
                no = tmp;
            } 
            // Se o no for o menor, interrompe o loop
            else break;
        }
    } 

    // Retorna a raiz
    return raiz;
}

// Modifica o valor do no
// assumindo que o novo valor é menor que o anterior (heap mínima)
// ou maior que o anterior (heap máxima)
template <class T>
void Heap<T>::change(int no, T novo_valor){
    // Se a heap for máxima e o novo valor for menor ao anterior
    if(e_max_heap && novo_valor<buffer[no]){
        // Informa o usuário e termina a função
        printf("O novo valor deve ser maior que o anterior.\n");
        return;
    }

    // Se a heap for mínima e o novo valor for maior ao anterior
    if(!e_max_heap && novo_valor>buffer[no]){
        //Informa o usuário e termina a função
        printf("O novo valor deve ser menor que o anterior.\n");
        return;
    }

    // Atualiza o valor do no
    buffer[no] = novo_valor;
    
    // Variável temporária para reordenação
    int pai;

    // Até o no ser a raiz
    while(no>0){
        // Redefine o valor do pai
        pai = (no-1)/2;
        // Se a heap for máxima
        if(e_max_heap){
            // Se o valor do pai for menor que o valor do no
            if(buffer[pai] < buffer[no]){
                // Troca o pai com o no
                swap(no, pai);
                // Redefine a posição do no
                no = pai;
            }
            // Se o valor do pai for maior que o valor do no, interrompe o loop
            else break;
        // Se a heap for mínima
        }else{
            // Se o valor do pai for maior que o valor do no
            if(buffer[pai] > buffer[no]){
                // Troca o pai com o no
                swap(no,pai);
                // Redefine a posição do no
                no = pai;
            }
            // Se o valor do pai for menor que o valor do no, interrompe o loop
            else break;
        }
    }
}