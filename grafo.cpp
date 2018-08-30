#include "grafo.h"
#include <list>
#include <queue>
#include <stack>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Vertice::Vertice(int i){
    indice = i;
    grau = 0;
    marcacao = 0;
    pai = -1;
    nivel = -1;
}

int Vertice::getIndice(){
    return indice;
}

int Vertice::getGrau(){
    return grau;
}

int Vertice::getPai(){
    return pai;
}

int Vertice::getNivel(){
    return nivel;
}

int Vertice::getMarcacao(){
    return marcacao;
}

void Vertice::incrementaGrau(){
    grau++;
}

void Vertice::setPai(int v){
    pai = v;
}

void Vertice::setNivel(int n){
    nivel = n;
}

void Vertice::desmarca(){
    marcacao = 0;
    pai = -1;
    nivel = -1;
}

void Vertice::marca(int i){
    marcacao = i;
}

Aresta::Aresta(int v1, int v2){
    v[0] = new Vertice(v1);
    v[1] = new Vertice(v2);
}

Vertice* Aresta::getVertice(int v){
    return this->v[v-1];
}

MatrizAdjacencias::MatrizAdjacencias(int n){
    n_vertices = n;
    n_arestas = 0;
    vertices = (Vertice**) malloc(sizeof(Vertice*)*n_vertices);
    adjacencias = (int**) malloc(sizeof(int*)*n_vertices);
    for(int i=0;i<n_vertices;i++){
        vertices[i] = new Vertice(i+1);
        adjacencias[i] = (int*) malloc(sizeof(int)*n_vertices);
        for(int j=0;j<n_vertices;j++){
            adjacencias[i][j] = 0;
        }
    }
}

MatrizAdjacencias::MatrizAdjacencias(FILE *input){
    fscanf(input, "%d", &n_vertices);
    n_arestas = 0;
    vertices = (Vertice**) malloc(sizeof(Vertice*)*n_vertices);
    adjacencias = (int**) malloc(sizeof(int*)*n_vertices);
    for(int i=0;i<n_vertices;i++){
        vertices[i] = new Vertice(i+1);
        adjacencias[i] = (int*) malloc(sizeof(int)*n_vertices);
        for(int j=0;j<n_vertices;j++){
            adjacencias[i][j] = 0;
        }
    }
    
    int v1, v2;
    while(fscanf(input, "%d %d", &v1, &v2) != EOF){
        setAdjacencia(v1,v2);
    }
}

void MatrizAdjacencias::setAdjacencia(int v1, int v2){
    adjacencias[v1-1][v2-1] = 1;
    adjacencias[v2-1][v1-1] = 1;
    vertices[v1-1]->incrementaGrau();
    vertices[v2-1]->incrementaGrau();
    n_arestas++;
}

void MatrizAdjacencias::BFS(int origem){
    for(int i=0;i<n_vertices;i++){
        vertices[i]->desmarca();
    }
    queue<int> Q;
    int nivel;
    vertices[origem-1]->marca();
    Q.push(origem-1);
    vertices[origem-1]->setNivel(0);
    vertices[origem-1]->setPai(0);
    while(!Q.empty()){
        int v = Q.front();
        Q.pop();
        for(int i=0;i<n_vertices;i++){
            if(adjacencias[v][i]){
                if(vertices[i]->getMarcacao() == 0){
                    vertices[i]->marca();
                    nivel = vertices[v]->getNivel()+1;
                    vertices[i]->setNivel(nivel);
                    vertices[i]->setPai(v+1);
                    Q.push(i);
                }
            }
        }
    } 
}
void MatrizAdjacencias::DFS(int origem){
    for(int i=0;i<n_vertices;i++){
        vertices[i]->desmarca();
    }
    stack<int> S;
    S.push(origem-1);
    while(!S.empty()){
        int v = S.top();
        S.pop();
        if(vertices[v]->getMarcacao()==0){
            vertices[v]->marca();
            for(int i=n_vertices-1;i>=0;i--){
                if(adjacencias[v][i]){
                    S.push(i);
                }
            }
        }
    }
}

void MatrizAdjacencias::componentesConexos(){}


ListaAdjacencias::ListaAdjacencias(int n){
    n_vertices = n;
    n_arestas = 0;
    vertices = (Vertice**) malloc(sizeof(Vertice*)*n_vertices);
    adjacencias = (list<int>**) malloc(sizeof(list<int>*)*n_vertices);
    for(int i=0;i<n_vertices;i++){
        vertices[i] = new Vertice(i+1);
        adjacencias[i] = new list<int>;
    }
}

ListaAdjacencias::ListaAdjacencias(FILE *input){
    fscanf(input, "%d", &n_vertices);
    n_arestas = 0;
    vertices = (Vertice**) malloc(sizeof(Vertice*)*n_vertices);
    adjacencias = (list<int>**) malloc(sizeof(list<int>*)*n_vertices);
    for(int i=0;i<n_vertices;i++){
        vertices[i] = new Vertice(i+1);
        adjacencias[i] = new list<int>;
    }

    int v1, v2;
    while(fscanf(input, "%d %d", &v1, &v2) != EOF){
        setAdjacencia(v1,v2);
    }

}

void ListaAdjacencias::setAdjacencia(int v1, int v2){
    adjacencias[v1-1]->push_back(v2-1);
    adjacencias[v2-1]->push_back(v1-1);
    vertices[v1-1]->incrementaGrau();
    vertices[v2-1]->incrementaGrau();
    n_arestas++;
}

void ListaAdjacencias::BFS(int origem){
    int v;
    for(int i=0;i<n_vertices;i++){
        vertices[i]->desmarca();
    }
    queue<int> Q;
    int nivel;
    vertices[origem-1]->marca();
    Q.push(origem-1);
    vertices[origem-1]->setNivel(0);
    vertices[origem-1]->setPai(0);
    while(!Q.empty()){
        v = Q.front();
        Q.pop();
        list<int>::iterator w;
        list<int> *vizinhos = adjacencias[v];
        for(w = vizinhos->begin();w!= vizinhos->end();w++){
            if(vertices[*w]->getMarcacao()==0){
                vertices[*w]->marca();
                nivel = vertices[v]->getNivel()+1;
                vertices[*w]->setNivel(nivel);
                vertices[*w]->setPai(v+1);
                Q.push(*w);
            }
        }
    }
}

void ListaAdjacencias::DFS(int origem){
    for(int i=0;i<n_vertices;i++){
        vertices[i]->desmarca();
    }
    stack<int> S;
    S.push(origem-1);
    while(!S.empty()){
        int v = S.top();
        S.pop();
        if(vertices[v]->getMarcacao()==0){
            vertices[v]->marca();
            list<int>::iterator w;
            list<int> *vizinhos = adjacencias[v];
            for(w = vizinhos->begin();w!=vizinhos->end();w++){
                S.push(*w);
            }
        }
    }
}

void ListaAdjacencias::componentesConexos(){}   