#include "grafo.h"
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Tupla::Tupla(){}

Tupla::Tupla(int e1, int e2){
    elem1 = e1;
    elem2 = e2;
}

Tupla::~Tupla(){}

bool Tupla::operator>(Tupla t){
    return elem2 > t.elem2 ? elem2 : t.elem2;
}

bool Tupla::operator <(Tupla t){
    return elem2 < t.elem2 ? elem2 : t.elem2;
}

// Inicializa lista vazia
Lista::Lista()
{
    inicio = NULL;
    fim = NULL;
    tamanho = 0;
}

// Libera memória usada pela lista
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

// Se o ponteiro de início estiver em NULL, a lista está vazia
bool Lista::vazia()
{
    return inicio == NULL;
}

// Retorna tamanho da lista
int Lista::getTamanho(){
    return tamanho;
}

// Retorna ponteiro para o início da lista
ListNode *Lista::getInicio()
{
    return inicio;
}

// Retorna ponteiro para o fim da lista
ListNode *Lista::getFim()
{
    return fim;
}

// Inicializa um vértice
Vertice::Vertice()
{
    // Todo vértice possui grau zero até seus vizinhos serem analisador
    grau = 0;

    // O vértice começa desmarcado
    marcacao = 0;

    // Possíveis valores de pai:
    // -2 -> vértice ainda não descoberto
    // -1 -> vértice raiz de uma busca (descoberto mas não possui pai)
    // pai <= 0 -> índice do pai do vértice
    pai = -2;

    // Inicializando nível como -1
    nivel = -1;
}

// Retorna grau do vértice
int Vertice::getGrau()
{
    return grau;
}

// Retorna pai do vértice
int Vertice::getPai()
{
    return pai;
}

// Retorna nível do vértice
int Vertice::getNivel()
{
    return nivel;
}

// Retorna marcação  do vértice
// (Representa qual componente conexa ele faz parte)
int Vertice::getMarcacao()
{
    return marcacao;
}

// Incrementa o grau do vértice
void Vertice::incrementaGrau()
{
    grau++;
}

// Define pai do vértice
void Vertice::setPai(int v)
{
    pai = v;
}

// Define nível do vértice
void Vertice::setNivel(int n)
{
    nivel = n;
}

// Desmarca o vértice e retorna pai e nível para seus valores de inicialização
void Vertice::desmarca()
{
    marcacao = 0;
    pai = -2;
    nivel = -1;
}

// Marca o vértice com o identificador de sua componente conexa
void Vertice::marca(int i)
{
    marcacao = i;
}

// Construtor cria uma nova aresta apontando para dois vértices
Aresta::Aresta(int v1, int v2)
{
    v[0] = new Vertice();
    v[1] = new Vertice();
}

// Destrutor libera memória usada pelo array usado para criação de vértices
Aresta::~Aresta()
{
    free(v);
}

// Retorna um ponteiro para um vértice da aresta
Vertice *Aresta::getVertice(int v)
{
    return this->v[v - 1];
}

Grafo::Grafo(){}

Grafo::~Grafo(){}

// Retorna o grau mínimo do grafo
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

// Retorna o grau máximo do grafo
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

// Retorna o grau médio do grafo
float Grafo::getGrauMedio(){
    float acum = 0;

    for(int i=0; i<n_vertices;i++)  acum+=vertices[i]->getGrau();    

    return acum/n_vertices;
}

// Retorna o grau mediano do grafo
float Grafo::getGrauMediano(){
    vector<float> graus;
    for(int i = 0; i<n_vertices; i++){
        graus.push_back(vertices[i]->getGrau());
    }

    sort(graus.begin(), graus.end());

    return n_vertices % 2 == 1 ? graus[n_vertices/2] : (graus[n_vertices/2] + graus[n_vertices/2 + 1]) / 2;
}


// Retorna lista de ponteiros para os vértices do grafo
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

