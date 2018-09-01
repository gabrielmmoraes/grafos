#include "grafo.h"
#include <list>
#include <queue>
#include <stack>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Lista::Lista()
{
    inicio = NULL;
    fim = NULL;
    tamanho = 0;
}

Lista::~Lista()
{
    ListNode *no = inicio;
    if(inicio){
        while (inicio->prox != NULL)
        {
            no = inicio;
            inicio = inicio->prox;
            free(no);
        }
        free(inicio);
    }
}

ListNode *Lista::push(int i)
{
    ListNode *no = (ListNode *)malloc(sizeof(ListNode));
    no->indice = i;
    no->prox = NULL;
    if (inicio == NULL)
    {
        no->prev = NULL;
        inicio = no;
    }
    else
    {
        no->prev = fim;
        fim->prox = no;
    }
    fim = no;
    tamanho++;

    return no;
}

void Lista::erase(ListNode *no)
{
    if (no==inicio && no==fim)
    {
        inicio = NULL;
        fim = NULL;
        tamanho--;
        free(no);
        return;
    }
    
    if (no==inicio)
    {
        inicio = no->prox;
        no->prox->prev == NULL;
        tamanho--;
        free(no);
        return;
    }
    if (no==fim)
    {
        fim = no->prev;
        no->prev->prox == NULL;
        tamanho--;
        free(no);
        return;
    }
    no->prev->prox = no->prox;
    no->prox->prev = no->prev;
    tamanho--;
    free(no);
}

bool Lista::vazia()
{
    return inicio==NULL;
}

int Lista::getTamanho(){
    return tamanho;
}

ListNode *Lista::getInicio()
{
    return inicio;
}

ListNode *Lista::getFim()
{
    return fim;
}

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
        S.pop();
        if (vertices[tupla->vertice]->getMarcacao() == 0)
        {
            vertices[tupla->vertice]->setPai(tupla->pai);
            nivel = vertices[tupla->vertice]->getPai() != -1 ? vertices[tupla->pai]->getNivel() + 1 : 0;
            vertices[tupla->vertice]->setNivel(nivel);
            vertices[tupla->vertice]->marca();
            for (i = n_vertices - 1; i >= 0; i--)
            {
                if (adjacencias[tupla->vertice][i])
                {
                    listaTupla[i]->pai = tupla->vertice;
                    S.push(listaTupla[i]);
                }
            }
        }
    }
}

void MatrizAdjacencias::componentesConexos()
{
    Lista desmarcados;
    ListNode **indices = (ListNode **)malloc(sizeof(ListNode *) * n_vertices);
    ListNode *no;
    for (int i = 0; i < n_vertices; i++)
    {
        vertices[i]->desmarca();
        no = desmarcados.push(i);
        indices[i] = no;
    }

    queue<int> Q;
    int marcador = 1;
    int origem = 0;
    while (!desmarcados.vazia())
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

        no = desmarcados.getInicio();
        if(!no) break;
        origem = no->indice;
        marcador++;
    }
}

ListaAdjacencias::ListaAdjacencias(int n)
{
    n_vertices = n;
    n_arestas = 0;
    vertices = (Vertice **)malloc(sizeof(Vertice *) * n_vertices);
    adjacencias = (Lista **)malloc(sizeof(Lista *) * n_vertices);
    for (int i = 0; i < n_vertices; i++)
    {
        vertices[i] = new Vertice();
        adjacencias[i] = new Lista();
    }
}

ListaAdjacencias::ListaAdjacencias(FILE *input)
{
    fscanf(input, "%d", &n_vertices);
    n_arestas = 0;
    vertices = (Vertice **)malloc(sizeof(Vertice *) * n_vertices);
    adjacencias = (Lista **)malloc(sizeof(Lista *) * n_vertices);
    for (int i = 0; i < n_vertices; i++)
    {
        vertices[i] = new Vertice();
        adjacencias[i] = new Lista();
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
    adjacencias[v1 - 1]->push(v2 - 1);
    adjacencias[v2 - 1]->push(v1 - 1);
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
        ListNode *w = adjacencias[v]->getInicio();
        while (w != NULL)
        {
            if (vertices[w->indice]->getMarcacao() == 0)
            {
                vertices[w->indice]->marca(marcador);
                nivel = vertices[v]->getNivel() + 1;
                vertices[w->indice]->setNivel(nivel);
                vertices[w->indice]->setPai(v);
                Q.push(w->indice);
            }
            w = w->prox;
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

        // Retirando tupla da pilha
        S.pop();

        // Se vértice ainda não foi marcado, realizar busca dentro dele
        if (vertices[tupla->vertice]->getMarcacao() == 0)
        {

            // O pai é o vértice que botou a tupla na pilha mais recentemente
            // Se o pai ainda não foi definido, então o último vértice a botar tupla->vertice na pilha é o pai de tupla->vertice
            vertices[tupla->vertice]->setPai(tupla->pai);

            nivel = vertices[tupla->vertice]->getPai() != -1 ? vertices[tupla->pai]->getNivel() + 1 : 0;

            // Nível do vértice é igual ao nível do pai +1
            vertices[tupla->vertice]->setNivel(nivel);

            // Marca o vértice com o número de sua componente conexa
            vertices[tupla->vertice]->marca();
            // Definindo lista vizinhos como lista de vértices adjacentes de tupla->vertice
            // Iterando sobre todos elementos da lista vizinhos e adicionando-os à pilha
            ListNode *w = adjacencias[tupla->vertice]->getFim();
            while (w != NULL)
            {
                // A tupla guarda o vértice tupla->vertice como possível pai de w
                // Ele só será definido como pai se ele estiver definido como pai de w quando w for tirado da pilha pela primeira vez
                listaTupla[w->indice]->pai = tupla->vertice;
                // Inserindo tupla do vizinho no stack
                S.push(listaTupla[w->indice]);
                w = w->prev;
            }
        }
    }
}

void ListaAdjacencias::componentesConexos()
{
    Lista desmarcados;
    ListNode **indices = (ListNode**) malloc(sizeof(ListNode*)*n_vertices);
    ListNode* no;
    for (int i = 0; i < n_vertices; i++)
    {
        vertices[i]->desmarca();
        no = desmarcados.push(i);
        indices[i] = no;
    }
    queue<int> Q;
    int marcador = 1;
    int origem = 0;
    while (!desmarcados.vazia())
    {
        vertices[origem]->marca(marcador);
        desmarcados.erase(indices[origem]);
        Q.push(origem);
        int v;
        while (!Q.empty())
        {
            v = Q.front();
            Q.pop();
            ListNode *w = adjacencias[v]->getInicio();
            while (w != NULL)
            {
                if (vertices[w->indice]->getMarcacao() == 0)
                {
                    vertices[w->indice]->marca(marcador);
                    desmarcados.erase(indices[w->indice]);
                    Q.push(w->indice);
                }
                w = w->prox;
            }
        }

        no = desmarcados.getInicio();
        if(!no) break;
        origem = no->indice;
        marcador++;
    }
}