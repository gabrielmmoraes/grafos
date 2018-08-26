#ifndef GRAFO_H
#define GRAFO_H

#include <list>
#include <fstream.h>

using namespace std;

class Vertice{
    public:
        Vertice(unsigned int indice);
        
        int getIndice();
        int getPai();
        int getNivel();

        void setPai(int v);
        void setNivel(int n);
    protected:
    private:
        int indice;
        int descoberto;
        int explorado;
        int pai;
        int nivel;
        
}

class Aresta{
    public:
        Aresta(int v1, int v2);
        Vertice getVertice(int v);
    protected:
    private:
        Vertice v1;
        Vertice v2;
}

class MatrizAdjacencias{
    public:
        MatrizAdjacencias();
        MatrizAdjacencias(ofstream *input);

        void setAdjacencia(int v1, int v2);

        void BFS(int origem);
        void DFS(int origem);

        void componentesConexos();

    protected:
    private:
        int *vertices;
        int **adjacencias;
}

class ListaAdjacencias{
    public:
        ListaAdjacencias();
        ListaAdjacencias(ofstream *input);

        void setAdjacencia(int v1, int v2);

        void BFS(int origem);
        void DFS(int origem);

        void componentesConexos();
    protected:
    private:
        int *vertices;
        list<Vertice> *adjacencias;
}

#endif //GRAFO_H