// Constrói uma matriz de adjacência a partir da descrição de um grafo dentro de um arquivo
MatrizAdjacencias::MatrizAdjacencias(FILE *input)
{
    // Lê a primeira linha do programa e guarda o inteiro como o número de vértices total
    fscanf(input, "%d", &n_vertices);

    // Inicializa o número de arestas como 0    
    n_arestas = 0;

    // Cria uma lista de ponteiros para elementos de classe Vertice (tamanho n_vertices)
    // Com isso conseguimos guardar características de cada vértice
    vertices = (Vertice **)malloc(sizeof(Vertice *) * n_vertices);
    
    // Cria uma lista de ponteiros para listas, simulando uma matriz de tamanho n_vertice^2
    // Com isso conseguimos acessar a relação entre dois vértices em tempo O(1)
    adjacencias = (int **)malloc(sizeof(int *) * n_vertices);
    
    // Para cada n_vertice, inicializa-se uma classe Vertice e uma linha da matriz de tamanho n_vertice
    for (int i = 0; i < n_vertices; i++)
    {
        // Criando novo vértice e retornando seu ponteiro à lista de ponteiros para Vertices
        vertices[i] = new Vertice();

        // Cria linha da matriz com tamanho n_vertices e as iniciliza com valor 0
        adjacencias[i] = (int *)calloc(n_vertices, sizeof(int));
    }

    // Declaração de duas variáveis auxiliares para guardarem os vértices que serão fornecidos pela linha sendo
    // lida no arquivo
    int v1, v2;

    // Loop de leitura de linhas do arquivo que termina quando recebe EOF (End Of File)
    while (fscanf(input, "%d %d", &v1, &v2) != EOF)
    {
        // Se o índice de qualquer um dos vértices na linha lida for maior que o n_vertice, descarta-se a informação
        // e segue a próxima iteração do loop (pŕoxima linha)
        if(v1 > n_vertices || v2 > n_vertices) continue;

        // Caso a condição acima não seja satisfeita, define-se adjacência simétrica entre os dois vértices
        setAdjacencia(v1, v2);

        // Após processar informações da aresta, incrementa-se o valor total de n_arestas
        n_arestas++;
    }
}


// Destrutor da Matriz de Adjacência. Libera o espaço de memória usado pela matriz e pela lista de vértices
MatrizAdjacencias::~MatrizAdjacencias()
{
    // Libera a memória da lista de vértices
    free(vertices);

    // Libera a memória de cada linha da matriz
    for (int i = 0; i < n_vertices; i++) free(adjacencias[i]);
    
    // Libera a memória da lista de ponteiros para as linhas da matriz
    free(adjacencias);
}


// Retorna o número de vértices do grafo
int MatrizAdjacencias::getNVertices()
{
    return n_vertices;
}


// Retorna o número de arestas do grafo
int MatrizAdjacencias::getNArestas()
{
    return n_arestas;
}

// Define adjacência entre dois vértices
void MatrizAdjacencias::setAdjacencia(int v1, int v2)
{
    // Define o vértice v2 como vizinho de v1
    adjacencias[v1 - 1][v2 - 1] = 1;

    // Define o vértice v1 como vizinho de v2
    adjacencias[v2 - 1][v1 - 1] = 1;

    // Considerando que agora v1 possui um vizinho a mais, incrementa-se seu grau
    vertices[v1 - 1]->incrementaGrau();

    // Considerando que agora v2 possui um vizinho a mais, incrementa-se seu grau
    vertices[v2 - 1]->incrementaGrau();
}

