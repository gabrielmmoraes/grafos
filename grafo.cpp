#include "grafo.h"
#include <list>
#include <queue>
#include <stack>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Vertice::Vertice()
{
    grau = 0;
    marcacao = 0;
    pai = -2;
    nivel = -1;
}

Vertice::~Vertice()
{
}

int Vertice::getGrau()
{
    return grau;
}

int Vertice::getPai()
{
    return pai;
}

int Vertice::getNivel()
{
    return nivel;
}

int Vertice::getMarcacao()
{
    return marcacao;
}

void Vertice::incrementaGrau()
{
    grau++;
}

void Vertice::setPai(int v)
{
    pai = v;
}

void Vertice::setNivel(int n)
{
    nivel = n;
}

void Vertice::desmarca()
{
    marcacao = 0;
    pai = -2;
    nivel = -1;
}

void Vertice::marca(int i)
{
    marcacao = i;
}

Aresta::Aresta(int v1, int v2)
{
    v[0] = new Vertice();
    v[1] = new Vertice();
}

Aresta::~Aresta()
{
    free(v);
}

Vertice *Aresta::getVertice(int v)
{
    return this->v[v - 1];
}

MatrizAdjacencias::MatrizAdjacencias(int n)
{
    n_vertices = n;
    n_arestas = 0;
    vertices = (Vertice **)malloc(sizeof(Vertice *) * n_vertices);
    adjacencias = (int **)malloc(sizeof(int *) * n_vertices);
    for (int i = 0; i < n_vertices; i++)
    {
        vertices[i] = new Vertice();
        adjacencias[i] = (int *)malloc(sizeof(int) * n_vertices);
        for (int j = 0; j < n_vertices; j++)
        {
            adjacencias[i][j] = 0;
        }
    }
}

MatrizAdjacencias::MatrizAdjacencias(FILE *input)
{
    fscanf(input, "%d", &n_vertices);
    n_arestas = 0;
    vertices = (Vertice **)malloc(sizeof(Vertice *) * n_vertices);
    adjacencias = (int **)malloc(sizeof(int *) * n_vertices);
    for (int i = 0; i < n_vertices; i++)
    {
        vertices[i] = new Vertice();
        adjacencias[i] = (int *)malloc(sizeof(int) * n_vertices);
        for (int j = 0; j < n_vertices; j++)
        {
            adjacencias[i][j] = 0;
        }
    }

    int v1, v2;
    while (fscanf(input, "%d %d", &v1, &v2) != EOF)
    {
        setAdjacencia(v1, v2);
    }
}

MatrizAdjacencias::~MatrizAdjacencias()
{
    free(vertices);
    for (int i = 0; i < n_vertices; i++)
    {
        free(adjacencias[i]);
    }
    free(adjacencias);
}

int MatrizAdjacencias::getNVertices()
{
    return n_vertices;
}

int MatrizAdjacencias::getNArestas()
{
    return n_arestas;
}

void MatrizAdjacencias::setAdjacencia(int v1, int v2)
{
    adjacencias[v1 - 1][v2 - 1] = 1;
    adjacencias[v2 - 1][v1 - 1] = 1;
    vertices[v1 - 1]->incrementaGrau();
    vertices[v2 - 1]->incrementaGrau();
    n_arestas++;
}

void MatrizAdjacencias::BFS(int origem, int marcador)
{
    if (marcador == 1)
    {
        for (int i = 0; i < n_vertices; i++)
        {
            vertices[i]->desmarca();
        }
    }
    queue<int> Q;
    int nivel;
    vertices[origem]->marca(marcador);
    Q.push(origem);
    vertices[origem]->setNivel(0);
    vertices[origem]->setPai(-1);
    int v;
    int i;
    while (!Q.empty())
    {
        v = Q.front();
        Q.pop();
        for (i = 0; i < n_vertices; i++)
        {
            if (adjacencias[v][i])
            {
                if (vertices[i]->getMarcacao() == 0)
                {
                    vertices[i]->marca(marcador);
                    nivel = vertices[v]->getNivel() + 1;
                    vertices[i]->setNivel(nivel);
                    vertices[i]->setPai(v);
                    Q.push(i);
                }
            }
        }
    }
}
void MatrizAdjacencias::DFS(int origem)
{

    // Iterador de for
    int i;

    // Lista de ponteiros para tuplas
    Tupla **listaTupla = (Tupla **)malloc(sizeof(Tupla *) * n_vertices);

    // Criando stack de ponteiros para tuplas
    stack<Tupla *> S;

    // Criando variável iterável do DFS
    Tupla *tupla;

    int nivel;

    for (int i = 0; i < n_vertices; i++)
    {
        vertices[i]->desmarca();

        listaTupla[i] = (Tupla *)malloc(sizeof(Tupla));

        listaTupla[i]->vertice = i;
    }

    listaTupla[origem]->pai = -1;
    S.push(listaTupla[origem]);

    while (!S.empty())
    {
        tupla = S.top();
        printf("Analisando vértice %d\n", tupla->vertice + 1);
        S.pop();
        if (vertices[tupla->vertice]->getMarcacao() == 0)
        {
            printf("Definindo pai de %d como %d\n", tupla->vertice + 1, tupla->pai + 1);
            vertices[tupla->vertice]->setPai(tupla->pai);
            nivel = vertices[tupla->vertice]->getPai() != -1 ? vertices[tupla->pai]->getNivel() + 1 : 0;
            printf("Definindo nível de %d como %d\n", tupla->vertice + 1, nivel);
            vertices[tupla->vertice]->setNivel(nivel);
            vertices[tupla->vertice]->marca();
            for (i = n_vertices - 1; i >= 0; i--)
            {
                if (adjacencias[tupla->vertice][i])
                {
                    printf("Possível pai de %d marcado como %d\n", listaTupla[i]->vertice + 1, tupla->vertice + 1);
                    listaTupla[i]->pai = tupla->vertice;
                    S.push(listaTupla[i]);
                }
            }
        }
    }
}

