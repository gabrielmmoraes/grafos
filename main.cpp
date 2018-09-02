#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include "grafo.h"

int main(){

	/* Lista l;

	for(int i=0;i<10;i++){
		l.push(i);
		printf("Tamanho %d: %d\n", i, l.getTamanho());
	}
	printf("\n");

	ListNode* p = l.getInicio();
	while(p){
		printf("Lista: %d\n",p->indice);
		p = p->prox;
	}
	printf("Tamanho: %d\n\n", l.getTamanho());

	p = l.getInicio();
	while(p){
		l.erase(p);
		printf("Apagando: %d\n", p->indice);
		//printf("Inicio: %d\n", l.getInicio()->indice);
		p = p->prox;
		printf("Tamanho: %d\n", l.getTamanho());
	}
	printf("\n");
	p = l.getInicio();
	printf("%p\n",p);
    while(p){
		printf("Lista: %d\n",p->indice);
		p = p->prox;
	} */
    FILE* pFile;

    pFile = fopen("grafo_teste.txt", "r");

    MatrizAdjacencias lista(pFile);

    //int oi = lista.componentesConexos();
	lista.DFS(0);

     for(int i=0; i<lista.getNVertices(); i++){
        printf("Pai do vertice %d é %d\n", i+1, lista.getVertices()[i]->getPai()+1);
    }  

    // Apresentação dos resultados
    //printf("Resultados:\n\tVértices: %u\n\tArestas: %u\n\tCC: %d\n", lista.getNVertices(), lista.getNArestas(), oi);
}