// Busca em largura a partir de um vértice origem, retorna o maior nível
int MatrizAdjacencias::BFS(int origem)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Declaração de variáveis locais

    // Declaração da fila que será usada para selecionar próximo vértice
    queue<int> Q;
    
    // Variável auxiliar que guarda o nível do vértice atual    
    int nivel;

    // Variável que guarda o vértice sendo analizado no momento dentro do BFS
    int verticeAtual;
    
    // Variável iterável do for
    int i;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Preparando para executar BFS

    for (i = 0; i < n_vertices; i++)
    {
        // Desmarcando todos os vértices
        vertices[i]->desmarca();
    }

    // Marcando vértice inicial como visitado
    vertices[origem]->marca();

    // Inserindo vértice na fila
    Q.push(origem);

    // Definindo o nível da raiz do BFS como 0 e seu pai como -1
    vertices[origem]->setNivel(0);
    vertices[origem]->setPai(-1);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // BFS
    int maiornivel = 0;
    while (!Q.empty())
    {
        // Definindo vértice atual como topo da fila
        verticeAtual = Q.front();

        // Retirando a cabeça da fila
        Q.pop();

        for (i = 0; i < n_vertices; i++)
        {
            // Checa se i é vizinho de verticeAtual
            if (adjacencias[verticeAtual][i])
            {
                // Checa se o vértice já foi marcado
                if (vertices[i]->getMarcacao() == 0)
                {
                    // Marca o vértice
                    vertices[i]->marca();

                    // Define o nível como o nível do pai (verticeAtual) + 1
                    nivel = vertices[verticeAtual]->getNivel() + 1;
                    maiornivel = nivel>maiornivel?nivel:maiornivel;
                    vertices[i]->setNivel(nivel);

                    // Define o pai como o verticeAtual
                    vertices[i]->setPai(verticeAtual);

                    // Insere i na fila
                    Q.push(i);
                }
            }
        }
    }
    return maiornivel;
}

// Busca em profundidade a partir de um vértice origem
void MatrizAdjacencias::DFS(int origem)
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

    // Variável auxiliar para guardar o nível de profundidade atual da DFS
    int nivel;

    // Declarando variável que guarda o topo da fila (vértice sendo analisado no BFS)
    int verticeAtual;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Preparando para executar DFS

    // For de inicialização do DFS
    for (int i = 0; i < n_vertices; i++)
    {
        // Desmarcando todos os vértices
        vertices[i]->desmarca();

        // Aloca memória para uma tupla e guarda seu ponteiro na lista de tuplas
        listaTupla[i] = (Tupla *)malloc(sizeof(Tupla));

        // Inicializa a tupla definindo o vértice que ela corresponde como i
        // Ou seja, cada vértice tem sua tupla correspondente
        listaTupla[i]->elem1 = i;
    }
    
    // Definindo o pai da origem do DFS como -1 (pois nenhum vértice o descobre)
    listaTupla[origem]->elem2 = -1;

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

        // Definindo vértice atual como índice gaurdado na tupla ao topo da pilha
        verticeAtual = tupla->elem1;

        // Se vértice ainda não foi marcado, realizar busca dentro dele
        if (vertices[verticeAtual]->getMarcacao() == 0)
        {
            // O pai é o vértice que botou a tupla na pilha mais recentemente
            // Se o pai ainda não foi definido, então o último vértice a botar verticeAtual na pilha é o pai
            // do verticeAtual
            vertices[verticeAtual]->setPai(tupla->elem2);

            // Se o vértice for a origem, definir seu nível como 0. Do contrário seu nível é igual ao nível do pai + 1 
            nivel = vertices[verticeAtual]->getPai() != -1 ? vertices[tupla->elem2]->getNivel() + 1 : 0;
            vertices[verticeAtual]->setNivel(nivel);
            
            // Marca o vértice sendo analisado
            vertices[verticeAtual]->marca();

            // Loop para checar vizinhos
            for (i = n_vertices - 1; i >= 0; i--)
            {
                // Checa se há conexão entre verticeAtual e i
                if (adjacencias[verticeAtual][i])
                {
                    // A tupla que será inserida à pilha (tupla do i) guarda o verticeAtual como seu possível pai
                    // Ele só será considerado o pai se ele estiver definido como possível pai de i quando i for
                    // retirado da pilha pela primeira vez
                    listaTupla[i]->elem2 = verticeAtual;

                    // Inserindo tupla de i no stack
                    S.push(listaTupla[i]);
                }
            }
        }
    }
}