void MatrizAdjacencias::componentesConexos()
{
    list<int> desmarcados;
    list<int>::iterator *indices = (list<int>::iterator *)malloc(sizeof(list<int>::iterator) * n_vertices);
    list<int>::iterator it = desmarcados.begin();
    for (int i = 0; i < n_vertices; i++)
    {
        vertices[i]->desmarca();
        desmarcados.push_back(i);
        indices[i] = ++it;
    }
    queue<int> Q;
    int marcador = 1;
    int origem = 0;
    while (!desmarcados.empty())
    {
        vertices[origem]->marca(marcador);
        desmarcados.erase(indices[origem]);
        Q.push(origem);
        int v;
        int i;
        while (!Q.empty())
        {
            v = Q.front();
            Q.pop();
            for (i = 0; i < n_vertices; i++)
            {
                if (adjacencias[v][i])
                {
                    if (vertices[i]->getMarcacao() == 0)
                    {
                        vertices[i]->marca(marcador);
                        desmarcados.erase(indices[i]);
                        Q.push(i);
                    }
                }
            }
        }
        origem = desmarcados.front();
        marcador++;
    }
}

ListaAdjacencias::ListaAdjacencias(int n)
{
    n_vertices = n;
    n_arestas = 0;
    vertices = (Vertice **)malloc(sizeof(Vertice *) * n_vertices);
    adjacencias = (list<int> **)malloc(sizeof(list<int> *) * n_vertices);
    for (int i = 0; i < n_vertices; i++)
    {
        vertices[i] = new Vertice();
        adjacencias[i] = new list<int>;
    }
}

ListaAdjacencias::ListaAdjacencias(FILE *input)
{
    fscanf(input, "%d", &n_vertices);
    n_arestas = 0;
    vertices = (Vertice **)malloc(sizeof(Vertice *) * n_vertices);
    adjacencias = (list<int> **)malloc(sizeof(list<int> *) * n_vertices);
    for (int i = 0; i < n_vertices; i++)
    {
        vertices[i] = new Vertice();
        adjacencias[i] = new list<int>;
    }

    int v1, v2;
    while (fscanf(input, "%d %d", &v1, &v2) != EOF)
    {
        setAdjacencia(v1, v2);
    }
}

ListaAdjacencias::~ListaAdjacencias()
{
    free(vertices);
    free(adjacencias);
}

int ListaAdjacencias::getNVertices()
{
    return n_vertices;
}

int ListaAdjacencias::getNArestas()
{
    return n_arestas;
}

void ListaAdjacencias::setAdjacencia(int v1, int v2)
{
    adjacencias[v1 - 1]->push_back(v2 - 1);
    adjacencias[v2 - 1]->push_back(v1 - 1);
    vertices[v1 - 1]->incrementaGrau();
    vertices[v2 - 1]->incrementaGrau();
    n_arestas++;
}

void ListaAdjacencias::BFS(int origem, int marcador)
{
    int v;
    if (marcador == 1)
    {
        for (int i = 0; i < n_vertices; i++)
        {
            vertices[i]->desmarca();
        }
    }
    queue<int> Q;
    int nivel;
    vertices[origem]->marca(marcador);
    Q.push(origem);
    vertices[origem]->setNivel(0);
    vertices[origem]->setPai(-1);
    while (!Q.empty())
    {
        v = Q.front();
        Q.pop();
        list<int>::iterator w;
        list<int> *vizinhos = adjacencias[v];
        for (w = vizinhos->begin(); w != vizinhos->end(); ++w)
        {
            if (vertices[*w]->getMarcacao() == 0)
            {
                vertices[*w]->marca(marcador);
                nivel = vertices[v]->getNivel() + 1;
                vertices[*w]->setNivel(nivel);
                vertices[*w]->setPai(v);
                Q.push(*w);
            }
        }
    }
}

