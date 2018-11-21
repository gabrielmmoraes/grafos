#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include "tupla.h"
#include "lista.h"

using namespace std;

class Vertice
{
  public:
    Vertice(float x=0, float y=0);

    int getGrau();
    int getPai();
    int getNivel();
    float getPosX();
    float getPosY();
    int getMarcacao();

    void incrementaGrau();
    void setPai(int v);
    void setNivel(int n);
    void setPos(float x, float y);
    void desmarca();
    void marca(int i = 1);

  protected:
  private:
    int grau;
    int marcacao;
    int pai;
    int nivel;
    float pos_x;
    float pos_y;
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
    bool peso;
    bool pesos_negativos;
    int n_vertices;
    int n_arestas;
    Vertice **vertices;

  private:
};

class MatrizAdjacencias : public Grafo
{
  public:
    MatrizAdjacencias(int n, bool p);
    ~MatrizAdjacencias();
    MatrizAdjacencias(FILE *pontos);
    MatrizAdjacencias(FILE *input, bool p);

    int getNVertices();
    int getNArestas();

    void setAdjacencia(int v1, int v2, float w);

    int BFS(int origem);
    void DFS(int origem);

    Tupla<int*, float> TSP();

    float* Dijkstra(int origem, int destino=-1);
    float* Prim(int origem);

    Tupla<int*, float> CaminhoMinimo(int origem, int destino);

    void ArvoreGeradoraMinima(FILE* output);

    int diametro();
    float excentricidade(int vertice);
    float DistanciaMedia();

    vector<Tupla<int, int> >  componentesConexos();
    Lista **analiseComponentesConexos();

  protected:
  private:
    float **adjacencias;
};

class ListaAdjacencias : public Grafo
{
  public:
    ListaAdjacencias(int n, bool p);
    ~ListaAdjacencias();
    ListaAdjacencias(FILE *pontos);
    ListaAdjacencias(FILE *input, bool p);

    int getNVertices();
    int getNArestas();

    void setAdjacencia(int v1, int v2, float w);

    int BFS(int origem);
    void DFS(int origem);
    
    float* Dijkstra(int origem, int destino=-1);
    float* Prim(int origem);

    Tupla<int*, float> CaminhoMinimo(int origem, int destino);

    void ArvoreGeradoraMinima(FILE* output);

    int diametro();
    float excentricidade(int vertice);
    float DistanciaMedia();

    vector<Tupla<int, int> > componentesConexos();
    Lista **analiseComponentesConexos();

  protected:
  private:
    Lista **adjacencias;
};

#endif //GRAFO_H