//Calcula a maior distância no grafo. Retorna -1 se o grafo não or conexo
int MatrizAdjacencias::diametro(){
    int diametro = 0;
    int tmp;
    if(componentesConexos().size()>1) return -1;

    for(int i=0;i<n_vertices;i++){
        tmp = BFS(i);
        diametro = tmp>diametro?tmp:diametro;
    }

    return diametro;
}

// Função que percorre todas componentes conexas do grafo e retorna um vetor que associa cada CC ao seu tamanho
vector<Tupla> MatrizAdjacencias::componentesConexos()
{
    Tupla t;
    Lista desmarcados;
    ListNode **indices = (ListNode **)malloc(sizeof(ListNode *) * n_vertices);
    ListNode *no;

    vector<Tupla> tamanhos;
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

        // Guardando identificador da componente conexa na tupla
        t.elem1 = marcador;

        // Guardando tamanha da componente conexa na tupla
        t.elem2 = tamanho;
        
        // Inserindo tupla no final do vetor
        tamanhos.push_back(t);

        no = desmarcados.getInicio();
        if(!no) break;
        origem = no->indice;
        marcador++;
    }
    return tamanhos;
}

//Função para analisar as componentes conexas com relação a tamanho e elementos que as formam
Lista** MatrizAdjacencias::analiseComponentesConexos()
{
    Tupla t;
    vector<Tupla> ccs = componentesConexos();
    Lista** componentesConexas = (Lista**) malloc(sizeof(Lista*) * ccs.size()) ;
    int c = 0;

    make_heap(ccs.begin(),ccs.end());
    
    while(!ccs.empty()){
    
        t = ccs.front();
        pop_heap(ccs.begin(),ccs.end());
        ccs.pop_back();
    
        componentesConexas[c] = new Lista();
        componentesConexas[c]->push(t.elem1);

        printf("Componente conexa %d:\n",t.elem1);
        for(int i=0;i<n_vertices;i++){
            if(vertices[i]->getMarcacao()==t.elem1){
                componentesConexas[c]->push(i);
                printf("Vértice %d\n",i+1);
            }
        }
        sort_heap(ccs.begin(),ccs.end());
        c++;
    }

    return componentesConexas;
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

// Constrói uma lista de adjacência a partir da descrição de um grafo dentro de um arquivo
ListaAdjacencias::ListaAdjacencias(FILE *input)
{
    // Lê a primeira linha do programa e guarda o inteiro como o número de vértices total
    fscanf(input, "%d", &n_vertices);

    // Inicializa o número de arestas como 0
    n_arestas = 0;

    // Cria uma lista de ponteiros para elementos de classe Vertice (tamanho n_vertices)
    // Com isso conseguimos guardar características de cada vértice
    vertices = (Vertice **)malloc(sizeof(Vertice *) * n_vertices);

    // Cria uma lista de ponteiros para elementos de classe Lista (tamanho n_vertices))
    // Com isso conseguimos gaurdar listas encadeadas para vizinhos de cada vértice
    adjacencias = (Lista **)malloc(sizeof(Lista *) * n_vertices);
    
    // Para cada n_vertice, inicializa-se uma classe Vertice e uma Lista para gaurdar seus vizinhos
    for (int i = 0; i < n_vertices; i++)
    {
        // Criando novo vértice e retornando seu ponteiro à lista de ponteiros para Vertices
        vertices[i] = new Vertice();

        // Criando nova listae retornando seu ponteiro à lista de ponteiros para Listas de Adjacências
        adjacencias[i] = new Lista();
    }

    // Declaração de duas variáveis auxiliares para guardarem os vértices que serão fornecidos pela linha sendo
    // lida no arquivo
    int v1, v2;

    // Loop de leitura de linhas do arquivo que termina quando recebe EOF (End Of File)
    while (fscanf(input, "%d %d", &v1, &v2) != EOF)
    {
        // Se o índice de qualquer um dos vértices na linha lida for maior que o n_vertice, descarta-se a informação
        // e segue a próxima iteração do loop (pŕoxima linha)
        if(v1 > n_vertices || v2 > n_vertices) continue;

        // Caso a condição acima não seja satisfeita, define-se adjacência simétrica entre os dois vértices
        setAdjacencia(v1, v2);

        // Após processar informações da aresta, incrementa-se o valor total de n_arestas
        n_arestas++;
    }
}

// Destrutor da Lista de Adjacencias. Libera a memória usada pelo array de vértices e pela própria lista
ListaAdjacencias::~ListaAdjacencias()
{
    free(vertices);
    free(adjacencias);
}

// Retorna número de vértices do grafo
int ListaAdjacencias::getNVertices()
{
    return n_vertices;
}

// Retorna número de arestas do grafo
int ListaAdjacencias::getNArestas()
{
    return n_arestas;
}

// Define adjacência entre dois vértices
void ListaAdjacencias::setAdjacencia(int v1, int v2)
{
    // Adiciona o vértice v2 como vizinho de v1
    adjacencias[v1 - 1]->push(v2 - 1);

    // Adiciona v1 como vizinho de v2
    adjacencias[v2 - 1]->push(v1 - 1);

    // Considerando que agora v1 possui um vizinho a mais, incrementa-se seu grau
    vertices[v1 - 1]->incrementaGrau();

    // Considerando que agora v2 possui um vizinho a mais, incrementa-se seu grau
    vertices[v2 - 1]->incrementaGrau();
}

// Busca em largura a partir de um vértice origem
int ListaAdjacencias::BFS(int origem)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Declaração de variáveis locais

    // Variável que guarda o vértice sendo analizado no momento dentro do BFS
    int verticeAtual;

    // Variável auxiliar para acessar pListaAdjacencias->indice
    int verticeVizinho;

    // Declaração da fila que será usada para selecionar próximo vértice
    queue<int> Q;

    // Variável auxiliar que guarda o nível do vértice atual
    int nivel;

    // Declarando ponteiro para percorrer a lista de adjacência
    ListNode* pListaAdjacencias;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Preparando para executar BFS

    for (int i = 0; i < n_vertices; i++)
    {
        // Desmarcando todos os vértices
        vertices[i]->desmarca();
    }

    // Marcando vértice inicial como visitado
    vertices[origem]->marca();

    // Inserindo vértice na fila
    Q.push(origem);

    // Definindo o nível da raiz do BFS como 0 e seu pai como -1
    vertices[origem]->setNivel(0);
    vertices[origem]->setPai(-1);
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // BFS

    // Enquanto existirem vértices na fila, executar BFS
    int maiornivel = 0;
    while (!Q.empty())
    {
        // Definindo vértice atual como topo da fila
        verticeAtual = Q.front();
        
        // Retirando a cabeça da fila
        Q.pop();

        // Apontando pListaAdjacencias para o início da lista de adjacência
        pListaAdjacencias = adjacencias[verticeAtual]->getInicio();
        
        // Executar até percorrer todos os vértices vizinhos
        while (pListaAdjacencias != NULL)
        {
            // Definindo vértice vizinho a ser analisado como índice guardado no elemento da lista de adjacência
            // sendo apontado no momento
            verticeVizinho = pListaAdjacencias->indice;

            // Se o vértice apontado por pListaAdjacencias não estiver marcado, continuar
            if (vertices[verticeVizinho]->getMarcacao() == 0)
            {
                // Marca o vértice vizinho sendo analisado
                vertices[verticeVizinho]->marca();

                // Seta seu nível como o nivel de seu pai (v) + 1
                nivel = vertices[verticeAtual]->getNivel() + 1;
                maiornivel = nivel>maiornivel?nivel:maiornivel;
                vertices[verticeVizinho]->setNivel(nivel);

                // O pai do vizinho sendo analisado é igual ao vértice que saiu da fila mais recentemente
                vertices[verticeVizinho]->setPai(verticeAtual);

                // Adiciona o vizinho na fila
                Q.push(verticeVizinho);
            }

            // Define o ponteiro para o próximo vizinho a ser analizado
            pListaAdjacencias = pListaAdjacencias->prox;
        }
    }
    return maiornivel;
}