void ListaAdjacencias::DFS(int origem)
{

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Declaração de variáveis locais

    // Iterador de for
    int i;

    // Lista de ponteiros para tuplas
    Tupla **listaTupla = (Tupla **)malloc(sizeof(Tupla *) * n_vertices);

    // Criando stack de ponteiros para tuplas
    stack<Tupla *> S;

    // Criando variável iterável do DFS
    Tupla *tupla;

    // Declarando lista de vizinhos do vértice sendo analisado no DFS
    list<int> *vizinhos;

    // Definindo um iterador para lista vizinhos
    list<int>::iterator w;

    int nivel;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Preparando para executar DFS

    // For de inicialização do DFS
    for (i = 0; i < n_vertices; i++)
    {
        // Desmarcando todos os vértices
        vertices[i]->desmarca();

        listaTupla[i] = (Tupla *)malloc(sizeof(Tupla));

        listaTupla[i]->vertice = i;
    }

    listaTupla[origem]->pai = -1;

    // Botando o ponteiro da tupla do vértice de origem no stack
    S.push(listaTupla[origem]);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // DFS

    while (!S.empty())
    {
        // Definindo tupla a ser analizada como o topo da pilha
        tupla = S.top();

        printf("Analisando vértice %d\n", tupla->vertice);

        // Retirando tupla da pilha
        S.pop();

        // Se vértice ainda não foi marcado, realizar busca dentro dele
        if (vertices[tupla->vertice]->getMarcacao() == 0)
        {
            printf("Definindo pai de %d como %d\n", tupla->vertice + 1, tupla->pai + 1);

            // O pai é o vértice que botou a tupla na pilha mais recentemente
            // Se o pai ainda não foi definido, então o último vértice a botar tupla->vertice na pilha é o pai de tupla->vertice
            vertices[tupla->vertice]->setPai(tupla->pai);

            printf("Pai de %d é %d\n", tupla->vertice, vertices[tupla->vertice]->getPai());
            //nivel = vertices[tupla->vertice]->getPai() != -1 ? vertices[tupla->pai]->getNivel()+1 : 0;
            //printf("Definindo nível de %d como %d\n", tupla->vertice+1, nivel);

            // Nível do vértice é igual ao nível do pai +1
            //vertices[tupla->vertice]->setNivel(nivel);

            // Marca o vértice com o número de sua componente conexa
            vertices[tupla->vertice]->marca();
            // Definindo lista vizinhos como lista de vértices adjacentes de tupla->vertice
            vizinhos = adjacencias[tupla->vertice];
            // Iterando sobre todos elementos da lista vizinhos e adicionando-os à pilha
            for (w = vizinhos->begin(); w != vizinhos->end(); ++w)
            {
                // A tupla guarda o vértice tupla->vertice como possível pai de w
                // Ele só será definido como pai se ele estiver definido como pai de w quando w for tirado da pilha pela primeira vez
                printf("Possível pai de %d marcado como %d\n", listaTupla[*w]->vertice + 1, tupla->vertice + 1);
                listaTupla[*w]->pai = tupla->vertice;
                // Inserindo tupla do vizinho no stack
                S.push(listaTupla[*w]);
            }
        }
    }
}

void ListaAdjacencias::componentesConexos()
{
    list<int> desmarcados;
    list<int>::iterator *indices = (list<int>::iterator *)malloc(sizeof(list<int>::iterator) * n_vertices);
    list<int>::iterator it = desmarcados.begin();
    for (int i = 0; i < n_vertices; i++)
    {
        vertices[i]->desmarca();
        desmarcados.push_back(i);
        indices[i] = ++it;
    }
    queue<int> Q;
    int marcador = 1;
    int origem = 0;
    while (!desmarcados.empty())
    {
        vertices[origem]->marca(marcador);
        desmarcados.erase(indices[origem]);
        Q.push(origem);
        int v;
        while (!Q.empty())
        {
            v = Q.front();
            Q.pop();
            list<int>::iterator w;
            list<int> *vizinhos = adjacencias[v];
            for (w = vizinhos->begin(); w != vizinhos->end(); ++w)
            {
                if (vertices[*w]->getMarcacao() == 0)
                {
                    vertices[*w]->marca(marcador);
                    desmarcados.erase(indices[*w]);
                    Q.push(*w);
                }
            }
        }
        origem = desmarcados.front();
        marcador++;
    }
}