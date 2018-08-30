#include "grafo.h"
#include <list>
#include <queue>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>>

using namespace std;

Vertice::Vertice(unsigned long i){
    indice = i;
    grau = 0;
    marcacao = 0;
    pai = -1;
    nivel = -1;
}

unsigned long Vertice::getIndice(){
    return indice;
}

unsigned long Vertice::getGrau(){
    return grau;
}

unsigned long Vertice::getPai(){
    return pai;
}

unsigned long Vertice::getNivel(){
    return nivel;
}

uint8_t Vertice::getMarcacao(){
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
    marcacao = 1;
    // marcacao = i;
}

Aresta::Aresta(unsigned long v1, unsigned long v2){
    v[0] = new Vertice(v1);
    v[1] = new Vertice(v2);
}

Vertice* Aresta::getVertice(unsigned long v){
    return this->v[v-1];
}

MatrizAdjacencias::MatrizAdjacencias(unsigned long n){
    n_vertices = n;
    n_arestas = 0;
    vertices = (Vertice**) malloc(sizeof(Vertice*)*n_vertices);
    adjacencias = (unsigned long**) malloc(sizeof(unsigned long*)*n_vertices);
    for(unsigned long i=0;i<n_vertices;i++){
        vertices[i] = new Vertice(i+1);
        adjacencias[i] = (unsigned long*) malloc(sizeof(unsigned long)*n_vertices);
        for(unsigned long j=0;j<n_vertices;j++){
            adjacencias[i][j] = 0;
        }
    }
}

MatrizAdjacencias::MatrizAdjacencias(FILE *input){
    fscanf(input, "%d", &n_vertices);
    n_arestas = 0;
    vertices = (Vertice**) malloc(sizeof(Vertice*)*n_vertices);
    adjacencias = (unsigned long**) malloc(sizeof(unsigned long*)*n_vertices);
    for(unsigned long i=0;i<n_vertices;i++){
        vertices[i] = new Vertice(i+1);
        adjacencias[i] = (unsigned long*) malloc(sizeof(unsigned long)*n_vertices);
        for(unsigned long j=0;j<n_vertices;j++){
            adjacencias[i][j] = 0;
        }
    }
    
    unsigned long v1, v2;
    while(fscanf(input, "%d %d", &v1, &v2) != EOF){
        setAdjacencia(v1,v2);
    }
}

void MatrizAdjacencias::setAdjacencia(unsigned long v1, unsigned long v2){
    adjacencias[v1-1][v2-1] = 1;
    adjacencias[v2-1][v1-1] = 1;
    vertices[v1-1]->incrementaGrau();
    vertices[v2-1]->incrementaGrau();
    n_arestas++;
}

void MatrizAdjacencias::BFS(unsigned long origem){
    for(unsigned long i=0;i<n_vertices;i++){
        vertices[i]->desmarca();
    }
    queue<unsigned long> Q;
    unsigned long nivel;
    vertices[origem-1]->marca();
    Q.push(origem-1);
    vertices[origem-1]->setNivel(0);
    vertices[origem-1]->setPai(0);
    unsigned long v;
    unsigned long i;
    while(!Q.empty()){
        v = Q.front();
        Q.pop();
        for(i=0;i<n_vertices;i++){
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
void MatrizAdjacencias::DFS(unsigned long origem){
    for(unsigned long i=0;i<n_vertices;i++){
        vertices[i]->desmarca();
    }
    stack<unsigned long> S;
    S.push(origem-1);
    unsigned long v;
    unsigned long i;
    while(!S.empty()){
        v = S.top();
        S.pop();
        if(vertices[v]->getMarcacao()==0){
            vertices[v]->marca();
            for(i=n_vertices-1;i>=0;i--){
                if(adjacencias[v][i]){
                    S.push(i);
                }
            }
        }
    }
}

void MatrizAdjacencias::componentesConexos(){}


ListaAdjacencias::ListaAdjacencias(unsigned long  n){
    n_vertices = n;
    n_arestas = 0;
    vertices = (Vertice**) malloc(sizeof(Vertice*)*n_vertices);
    adjacencias = (list<unsigned long>**) malloc(sizeof(list<unsigned long>*)*n_vertices);
    for(unsigned long i=0;i<n_vertices;i++){
        vertices[i] = new Vertice(i+1);
        adjacencias[i] = new list<unsigned long>;
    }
}

ListaAdjacencias::ListaAdjacencias(FILE *input){
    fscanf(input, "%d", &n_vertices);
    n_arestas = 0;
    vertices = (Vertice**) malloc(sizeof(Vertice*)*n_vertices);
    adjacencias = (list<unsigned long>**) malloc(sizeof(list<unsigned long>*)*n_vertices);
    for(unsigned long i=0;i<n_vertices;i++){
        vertices[i] = new Vertice(i+1);
        adjacencias[i] = new list<unsigned long>;
    }

    unsigned long v1, v2;
    while(fscanf(input, "%d %d", &v1, &v2) != EOF){
        setAdjacencia(v1,v2);
    }

}

void ListaAdjacencias::setAdjacencia(unsigned long v1, unsigned long v2){
    adjacencias[v1-1]->push_back(v2-1);
    adjacencias[v2-1]->push_back(v1-1);
    vertices[v1-1]->incrementaGrau();
    vertices[v2-1]->incrementaGrau();
    n_arestas++;
}

void ListaAdjacencias::BFS(unsigned long origem){
    unsigned long v;
    for(unsigned long i=0;i<n_vertices;i++){
        vertices[i]->desmarca();
    }
    queue<unsigned long> Q;
    unsigned long nivel;
    vertices[origem-1]->marca();
    Q.push(origem-1);
    vertices[origem-1]->setNivel(0);
    vertices[origem-1]->setPai(0);
    while(!Q.empty()){
        v = Q.front();
        Q.pop();
        list<unsigned long>::iterator w;
        list<unsigned long> *vizinhos = adjacencias[v];
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

void ListaAdjacencias::DFS(unsigned long origem){
    for(unsigned long i=0;i<n_vertices;i++){
        vertices[i]->desmarca();
    }
    stack<unsigned long> S;
    S.push(origem-1);
    unsigned long v;
    while(!S.empty()){
        S.top();
        S.pop();
        if(vertices[v]->getMarcacao()==0){
            vertices[v]->marca();
            list<unsigned long>::iterator w;
            list<unsigned long> *vizinhos = adjacencias[v];
            for(w = vizinhos->begin();w!=vizinhos->end();w++){
                S.push(*w);
            }
        }
    }
}

void ListaAdjacencias::componentesConexos(){}   