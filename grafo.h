#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include<vector>
#include "tupla.h"
#include "lista.h"

using namespace std;

class Vertice
{
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
    void marca(int i = 1);

  protected:
  private:
    int grau;
    int marcacao;
    int pai;
    int nivel;
};

class Aresta
{
  public:
    Aresta(int v1, int v2);
    ~Aresta();
    Vertice *getVertice(int v);
  protected:
  private:
    Vertice *v[2];
};

class Grafo
{
  public:
    Grafo();
    ~Grafo();

    int getGrauMin();
    int getGrauMax();
    float getGrauMedio();
    float getGrauMediano();

    Vertice **getVertices();

  protected:
    int n_vertices;
    int n_arestas;
    Vertice **vertices;

  private:
};

class MatrizAdjacencias : public Grafo
{
  public:
    MatrizAdjacencias(int n);
    ~MatrizAdjacencias();
    MatrizAdjacencias(FILE *input);

    int getNVertices();
    int getNArestas();

    void setAdjacencia(int v1, int v2);

    int BFS(int origem);
    void DFS(int origem);

    int diametro();

    vector<Tupla> componentesConexos();
    Lista **analiseComponentesConexos();

  protected:
  private:
    int **adjacencias;
};

class ListaAdjacencias : public Grafo
{
  public:
    ListaAdjacencias(int n);
    ~ListaAdjacencias();
    ListaAdjacencias(FILE *input);

    int getNVertices();
    int getNArestas();

    void setAdjacencia(int v1, int v2);

    int BFS(int origem);
    void DFS(int origem);

    int diametro();

    vector<Tupla> componentesConexos();
    Lista **analiseComponentesConexos();

  protected:
  private:
    Lista **adjacencias;
};

#endif //GRAFO_H