// Busca em profundidade a partir de um vértice origem
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

    // Variável auxiliar para guardar o nível de profundidade atual da DFS
    int nivel;

    // Declarando variável que guarda o topo da fila (vértice sendo analisado no BFS)
    int verticeAtual;

    // Variável auxiliar para acessar pListaAdjacencias->indice
    int verticeVizinho;

    // Declarando ponteiro para percorrer a lista de adjacência
    ListNode* pListaAdjacencias;

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
        listaTupla[i]->elem1 = i;
    }

    // Definindo o pai da origem do DFS como -1 (pois nenhum vértice o descobre)
    listaTupla[origem]->elem2 = -1;

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

        // Definindo vértice atual como índice gaurdado na tupla ao topo da pilha
        verticeAtual = tupla->elem1;

        // Se vértice ainda não foi marcado, realizar busca dentro dele
        if (vertices[verticeAtual]->getMarcacao() == 0)
        {
            // O pai é o vértice que botou a tupla na pilha mais recentemente
            // Se o pai ainda não foi definido, então o último vértice a botar tupla->vertice na pilha é o pai de tupla->vertice
            vertices[verticeAtual]->setPai(tupla->elem2);

            // Se o vértice for a origem, definir seu nível como 0. Do contrário seu nível é igual ao nível do pai + 1 
            nivel = vertices[verticeAtual]->getPai() != -1 ? vertices[tupla->elem2]->getNivel() + 1 : 0;
            vertices[verticeAtual]->setNivel(nivel);

            // Marca o vértice sendo analisado
            vertices[verticeAtual]->marca();

            // Apontando o ponteiro da lista de adjacências para o final da lista
            // Assim garantimos que os elementos são postos do maior pro menor
            pListaAdjacencias = adjacencias[verticeAtual]->getFim();
            
            // Iterando sobre todos elementos da lista vizinhos e adicionando-os à pilha
            while (pListaAdjacencias != NULL)
            {
                // Definindo vértice vizinho a ser analisado como índice guardado no elemento da lista de adjacência
                // sendo apontado no momento
                verticeVizinho = pListaAdjacencias->indice;

                // A tupla que será inserida à pilha (tupla do vérticeVizinho) guarda o verticeAtual como seu possível pai
                // Ele só será considerado o pai se ele estiver definido como possível pai de verticeVizinho quando verticeVizinho for
                // retirado da pilha pela primeira vez
                listaTupla[verticeVizinho]->elem2 = verticeAtual;

                // Inserindo tupla do verticeVizinho no stack
                S.push(listaTupla[verticeVizinho]);

                // Próximo elemento da lista de adjacências a ser analisado é o elemento anterior ao apontado no momento
                pListaAdjacencias = pListaAdjacencias->prev;
            }
        }
    }
}

