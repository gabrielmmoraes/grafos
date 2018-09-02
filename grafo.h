#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <list>
#include<vector>

using namespace std;

// Definindo Tupla para marcação de vértice pai
  class Tupla{
      public:
        Tupla();
        Tupla(int e1, int e2);
        ~Tupla();

        bool operator >(Tupla t);
        bool operator <(Tupla t);
        int elem1;
        int elem2;
  };

typedef struct ListNode{
    ListNode* prev;
    int indice;
    ListNode* prox;
} ListNode;

class Lista{
    public:
        Lista();
        ~Lista();

        ListNode* push(int i);
        void erase(ListNode* no);

        bool vazia();
        int getTamanho();

        ListNode* getInicio();
        ListNode* getFim();
    protected:
    private:
        int tamanho;
        ListNode* inicio;
        ListNode* fim;
};

class Vertice{
    public:
        Vertice();
        
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

class Grafo{
    public:
        Grafo();
        ~Grafo();

        int getGrauMin();
        int getGrauMax();
        float getGrauMedio();
        float getGrauMediano();

        Vertice** getVertices();

    protected:
        int n_vertices;
        int n_arestas;
        Vertice** vertices;
    private:
};

class MatrizAdjacencias: public Grafo{
    public:
        MatrizAdjacencias(int n);
        ~MatrizAdjacencias();
        MatrizAdjacencias(FILE* input);

        int getNVertices();
        int getNArestas();

        void setAdjacencia(int v1, int v2);

        void BFS(int origem);
        void DFS(int origem);

        vector<Tupla> componentesConexos();
        Lista** analiseComponentesConexos();

    protected:
    private:
        int **adjacencias;
};

class ListaAdjacencias: public Grafo{
    public:
        ListaAdjacencias(int n);
        ~ListaAdjacencias();
        ListaAdjacencias(FILE *input);

        int getNVertices();
        int getNArestas();

        void setAdjacencia(int v1, int v2);

        void BFS(int origem);
        void DFS(int origem);

        vector<Tupla> componentesConexos();
        Lista** analiseComponentesConexos();
        
    protected:
    private:
        Lista **adjacencias;
};

#endif //GRAFO_H