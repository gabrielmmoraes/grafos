#include "grafo.h"
#include<string>

using namespace std;

Vertice::Vertice(int i){
    this.indice = i;
    this.grau = 0;
    this.descoberto = 0;
    this.explorado = 0;
    this.pai = -2;
    this.nivel = -1;
}

int Vertice::getIndice(){
    return this.indice;
}

int Vertice::getGrau(){
    return this.grau;
}

int Vertice::getPai(){
    return this.pai;
}

int Vertice::getNivel(){
    return this.nivel;
}

void Vertice::incrementaGrau(){
    this.grau++;
}

void Vertice::setPai(int v){
    this.pai = v;
}

void Vertice::setNivel(int n){
    this.nivel = n;
}


Aresta::Aresta(int v1, int v2){
    this.v[0] = new Vertice(v1);
    this.v[1] = new Vertice(v2);
}

Vertice Aresta::getVertice(int v){
    return this.v[v-1];
}

MatrizAdjacencias::MatrizAdjacencias(int n){
    this.n_vertices = n;
    this.n_arestas = 0;
    for(int i=0;i<this.n_vertices;i++){
        this.vertices[i] = new Vertice(i+1);
        for(int j=0;j<this.n_vertices;j++){
            this.adjacencias[i][j] = 0;
        }
    }
}

MatrizAdjacencias::MatrizAdjacencias(ifstream *input){
}

void MatrizAdjacencias::setAdjacencia(int v1, int v2){
    this.adjacencias[v1-1][v2-1] = 1;
    this.adjacencias[v2-1][v1-1] = 1;
}

void MatrizAdjacencias::BFS(int origem){}
void MatrizAdjacencias::DFS(int origem){}

void MatrizAdjacencias::componentesConexos(){}


ListaAdjacencias::ListaAdjacencias(int n){
    this.n_vertices = n;
    this.n_arestas = 0;
    for(int i=0;i<this.n_vertices;i++){
        this.vertices[i] = new Vertice(i+1);
        this.adjacencias[i] = new list<int>;
    }
}

ListaAdjacecnias::ListaAdjacencias(ifstream *input){}

void ListaAdjacencias::setAdjacencia(int v1, int v2){
    this.adjacencias[v1-1].insert(v2-1);
    this.adjacencias[v2-1].insert(v1-1);
}

void ListaAdjacencais::BFS(int origem){}
void ListaAdjacencias::DFS(int origem){}

void ListaAdjacencias::componentesConexos(){}