//Calcula a maior distância no grafo. Retorna -1 se o grafo não or conexo
int ListaAdjacencias::diametro(){
    int diametro = 0;
    int tmp;
    if(componentesConexos().size()>1) return -1;

    for(int i=0;i<n_vertices;i++){
        tmp = BFS(i);
        diametro = tmp>diametro?tmp:diametro;
    }

    return diametro;
}

// Função que percorre todas componentes conexas do grafo e retorna a quantidade de CCs
vector<Tupla> ListaAdjacencias::componentesConexos()
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Declaração de variáveis

    // Criando lista de desmarcados
    // A classe Lista implementa uma lista duplamente encadeada (ListNode)    
    Lista desmarcados;


    Tupla t;
    vector<Tupla> tamanhos;
    int tamanho;


    // Criando lista de ponteiros para elementos de uma lista duplamente encadeada
    ListNode **indices = (ListNode**) malloc(sizeof(ListNode*)*n_vertices);
    
    // Criando ponteiro para o elemento da lista encadeada a ser analisado no momento
    ListNode* no;

    // Declarando ponteiro para percorrer a lista de adjacência    
    ListNode* pListaAdjacencias;

    // Declarando fila a ser usada no BFS
    queue<int> Q;

    // Variável marcador que diferencia a componente conexa que algoritmo está computando no momento
    int marcador = 1;

    // Variável que guarda o vértice de origem da BFS
    int origem;

    // Declarando variável que guarda o topo da fila (vértice sendo analisado no BFS)
    int verticeAtual;

    // Variável auxiliar para acessar pListaAdjacencias->indice
    int verticeVizinho;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Preparando para executar BFS

    for (int i = 0; i < n_vertices; i++)
    {
        // Desmarcando todos os vértices
        vertices[i]->desmarca();

        // Inserindo vértice desmarcado na lista de desmarcados e retornando um ponteiro para o elemento adicionado
        no = desmarcados.push(i);
        
        // Inserindo ponteiro ao elemento adicionado para lista de ponteiros
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

        // Inicializando tamanho da componente conexa como 1
        tamanho = 1;
        
        // Retirando o vértice sendo analisado da lista de desmarcados
        desmarcados.erase(indices[origem]);

        // Inserindo o vértice na fila
        Q.push(origem);
        
        while (!Q.empty())
        {
            // Retirando topo da fila e guardando em uma variável para uso no algoritmo
            verticeAtual = Q.front();

            // Retirando o primeiro elemento da fila (v)
            Q.pop();
            
            // Criando um ponteiro para lista de adjacências e apontando-o para o início da lista
            pListaAdjacencias = adjacencias[verticeAtual]->getInicio();
            
            // Enquanto houverem vizinhos, adicioná-los à fila
            while (pListaAdjacencias != NULL)
            {
                // Definindo vértice vizinho a ser analisado como índice guardado no elemento da lista de adjacência
                // sendo apontado no momento
                verticeVizinho = pListaAdjacencias->indice;

                // Se o vértice não foi marcado (visitado)
                if (vertices[verticeVizinho]->getMarcacao() == 0)
                {
                    // Marca-se o vértice
                    vertices[verticeVizinho]->marca(marcador);

                    // Incrementando tamanho da componente conexa
                    tamanho++;
                    
                    // Retira o vértice da lista de desmarcados
                    desmarcados.erase(indices[verticeVizinho]);
                    
                    // Insere o vértice na fila
                    Q.push(verticeVizinho);
                }

                // Próximo elemento da lista de adjacências a ser analisado é o elemento posterior ao w* atual
                pListaAdjacencias = pListaAdjacencias->prox;
            }
        }

        // Guardando identificador da componente conexa na tupla
        t.elem1 = marcador;

        // Guardando tamanha da componente conexa na tupla
        t.elem2 = tamanho;
        
        // Inserindo tupla no final do vetor
        tamanhos.push_back(t);

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
    return tamanhos;
}

//Função para analisar as componentes conexas com relação a tamanho e elementos que as formam
Lista** ListaAdjacencias::analiseComponentesConexos()
{
    Tupla t;
    vector<Tupla> ccs = componentesConexos();
    Lista** componentesConexas = (Lista**) malloc(sizeof(Lista*) * ccs.size()) ;
    int c = 0;

    make_heap(ccs.begin(),ccs.end());
    
    while(!ccs.empty()){
    
        t = ccs.front();
        pop_heap(ccs.begin(),ccs.end());
        ccs.pop_back();
    
        componentesConexas[c] = new Lista();
        componentesConexas[c]->push(t.elem1);

        for(int i=0;i<n_vertices;i++){
            if(vertices[i]->getMarcacao()==t.elem1){
                componentesConexas[c]->push(i);
            }
        }
        sort_heap(ccs.begin(),ccs.end());
        c++;
    }

    return componentesConexas;
}