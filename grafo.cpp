#include "grafo.h"
#include <list>
#include <queue>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>>

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
    marcacao = 1;
    // marcacao = i;
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
    int v;
    int i;
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
void MatrizAdjacencias::DFS(int origem){
    for(int i=0;i<n_vertices;i++){
        vertices[i]->desmarca();
    }
    stack<int> S;
    S.push(origem-1);
    int v;
    int i;
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


ListaAdjacencias::ListaAdjacencias(int  n){
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
    // Definindo Tupla para marcação de vértice pai
    typedef struct Tupla{
       int vertice;
       int pai;
     } Tupla;    
  
    // Declaração de variáveis locais
   
    // Iterador de for
    int i;

    // Lista de ponteiros para tuplas
    Tupla** listaTupla = (Tupla**) malloc(sizeof(Tupla*)*n_vertices);

    // Criando stack de ponteiros para tuplas
    stack<Tupla*> S;

    // Criando variável iterável do DFS
    Tupla* tupla;

    // Declarando lista de vizinhos do vértice sendo analisado no DFS
    list<int> *vizinhos;

    // Definindo um iterador para lista vizinhos
    list<int>::iterator w;

    // For de inicialização do DFS
    for(i=0;i<n_vertices;i++){
      // Desmarcando todos os vértices
      vertices[i]->desmarca();
      
      // Alocando espaço para a tupla e guardando na lista
      // Número máximo de elementos da pilha é igual a N
      listaTupla[i] = (Tupla*) malloc(sizeof(Tupla)*n_vertices);

      // Inicializando vértices nas tuplas de forma que estejam ordenados em relação aos índices do grafo
      // Detalhe: não podemos inicializar tupla->pai, pois vai depender do grafo
      listaTupla[i]->vertice = i;
    }

    // Botando o ponteiro da tupla do vértice de origem no stack
    S.push(listaTupla[origem]);
    

    while(!S.empty()){
        // Definindo tupla a ser analizada como o topo da pilha
        tupla = S.top();

        // O pai é o vértice que botou a tupla na pilha mais recentemente
        // Se o pai ainda não foi definido, então o último vértice a botar tupla->vertice na pilha é o pai de tupla->vertice
        if(vertices[tupla->vertice]->getPai() == -1){
            vertices[tupla->vertice]->setPai(tupla->pai);
        }

        // Retirando tupla da pilha
        S.pop();

        // Se vértice ainda não foi marcado, realizar busca dentro dele
        if(vertices[tupla->vertice]->getMarcacao()==0){
            // Marca o vértice com o número de sua componente conexa
            vertices[tupla->vertice]->marca();
            // Definindo lista vizinhos como lista de vértices adjacentes de tupla->vertice
            vizinhos = adjacencias[tupla->vertice];
            // Iterando sobre todos elementos da lista vizinhos e adicionando-os à pilha
            for(w = vizinhos->begin();w!=vizinhos->end();w++){
                // A tupla guarda o vértice tupla->vertice como possível pai de w
                // Ele só será definido como pai se ele estiver definido como pai de w quando w for tirado da pilha pela primeira vez
                listaTupla[*w]->pai = tupla->vertice;              
                S.push(listaTupla[*w]);
            }
        }
    }
}


void ListaAdjacencias::componentesConexos(){}   