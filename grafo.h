#ifndef GRAFO_H
#define GRAFO_H

#include <list>
#include <fstream.h>

using namespace std;

class Vertice{
    public:
        Vertice(int i);
        
        int getIndice();
        int getGrau();
        int getPai();
        int getNivel();

        void incrementaGrau();
        void setPai(int v);
        void setNivel(int n);
    protected:
    private:
        int indice;
        int grau;
        int descoberto;
        int explorado;
        int pai;
        int nivel;
        
};

class Aresta{
    public:
        Aresta(int v1, int v2);
        Vertice getVertice(int v);
    protected:
    private:
        Vertice v[2];
};

class MatrizAdjacencias{
    public:
        MatrizAdjacencias(int n);
        MatrizAdjacencias(ifstream *input);

        void setAdjacencia(int v1, int v2);

        void BFS(int origem);
        void DFS(int origem);

        void componentesConexos();

    protected:
    private:
        int n_vertices;
        int n_arestas;
        Vertice vertices[n_vertices];
        int adjacencias[n_vertices][n_vertices];
};

class ListaAdjacencias{
    public:
        ListaAdjacencias(int n);
        ListaAdjacencias(ifstream *input);

        void setAdjacencia(int v1, int v2);

        void BFS(int origem);
        void DFS(int origem);

        void componentesConexos();
    protected:
    private:
        int n_vertices;
        int n_arestas;
        Vertice vertices[n_vertices];
        list<int> adjacencias[n_vertices];
};

#endif //GRAFO_H