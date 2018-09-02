#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <ctime>
#include <sys/time.h>
#include "grafo.h"

using namespace std;

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main(){

	const int LEITURAS = 10;

	int i;

    FILE* pFile;

    pFile = fopen("as_graph.txt", "r");

	long inicio, fim, acum = 0;

	double duracao;

	printf("Análise do grafo com Lista de Adjacência:\n\n");
	
	inicio = getMicrotime();

    MatrizAdjacencias matriz(pFile);
	matriz.~MatrizAdjacencias();

	fim = getMicrotime();

	duracao = (fim-inicio) / 1000;

	inicio = getMicrotime();

    ListaAdjacencias matriz2(pFile);
	matriz2.~ListaAdjacencias();

	fim = getMicrotime();

	duracao = (fim-inicio) / 1000;




	printf("Construindo Lista de Adjacência (%.0lf ms)\n\n", duracao);
    
	for(i = 0; i<LEITURAS; i++){
		printf("Executando BFS no vértice %d\n", i);
		inicio = getMicrotime();
		matriz.BFS(i);
		fim = getMicrotime();
		duracao = (fim - inicio) / 1000;
		printf("Executada BFS em %d (%.0lf ms)\n\n", i, duracao);
		acum += duracao;
	}

	duracao = (acum / LEITURAS);

	printf("Executando BFS em %d vértices distintos (%.0lf ms)\n", LEITURAS, duracao);

    
	for(i = 0; i<LEITURAS; i++){
		printf("Executando DFS no vértice %d\n", i);
		inicio = getMicrotime();
		matriz.DFS(i);
		fim = getMicrotime();
		duracao = (fim - inicio) / 1000;
		printf("Executada DFS em %d (%.0lf ms)\n\n", i, duracao);
		acum += duracao;
	}

	duracao = (acum / LEITURAS);

	printf("Executando DFS em %d vértices distintos (%.0lf ms)\n\n", LEITURAS, duracao);

	    
	for(i = 0; i<10; i++){
		printf("Executando CC\n");
		inicio = getMicrotime();
		matriz.componentesConexos();
		fim = getMicrotime();
		duracao = (fim - inicio) / 1000;
		printf("Executada CC em (%.0lf ms)\n\n", duracao);
		acum += duracao;
	}

	duracao = (acum / i+1);

	printf("Executando Componentes Conexas em %d vértices distintos (%.0lf ms)\n", LEITURAS, duracao);

    // Apresentação dos resultados
    //printf("Resultados:\n\tVértices: %u\n\tArestas: %u\n\tMediana: %.2f\n", lista.getNVertices(), lista.getNArestas(), lista.getGrauMediano());
}
