#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <list>

using namespace std;

// Definindo Tupla para marcação de vértice pai
  typedef struct Tupla{
     int vertice;
     int pai;
  } Tupla;

typedef struct Lista{
    int indice;
    Lista* prox;
    Lista* anterior;
} Lista;

class Vertice{
    public:
        Vertice();
        ~Vertice();
        
        int getGrau();
        int getPai();
        int getNivel();
        int getMarcacao();

        void incrementaGrau();
        void setPai(int v);
        void setNivel(int n);
        void desmarca();
        void marca(int i=1);
    protected:
    private:
        int grau;
        int marcacao;
        int pai;
        int nivel;
        
};

class Aresta{
    public:
        Aresta(int v1, int v2);
        ~Aresta();
        Vertice* getVertice(int v);
    protected:
    private:
        Vertice *v[2];
};

class MatrizAdjacencias{
    public:
        MatrizAdjacencias(int n);
        ~MatrizAdjacencias();
        MatrizAdjacencias(FILE* input);

        int getNVertices();
        int getNArestas();

        void setAdjacencia(int v1, int v2);

        void BFS(int origem);
        void DFS(int origem);

        void componentesConexos();

        Vertice **vertices;
    protected:
    private:
        int n_vertices;
        int n_arestas;
        int **adjacencias;
};

class ListaAdjacencias{
    public:
        ListaAdjacencias(int n);
        ~ListaAdjacencias();
        ListaAdjacencias(FILE *input);

        int getNVertices();
        int getNArestas();

        void setAdjacencia(int v1, int v2);

        void BFS(int origem);
        void DFS(int origem);

        void componentesConexos();
        
        Vertice **vertices;
    protected:
    private:
        int n_vertices;
        int n_arestas;
        list<int> **adjacencias;
};

#endif //GRAFO_H