#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

long long int permutacoes;

void trocar(uint8_t* arr, uint8_t i, uint8_t j){
    arr[i] ^= arr[j];
    arr[j] ^= arr[i];
    arr[i] ^= arr[j];
}

void imprimir(uint8_t* arr, uint8_t n){
    int i = 0;
 
    printf("Permutação encontrada: ");
 
    for (i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
 
    printf("\n");
}

void permutar(uint8_t* arr, uint8_t inicio, uint8_t fim){

    if (inicio == fim){
        imprimir(arr, fim+1);
        return;
    }
    
    permutar(arr, inicio+1, fim);
    
    uint8_t i;
    for (i = inicio; i <= fim; i++){
        if(arr[inicio] == arr[i]) continue;
        trocar(arr, inicio, i);
        permutar(arr, inicio+1, fim);
        trocar(arr, inicio, i);
    }
}

int main(int argc, char* argv[]){
    uint8_t n;

    if (argc != 2){
      printf("Execute o programa com apenas um argumento, especificando o N (Exemplo: ./permutacao 2)\n");
      exit(0);
    }

    n = atoi(argv[1]);

    uint8_t i = 0;
    uint8_t arr[n];
    
    for (i = 0; i < n; i++){
        arr[i] = i+1;
    }
    
    permutar (&arr, 0, n-1);

    return 0;
}

//VC FEDE GABRIEL MONDES, EU TE ODEIO 
//EU CHOREI A NOITE TODA PQ E NAO CONSIGO FAZR ESSA MERDA E VC FICA ME GASTANDO 
//EU RECLAMANDO E VC FAZENDO MEME COM A MINHA CARA
//FICAR FORA DO GRUPO FOI POUCO
//VC N MERECE A MINHA AMIZADE 
//E EU AINDA TENHO Q FAZER ISSO HJ A NOITE E N VOU CONSEGUIR PQ SOU UM INUTIL FEDIDO 

