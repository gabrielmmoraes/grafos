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

	const int LEITURAS = 1000;

	int i;

    FILE* pFileIn;
	
	FILE* pFileOut;

    pFileIn = fopen("as_graph.txt", "r");
	pFileOut = fopen("resultados_as_graph_matriz.txt", "a");

	long inicio, fim, acum_bfs = 0, acum_dfs = 0;

	double duracao;

	fprintf(pFileOut, "Análise do grafo com Matriz de Adjacência:\n\n");
	
	inicio = getMicrotime();

    MatrizAdjacencias grafo(pFileIn);

	fim = getMicrotime();

	duracao = (fim-inicio) / 1000;

	fprintf(pFileOut, "Construindo Matriz de Adjacência (%.0lf ms)\n\n", duracao);
    
	for(i = 0; i<LEITURAS; i++){
		inicio = getMicrotime();
		grafo.BFS(i);
		fim = getMicrotime();
		duracao = (fim - inicio) / 1000;
		acum_bfs += duracao;

		inicio = getMicrotime();
		grafo.DFS(i);
		fim = getMicrotime();
		duracao = (fim - inicio) / 1000;
		acum_dfs += duracao;
	}

	fprintf(pFileOut, "Tempo Médio (%d observações):\n\tBFS: %ld ms\n\tDFS: %ld ms\n\n",LEITURAS, acum_bfs/LEITURAS, acum_dfs/LEITURAS);

	for(int i=0;i<5;i++){
		grafo.BFS(i);
		fprintf(pFileOut, "BFS a partir de %d:\n",i+1);
		for(int j = 9;j<50;j+=10){
			fprintf(pFileOut, "O pai de %d é %d\n",j+1,grafo.getVertices()[j]->getPai()+1);
		}
		grafo.DFS(i);
		fprintf(pFileOut, "\nDFS a partir de %d:\n",i+1);
		for(int j = 9;j<50;j+=10){
			fprintf(pFileOut, "O pai de %d é %d\n",j+1,grafo.getVertices()[j]->getPai()+1);
		}
		fprintf(pFileOut, "\n");
	}

	Lista** componentes = grafo.analiseComponentesConexos();
	int quantidade = grafo.componentesConexos().size();
	int maior = componentes[0]->getTamanho();
	int menor = componentes[quantidade-1]->getTamanho();
	fprintf(pFileOut, "O grafo possui %d componentes conexas.\n A maior tem tamanho %d.\n A menor tem tamanho %d.\n\n",quantidade,maior,menor);

	fprintf(pFileOut, "Número de vértices: %d\nNúmero de Arestas: %d\nGrau mínimo: %d\nGrau máximo: %d\nGrau médio: %.2f\nMediana do grau: %.2f\n\n", grafo.getNVertices(), grafo.getNArestas(), grafo.getGrauMin(),grafo.getGrauMax(),grafo.getGrauMedio(),grafo.getGrauMediano(	));
}
