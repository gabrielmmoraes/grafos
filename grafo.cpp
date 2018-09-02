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

Grafo::Grafo(){}

Grafo::~Grafo(){}

int Grafo::getGrauMin(){
    int min = n_vertices;
    int grau;

    for(int i=0; i<n_vertices;i++){
        grau = vertices[i]->getGrau();
        if(!grau) return grau;
        min = grau < min ? grau : min;
    }

    return min;
}

int Grafo::getGrauMax(){
    int max = 0;
    int grau;

    for(int i=0; i<n_vertices;i++){
        grau = vertices[i]->getGrau();
        if(grau==n_vertices-1) return grau;
        max = grau > max ? grau : max;
    }

    return max;
}

int Grafo::getGrauMedio(){
    int acum = 0;

    for(int i=0; i<n_vertices;i++)  acum+=vertices[i]->getGrau();    

    return acum/n_vertices;
}

int Grafo::getGrauMediano(){

}

Vertice** Grafo::getVertices(){
    return vertices;
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
        if(v1 > n_vertices || v2 > n_vertices) continue;
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

int MatrizAdjacencias::componentesConexos()
{
    Lista desmarcados;
    ListNode **indices = (ListNode **)malloc(sizeof(ListNode *) * n_vertices);
    ListNode *no;

    Lista tamanhos;
    int tamanho;

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
        tamanho = 1;
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
                        tamanho++;
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
        tamanhos.push(tamanho);
    }
    return marcador;
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
        if(v1 > n_vertices || v2 > n_vertices) continue;
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

    // Variável que auxiliar para guardar o nível de profundidade atual da DFS
    int nivel;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Preparando para executar DFS

    // For de inicialização do DFS
    for (i = 0; i < n_vertices; i++)
    {
        // Desmarcando todos os vértices
        vertices[i]->desmarca();

        // Aloca memória para uma tupla e guarda seu ponteiro na lista de tuplas
        listaTupla[i] = (Tupla *) malloc(sizeof(Tupla));

        // Inicializa a tupla definindo o vértice que ela corresponde como i
        // Ou seja, cada vértice tem sua tupla correspondente
        listaTupla[i]->vertice = i;
    }

    // Definindo o pai da origem do DFS como -1 (pois nenhum vértice o descobre)
    listaTupla[origem]->pai = -1;

    // Botando o ponteiro da tupla do vértice de origem no stack
    S.push(listaTupla[origem]);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // DFS

    // Enquanto houverem ponteiros no stack, executa DFS
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

            // Se o vértice for a origem, definir seu nível como 0. Do contrário seu nível é igual ao nível do pai + 1 
            nivel = vertices[tupla->vertice]->getPai() != -1 ? vertices[tupla->pai]->getNivel() + 1 : 0;
            vertices[tupla->vertice]->setNivel(nivel);

            // Marca o vértice sendo analisado
            vertices[tupla->vertice]->marca();

            // Criando um ponteiro para lista de adjacências e apontando-o para o final da lista
            // Assim garantimos que os elementos são postos do maior pro menor
            ListNode *w = adjacencias[tupla->vertice]->getFim();
            
            // Iterando sobre todos elementos da lista vizinhos e adicionando-os à pilha
            while (w != NULL)
            {
                // A tupla que será inserida à pilha (tupla de w->indice) guarda o vértice atual (tupla->vertice) como seu possível pai
                // Ele só será considerado o pai se ele estiver definido como possível pai de w->indice quando w->indice for tirado da pilha pela primeira vez
                listaTupla[w->indice]->pai = tupla->vertice;

                // Inserindo tupla do vizinho (w->indice) no stack
                S.push(listaTupla[w->indice]);

                // Próximo elemento da lista de adjacências a ser analisado é o elemento anterior ao w* atual
                w = w->prev;
            }
        }
    }
}

int ListaAdjacencias::componentesConexos()
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Declaração de variáveis

    // Criando lista de desmarcados
    // A classe Lista implementa uma lista duplamente encadeada (ListNode)
    Lista desmarcados;

    // Criando lista de ponteiros para elementos de uma lista duplamente encadeada
    ListNode **indices = (ListNode**) malloc(sizeof(ListNode*)*n_vertices);
    
    // Criando ponteiro para o elemento da lista encadeada a ser analisado no momento
    ListNode* no;

    // Declarando fila a ser usada no BFS
    queue<int> Q;

    // Variável marcador que diferencia a componente conexa que algoritmo está computando no momento
    int marcador = 1;

    // Variável que guarda o vértice de origem da BFS
    int origem;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Preparando para executar BFS

    for (int i = 0; i < n_vertices; i++)
    {
        vertices[i]->desmarca();
        no = desmarcados.push(i);
        indices[i] = no;
    }

    // Definindo origem da primeira iteração como vértice de índice 0
    origem = 0;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // BFS

    // Executar enquanto houver vértices desmarcados
    while (!desmarcados.vazia())
    {
        // Marcando o vértice sendo analisado
        vertices[origem]->marca(marcador);

        // Retirando o vértice sendo analisado da lista de desmarcados
        desmarcados.erase(indices[origem]);

        // Inserindo o vértice na fila
        Q.push(origem);

        // Declarando variável que guarda o topo da fila (vértice sendo analisado)
        int v;
        
        while (!Q.empty())
        {
            // Retirando topo da fila e guardando em uma variável para uso no algoritmo
            v = Q.front();

            // Retirando o primeiro elemento da fila (v)
            Q.pop();
            
            // Criando um ponteiro para lista de adjacências e apontando-o para o início da lista
            ListNode *w = adjacencias[v]->getInicio();
            
            // Enquanto houverem vizinhos, adicioná-los à fila
            while (w != NULL)
            {
                // Se o vértice não foi marcado (visitado)
                if (vertices[w->indice]->getMarcacao() == 0)
                {
                    // Marca-se o vértice
                    vertices[w->indice]->marca(marcador);
                    
                    // Retira o vértice da lista de desmarcados
                    desmarcados.erase(indices[w->indice]);
                    
                    // Insere o vértice na fila
                    Q.push(w->indice);
                }

                // Próximo elemento da lista de adjacências a ser analisado é o elemento posterior ao w* atual
                w = w->prox;
            }
        }

        // Pega o primeiro elemento da lista de desmarcados
        no = desmarcados.getInicio();

        // Se nó for igual a NULL, a lista está vazia
        // Com isso o algoritmo pode ser finalizado
        if(!no) break;

        // Próximo vértice a ser analizado é igual ao número guardado dentro da lista sendo apontada
        origem = no->indice;

        // Incrementando o identificador da componente conexa (pois achamos outra componente)
        marcador++;
    }

    // Retorna o número de componentes conexas
    return marcador;
}