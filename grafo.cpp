#include "grafo.h"
#include "heap.h"
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

template <class num1, class num2>
struct greater1{
  bool operator()(Tupla<num1, num2>& a,Tupla<num1, num2>& b) const{
    return a>b;
  }
}; 

// Inicializa um vértice
Vertice::Vertice(float x, float y)
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

    //Inicializando posição com os argumentos passados (padrão na origem do plano cartesiano)
    pos_x = x;
    pos_y = y;
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

//Retorna posição do vértice no eixo x
float Vertice::getPosX()
{
    return pos_x;
}

//Retorna posição do vértice no eixo y
float Vertice::getPosY()
{
    return pos_y;
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

//Define posição do vértice
void Vertice::setPos(float x, float y)
{
    pos_x = x;
    pos_y = y;
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
int Grafo::getGrauMin()
{
    // Variável que armazena o menor valor encontrado
    // Inicializada como n_vertices, pois nenhum vértice terá grau maior do que n_vertices - 1
    int min = n_vertices;

    // Variável auxiliar para armazenar o grau do vértice sendo analisado
    int grau;

    // Loop para cada vértice
    for(int i=0; i<n_vertices;i++)
    {
        // Grau recebe o grau do vértice sendo analisado
        grau = vertices[i]->getGrau();

        // Se grau for igual a zero, temos o grau mínimo
        if(!grau) return grau;

        // Se grau for menor que o grau mínimo achado até o momento, atribuímos grau à variável min
        min = grau < min ? grau : min;
    }

    // Retorna menor variável encontrada até o momento
    return min;
}

// Retorna o grau máximo do grafo
int Grafo::getGrauMax()
{
    // Variável que armazena maior valor encontrado
    int max = 0;

    // Variável auxiliar para armazenar o grau do vértice sendo analisado
    int grau;

    // Loop para cada vértice
    for(int i=0; i<n_vertices;i++)
    {
        // Grau recebe o grau do vértice sendo analisado
        grau = vertices[i]->getGrau();

        // Se grau for igual a n_vertices - 1, temos o maior grau possível do grafo
        if(grau==n_vertices-1) return grau;

        // Se grau for maior que max, atribui-se o valor de grau a max
        max = grau > max ? grau : max;
    }

    // Retorna maior grau encontrado
    return max;
}

// Retorna o grau médio do grafo
float Grafo::getGrauMedio()
{
    // Variável auxiliar para armazenar soma dos graus
    float acum = 0;

    // Para cada vértice, soma-se seu grau ao acumulador
    for(int i=0; i<n_vertices;i++)  acum+=vertices[i]->getGrau();    

    // Retorna o valor do acumulador dividido pelo número de vértices
    return acum/n_vertices;
}

// Retorna o grau mediano do grafo
float Grafo::getGrauMediano()
{

    // Cria vetor de floats para armazenar graus de cada vértice
    // É inicializado como float para facilitar o cálculo da mediana
    vector<float> graus;

    // Para cada vértice, inserimos seu grau no vetor
    for(int i = 0; i<n_vertices; i++){
        graus.push_back(vertices[i]->getGrau());
    }

    // Sort de complexidade nlogn realizado no vetor de graus
    sort(graus.begin(), graus.end());

    // Retorna a mediana do vetor
    // Considerando o caso em que n_vertices é par (média dos dois elementos centrais)
    // ou ímpar (valor do elemento central)
    return n_vertices % 2 == 1 ? graus[n_vertices/2] : (graus[n_vertices/2] + graus[n_vertices/2 + 1]) / 2;
}

// Retorna lista de ponteiros para os vértices do grafo
Vertice** Grafo::getVertices()
{
    return vertices;
}

// Construtor de matriz de adjacência a partir de um número de vértices
// Ainda é preciso chamar setAdjacencia pela main a fim de criar as arestas e relações entre vértices
MatrizAdjacencias::MatrizAdjacencias(int n, bool p)
{
    // Define n_vertices como o argumento passado
    n_vertices = n;

    // Inicializa n_arestas como 0
    n_arestas = 0;

    // Inicializa a flag de peso com o argumento passado
    peso = p;

    // Inicializa a flag de pesos negativos como falsa
    pesos_negativos = false;

    // Alocação de memória para lista de ponteiros para vértices e lista de adjacência
    vertices = (Vertice **)malloc(sizeof(Vertice *) * n_vertices);
    adjacencias = (float **)malloc(sizeof(float *) * n_vertices);
    
    // Para cada n_vertice, inicializa-se uma classe Vertice aloca-se memória para uma linha da matriz
    for (int i = 0; i < n_vertices; i++)
    {
        // Criando novo vértice e retornando seu ponteiro à lista de ponteiros para Vertices
        vertices[i] = new Vertice();

        // Alocando memória para uma linha da matriz de tamanho n_vertices
        adjacencias[i] = (float *)malloc(sizeof(float) * n_vertices);

        // Inicializando linha como 0
        for (int j = 0; j < n_vertices; j++)
        {
            adjacencias[i][j] = 0;
        }
    }
}

// Constrói uma matriz de adjacências a partir de um arquivo com pontos pertencentes a um plano
MatrizAdjacencias::MatrizAdjacencias(FILE *pontos)
{
    // Lê a primeira linha do programa e guarda o inteiro como o número de vértices total
    fscanf(pontos, "%d", &n_vertices);

    // Inicializa o número de arestas como 0    
    n_arestas = 0;

    // Inicializa a flag de peso como true
    peso = true;

    // Inicializa a flag de pesos negativos como falsa
    pesos_negativos = false;

    // Cria uma lista de ponteiros para elementos de classe Vertice (tamanho n_vertices)
    // Com isso conseguimos guardar características de cada vértice
    vertices = (Vertice **)malloc(sizeof(Vertice *) * n_vertices);
    
    // Cria uma lista de ponteiros para listas, simulando uma matriz de tamanho n_vertice^2
    // Com isso conseguimos acessar a relação entre dois vértices em tempo O(1)
    adjacencias = (float **)malloc(sizeof(float *) * n_vertices);
    
    // Declaração das coordenadas que serão lidas do arquivo
    float x,y;

    // Para cada n_vertice, inicializa-se uma classe Vertice e uma linha da matriz de tamanho n_vertice
    for (int i = 0; i < n_vertices; i++)
    {
        fscanf(pontos, "%f %f", &x, &y);
        // Criando novo vértice e retornando seu ponteiro à lista de ponteiros para Vertices
        vertices[i] = new Vertice(x,y);
    }

    float dist;
    // Define os pesos de todas as arestas
    for (int i = 0; i < n_vertices; i++)
    {
        // Cria linha da matriz com tamanho n_vertices
        adjacencias[i] = (float *)malloc(sizeof(float)*n_vertices);
        for (int j = 0; j < n_vertices; j++)
        {
            // Calcula a distância entre i e j
            x = (vertices[i]->getPosX()-vertices[j]->getPosX());
            y = (vertices[i]->getPosY()-vertices[j]->getPosY());
            x *= x;
            y *= y;
            dist = sqrt(x+y);

            // Define o peso da aresta como essa distância
            setAdjacencia(i+1,j+1,dist);
        }
    
    }
}

// Constrói uma matriz de adjacência a partir da descrição de um grafo dentro de um arquivo
MatrizAdjacencias::MatrizAdjacencias(FILE *input, bool p)
{
    // Lê a primeira linha do programa e guarda o inteiro como o número de vértices total
    fscanf(input, "%d", &n_vertices);

    // Inicializa o número de arestas como 0    
    n_arestas = 0;

    // Inicializa a flag de peso com o argumento passado
    peso = p;

    // Inicializa a flag de pesos negativos como falsa
    pesos_negativos = false;

    // Cria uma lista de ponteiros para elementos de classe Vertice (tamanho n_vertices)
    // Com isso conseguimos guardar características de cada vértice
    vertices = (Vertice **)malloc(sizeof(Vertice *) * n_vertices);
    
    // Cria uma lista de ponteiros para listas, simulando uma matriz de tamanho n_vertice^2
    // Com isso conseguimos acessar a relação entre dois vértices em tempo O(1)
    adjacencias = (float **)malloc(sizeof(float *) * n_vertices);
    
    // Para cada n_vertice, inicializa-se uma classe Vertice e uma linha da matriz de tamanho n_vertice
    for (int i = 0; i < n_vertices; i++)
    {
        // Criando novo vértice e retornando seu ponteiro à lista de ponteiros para Vertices
        vertices[i] = new Vertice();

        // Cria linha da matriz com tamanho n_vertices e as iniciliza com valor 0
        adjacencias[i] = (float *)calloc(n_vertices, sizeof(float));
    }

    // Declaração de duas variáveis auxiliares para guardarem os vértices que serão fornecidos pela linha sendo
    // lida no arquivo
    int v1, v2;
    float w = 1;
    int leitura = 1;

    // Loop de leitura de linhas do arquivo que termina quando recebe EOF (End Of File)
    while (true)
    {
        if(p) leitura = fscanf(input, "%d %d %f", &v1, &v2, &w);
        
        else leitura = fscanf(input, "%d %d", &v1, &v2);

        if(leitura == EOF) break;
        // Se o índice de qualquer um dos vértices na linha lida for maior que o n_vertice, descarta-se a informação
        // e segue a próxima iteração do loop (pŕoxima linha)
        if(v1 > n_vertices || v2 > n_vertices) continue;

        // Caso a condição acima não seja satisfeita, define-se adjacência simétrica entre os dois vértices
        setAdjacencia(v1, v2, w);
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
void MatrizAdjacencias::setAdjacencia(int v1, int v2, float w)
{
    //Se o peso da nova aresta for negativa, muda a flag de pesos negativos para refletir isso
    if(w<0) pesos_negativos = true;

    // Define o vértice v2 como vizinho de v1
    adjacencias[v1 - 1][v2 - 1] = w;

    // Define o vértice v1 como vizinho de v2
    adjacencias[v2 - 1][v1 - 1] = w;

    // Considerando que agora v1 possui um vizinho a mais, incrementa-se seu grau
    vertices[v1 - 1]->incrementaGrau();

    // Considerando que agora v2 possui um vizinho a mais, incrementa-se seu grau
    vertices[v2 - 1]->incrementaGrau();

    n_arestas++;
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
    Tupla<int, int> **listaTupla = (Tupla<int, int> **)malloc(sizeof(Tupla<int, int> *) * n_vertices);

    // Criando stack de ponteiros para tuplas
    stack<Tupla<int, int> *> S;


    // Criando variável iterável do DFS
    Tupla<int, int> *tupla;

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
        listaTupla[i] = (Tupla<int, int> *)malloc(sizeof(Tupla<int, int>));

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

    // Loop para liberar todas as tuplas apontadas pelos ponteiros de listaTupla
    for (i = 0; i < n_vertices; i++)
    {
        free(listaTupla[i]);
    }

    // Libera memória da listaTupla
    free(listaTupla);
}

// Algoritmo de caminho mínimo entre origem e destino em grafos com pesos
// Retorna um vetor de distâncias em que o último elemento guarda todas as distâncias acumuladas
// Se o destino for -1, calcula a menor distância a partir da origem para todo o grafo
float* MatrizAdjacencias::Dijkstra(int origem, int destino){

    // Se há pesos negativos
    if(pesos_negativos){
        // Informa o usuário e termina a função
        printf("Não é possível utilizar o algoritmo de Dijkstra com pesos negativos.\n");
        return NULL; 
    }

    // Aloca memória para vetor de distâncias
    float* dist = (float*) malloc(sizeof(float)*n_vertices);

    // Define acumulador de distâncias
    float dist_acum = 0;

    // Aloca memória para vetor de pais temporários
    int* pai = (int*) malloc(sizeof(int*)*n_vertices);

    // Varíavel para nível inicial
    int nivel = 0;

    Heap h(n_vertices, false);

    // Tupla temporária
    Tupla<int, float>* t;

    // Varíavel temporária para peso a aresta analisada
    int peso;

    // Para todos os vértices
    for(int i=0;i<n_vertices;i++){

        t = (Tupla<int,float>*) malloc(sizeof(Tupla<int,float>));

        // Tupla recebe o índice do vértice
        t->elem1 = i;
        // E a distância inicial infinita
        t->elem2 = INFINITY;
        // Tupla adicionada no vector
        h.insert(t);
        // Distancia inicial infinita
        dist[i] = INFINITY;
        // Inicialmente nenhum vértice tem pai
        pai[i] = -2;
    }

    // Define distância da origem como 0 no vetor e na base da heap
    dist[origem] = 0;
    Tupla<int,float> t_origem(origem, 0);

    int index_origem = h.getIndex(&t_origem);
    h.change(index_origem, 0);
    
    // Define pai temporário da origem na árvore geradora
    pai[origem] = -1;

    // Enquanto há vértices a serem explorados
    while(!h.empty()){

        // t é o vértice restante com menor distância até a origem no momento
        t = h.extract();

        // Adiciona distância do vértice selecionado ao acumulador de distâncias
        dist_acum += dist[t->elem1]!=INFINITY?dist[t->elem1]:0; 

        // Define pai e nível do vértice selecionado na árvore geradora
        vertices[t->elem1]->setPai(pai[t->elem1]);
        if(pai[t->elem1]>0) nivel = vertices[pai[t->elem1]]->getNivel()+1;                
        vertices[t->elem1]->setNivel(nivel);

        // Se o destino foi atingido, interrompe o loop
        if(t->elem1 == destino) break;
        
        // Percorre a matriz de adjacencias
        for(int vizinho=0;vizinho<n_vertices;vizinho++){

            peso = adjacencias[t->elem1][vizinho];
            // Se o vizinho é realmente vizinho de t
            if(peso != 0){

                // Se a distância do vizinho a origem for maior que a distância do vértice mais o peso da aresta
                if(dist[vizinho] > dist[t->elem1] + peso){

                    // Define index do vizinho na heap
                    int i;
                    
                    Tupla<int,float> t_vizinho(vizinho, 0);

                    i = h.getIndex(&t_vizinho);

                    // Se o vizinho ainda está na heap
                    if (i != -1){
                        // Redefine menos distância
                        dist[vizinho] = dist[t->elem1] + peso;
                        // Define pai temporário
                        pai[vizinho] = t->elem1;
                        // Redefine menor distância na heap
                        h.change(i, dist[vizinho]);
                    }         
                }
            }
        }
    }

    // Adiona soma das distâncias ao final do vetor de distâncias
    dist[n_vertices] = dist_acum;

    // Retorna o vetor de distâncias
    return dist;
}

// Algoritmo de árvore geradora mínima a partir da origem
float* MatrizAdjacencias::Prim(int origem){

    // Aloca memória para vetor de custos
    float* custo = (float*) malloc(sizeof(float)*n_vertices);

    // Aloca memória para vetor de pais temporários
    int* pai = (int*) malloc(sizeof(int)*n_vertices);
    
    // Varíavel para nível inicial
    int nivel = 0;

    Heap h(n_vertices, false);

    // Tupla temporária
    Tupla<int, float>* t;

    // Varíavel temporária para peso a aresta analisada
    int peso;

    // Para todos os vértices
    for(int i=0;i<n_vertices;i++){
        t = (Tupla<int,float>*) malloc(sizeof(Tupla<int,float>));

        // Tupla recebe o índice do vértice
        t->elem1 = i;
        // E a distância inicial infinita
        t->elem2 = INFINITY;
        // Tupla adicionada no vector
        h.insert(t);
        // Distancia inicial infinita
        custo[i] = INFINITY;
        // Inicialmente nenhum vértice tem pai
        pai[i] = -2;
    }


    // Define custo da origem como 0 no vetor e na base da heap
    custo[origem] = 0;
    Tupla<int,float> t_origem(origem, 0);
    

    int index_origem = h.getIndex(&t_origem);
    h.change(index_origem, 0);
    
    // Define pai temporário da origem
    pai[origem] = -1;

    // Enquanto há vértices a serem explorados
    while(!h.empty()){

        // t é o vértice restante com menor custo para ser adicionado a árvore
        t = h.extract();

        // Define pai e nível do vértice selecionado na árvore geradora
        vertices[t->elem1]->setPai(pai[t->elem1]);
        if(pai[t->elem1]>0) nivel = vertices[pai[t->elem1]]->getNivel()+1;                
        vertices[t->elem1]->setNivel(nivel);
        
        // Percorre a matriz de adjacencias
        for(int vizinho=0;vizinho<n_vertices;vizinho++){

            peso = adjacencias[t->elem1][vizinho];
            // Se o vizinho é realmente vizinho de t
            if(peso != 0){

                // Se a distância do vizinho a origem for maior que a distância do vértice mais o peso da aresta
                if(custo[vizinho] > peso){

                    // Define um contador para achar o vizinho na heap
                    int i = 0;
                    
                    Tupla<int,float> t_vizinho(vizinho, 0);

                    i = h.getIndex(&t_vizinho);

                    if (i != -1){
                        custo[vizinho] = peso;
                        pai[vizinho] = t->elem1;
                        h.change(i, custo[vizinho]);
                    }            
                    
                }
            }
        }
    }

    // Retorna o vetor de distâncias
    return custo;
}

// Retorna o caminho mínimo e a distânica da origem ao destino
// Se origem e destino estão em componentes conexas diferentes
// Distância é infinita e caminho é apenas o destino
Tupla<int*, float> MatrizAdjacencias::CaminhoMinimo(int origem, int destino){

    // Vetor de índices referente ao caminho da origem ao destino
    int* caminho;

    // Disância da origem ao destino
    float distancia;
    
    // Declara variável de retorno
    Tupla<int*, float> ret;

    // Número de vértices que o caminho contém
    int tamanho_caminho;

    // Variável temporária para iterar pelo caminho pai pai
    int pai;

    // Se o grafo possuí pesos nas arestas
    if(peso){
        // A distância está na posição destino do vetor de distâncias encontrado por Dijkstra
        distancia = Dijkstra(origem, destino)[destino];
    } 
    // Se o grafo não possui pesos nas arestas
    else{
        // É rodada uma BFS a partir da origem
        BFS(origem);
        // E a distância é o nível do vértice destino na árvore geradora
        // Se o nível for -1, a origem e o destino estão em componentes conexas diferentes
        // E a distância deve ser infinita
        distancia = vertices[destino]->getNivel()!=-1?vertices[destino]->getNivel():INFINITY;
    }

    // Caminho começa com tamnho 0
    tamanho_caminho = 0;

    // Pai começa como o destino
    pai = destino;

    // Enquanto o pai não for -1
    // Raiz tem pai -1
    while(pai>=0){
        // Redefine o pai
        pai = vertices[pai]->getPai();
        // Incrementa o caminho
        tamanho_caminho++;
    }

    // Aloca memória para caminhi
    caminho = (int*) malloc(sizeof(int)*tamanho_caminho);

    // Pai começa como o destino
    pai = destino;

    // A partir do destino, percorrendo pai a pai
    for(int i=tamanho_caminho-1;i>=0;i--){
        // Coloca o pai no caminho
        caminho[i] = pai;
        // Redefine o pai
        pai = vertices[pai]->getPai();
    }

    // Define a varíavel de retorno com o caminho e a distância
    ret.elem1 = caminho;
    ret.elem2 = distancia;

    // Retorna
    return ret;
}

// Escreve a árvore geradora mínima em um arquivo
// Se o grafo não for conexo, escreve a floresta geradora mínima e a soma dos custos de todas as MSTs
void MatrizAdjacencias::ArvoreGeradoraMinima(FILE* output){

    // Vetor de custos
    float* custo = Prim(0);

    // Variável temporária para pai do vértice
    int pai;

    // Custo total da MST
    float custo_total;

    // Imprime tamnho da MST, que é o número de vértices do grafo
    fprintf(output, "%d\n", n_vertices);

    // Custo inicia como 0
    custo_total = 0;

    // Para todos os vértices do grafo
    for(int i=0;i<n_vertices;i++){

        // Pai do vértice i
        pai = vertices[i]->getPai();

        // Se o vértice está na MST
        if(custo[i] != INFINITY && pai>=0){
            // Imprime a aresta para o arquivo
            fprintf(output, "%d %d %.2f\n", pai+1, i+1, custo[i]);
            // Incrementa custo total
            custo_total+=custo[i];
        }
    }
    // Imprime o custo total
    fprintf(output, "Custo total: %.2f\n", custo_total);
}

//Calcula a maior distância no grafo. Retorna -1 se o grafo não or conexo
int MatrizAdjacencias::diametro()
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Declaração de variáveis

    // Declaração de variável a ser comparada
    int diametro = 0;
    
    // Declarando variável acumuladora
    int tmp;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // BFS

    // Checa se há mais de uma componente conexa
    // Caso tenha, o diâmetro é infinito
    if(componentesConexos().size()>1) return -1;

    // Roda n_vertices BFS e guarda o valor do maior nível alcançado (diâmetro do grafo)
    for(int i=0;i<n_vertices;i++)
    {
        // Executa BFS em i e guarda seu maior nível
        tmp = BFS(i);

        // Compara tmp com o maior diâmetro encontrado até o momento
        diametro = tmp > diametro ? tmp : diametro;
    }

    return diametro;
}

// Retorna a maior distância entre o vértice e qualquer outro vértice do grafo
float MatrizAdjacencias::excentricidade(int vertice){

    // Vetor de distâncias 
    float* dist;

    // Maior distância a partir do vértice
    float dist_max;

    // Se o grafo possui pesos nas arestas
    if(peso){
        // Vetor de distâncias encontrado por Dijkstra
        dist = Dijkstra(vertice);

        // Distância máxima começada como 0
        dist_max = 0;

        // Para todos os vértices do grafo
        for(int i=0;i<n_vertices;i++){
            // Se a distância de i ao vértice for maior que a distância máxima, redefine a distância máxima
            if(dist[i]!=INFINITY) dist_max = dist[i]>dist_max?dist[i]:dist_max; 
        }
    }

    // Se o grafo não possui pesos nas arestas
    else{
        // Distâcia máxima equivale ao maior nível da árvore geradora da BFS a partir do vértice
        dist_max = BFS(vertice);
    }

    // Retorna a maior distância
    return dist_max;
}

// Retorna a média das distâncias de todos os pares de vértices do grafo
float MatrizAdjacencias::DistanciaMedia(){

    // Acumulador de distâncias
    float dist_acum = 0;

    // Nivel do vertice na arvore BFS
    int nivel;

    for(int i=0;i<n_vertices;i++){
        // Se o grafo tem pesos nas arestas, adiciona as distâncias a partir de i ao acumulador
        if(peso) dist_acum += Dijkstra(i)[n_vertices];
        
        // Se o grafo não possui peso nas arestas
        else{ 

            // Roda uma BFS a partir de i
            BFS(i);

            // Para todo vértice do grafo
            for(int j=0;j<n_vertices;j++){
                // Pega o nivel de j na árvore BFS a partir de i
                nivel = vertices[j]->getNivel();

                // Se j e i estão na mesma componente conexa, adiciona esse nivel ao acumulador
                dist_acum += nivel>=0?nivel:0;
            }
        }
    }

    // Retorna média das distâncias
    return dist_acum/(2*n_vertices*(n_vertices-1)/2);
}

// Função que percorre todas componentes conexas do grafo e retorna um vetor que associa cada CC ao seu tamanho
vector<Tupla<int, int> > MatrizAdjacencias::componentesConexos()
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Declaração de variáveis

    // Criando lista de desmarcados
    // A classe Lista implementa uma lista duplamente encadeada (ListNode)    
    Lista desmarcados;
   
    // Declaração de tupla auxiliar
    // Cada tupla armazena os identificadores da componente conexa e seus respectivos tamanhos
    Tupla<int, int> t;

    // Vetor de tuplas
    vector<Tupla<int, int> > tamanhos;

    // Variável auxiliar para definir tamanho da componente conexa
    int tamanho;

    // Criando lista de ponteiros para elementos de uma lista duplamente encadeada
    ListNode **indices = (ListNode **)malloc(sizeof(ListNode *) * n_vertices);

    // Criando ponteiro para o elemento da lista encadeada a ser analisado no momento
    ListNode *no;

    // Declarando fila a ser usada no BFS
    queue<int> Q;

    // Variável marcador que diferencia a componente conexa que algoritmo está computando no momento
    int marcador = 1;
    
    // Variável que guarda o vértice de origem da BFS
    int origem ;

    // Declarando variável que guarda o topo da fila (vértice sendo analisado no BFS)
    int verticeAtual;

    // Variável iteradora do for
    int i;

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
            
            // Para cada vértice
            for (i = 0; i < n_vertices; i++)
            {
                // Checa se há relação entre verticeAtual e i
                if (adjacencias[verticeAtual][i])
                {
                    // Checa se i foi marcado
                    if (vertices[i]->getMarcacao() == 0)
                    {
                        // Marca vértice i
                        vertices[i]->marca(marcador);

                        // Incrementa tamanho da componente conexa
                        tamanho++;

                        // Retira i da lista de desmarcados
                        desmarcados.erase(indices[i]);

                        // Insere i na fila
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

        // Pega o primeiro elemento da lista de desmarcados
        no = desmarcados.getInicio();

        // Se nó for igual a NULL, a lista está vazia
        // Com isso o algoritmo pode ser finalizado
        if(!no) break;
        
        // Próximo vértice a ser analizado é igual ao número guardado dentro da lista sendo apontada        
        origem = no->elemento.elem1;

        // Incrementando o identificador da componente conexa (pois achamos outra componente)
        marcador++;
    }

    // Liberando memória do ponteiro índice (ponteiro para lista de Listas)
    free(indices);

    // Retorna vetor de Tuplas com todas as componentes conexas e seus tamanhos
    return tamanhos;
}

//Função para analisar as componentes conexas com relação a tamanho e elementos que as formam
Lista** MatrizAdjacencias::analiseComponentesConexos()
{
    // Declara a tupla que será retirada da heap
    Tupla<int, int> t;

    // Acha todas as componentes conexas
    vector<Tupla<int, int> > ccs = componentesConexos();

    // Declara o vetor de listas que guardará as componentes ordenadas
    Lista** componentesConexas = (Lista**) malloc(sizeof(Lista*) * ccs.size()) ;
    
    // Inicia o contador de componentes
    int c = 0;

    // Função padrão para transformar o vector em heapmax 
    make_heap(ccs.begin(),ccs.end());
    
    // Enquanto a heap não estiver vazia
    while(!ccs.empty()){
    
        // Pega primeira tupla da heap (componente de maior tamanho dentre as restantes)
        pop_heap(ccs.begin(),ccs.end());
        t = ccs.back();

        // Remove essa tupla da heap
        ccs.pop_back();
    
        // Inicia a lista para a componente conexa c
        componentesConexas[c] = new Lista();

        // Define o primeiro elemento da lista como o identificador da componente
        componentesConexas[c]->push(t.elem1);

        // Para todos os vértices marcados com o identificador da componente
        for(int i=0;i<n_vertices;i++)
        {
            if(vertices[i]->getMarcacao()==t.elem1){
                // Insere o identificador do vértice na lista
                componentesConexas[c]->push(i);
            }
        }

        // Incrementa o contador de componentes
        c++;
    }

    // Retorna o vetor de listas de componentes em ordem decrescente
    return componentesConexas;
}

// Construtor de lista de adjacência a partir de um número de vértices
// Ainda é preciso chamar setAdjacencia pela main a fim de criar as arestas e relações entre vértices
ListaAdjacencias::ListaAdjacencias(int n, bool p)
{
    // Define n_vertices como o argumento passado
    n_vertices = n;

    // Inicializa n_arestas como 0
    n_arestas = 0;

    // Inicializa a flag de pesos com o argumento passado
    peso = p;

    // Inicializa a flag de pesos neagtivos como false
    pesos_negativos = false;

    // Alocação de memória para lista de ponteiros para vértices e lista de adjacência
    vertices = (Vertice **)malloc(sizeof(Vertice *) * n_vertices);
    adjacencias = (Lista **)malloc(sizeof(Lista *) * n_vertices);
    
    // Para cada n_vertice, inicializa-se uma classe Vertice e uma Lista para guardar seus vizinhos
    for (int i = 0; i < n_vertices; i++)
    {
        // Criando novo vértice e retornando seu ponteiro à lista de ponteiros para Vertices
        vertices[i] = new Vertice();

        // Criando nova listae retornando seu ponteiro à lista de ponteiros para Listas de Adjacências
        adjacencias[i] = new Lista();
    }
}

// Constrói uma matriz de adjacências a partir de um arquivo com pontos pertencentes a um plano
ListaAdjacencias::ListaAdjacencias(FILE *pontos)
{
    // Lê a primeira linha do programa e guarda o inteiro como o número de vértices total
    fscanf(pontos, "%d", &n_vertices);

    // Inicializa o número de arestas como 0
    n_arestas = 0;

    // Inicializa a flag de pesos com o argumento passado
    peso = true;

    // Inicializa a flag de pesos negativos como false
    pesos_negativos = false;

    // Cria uma lista de ponteiros para elementos de classe Vertice (tamanho n_vertices)
    // Com isso conseguimos guardar características de cada vértice
    vertices = (Vertice **)malloc(sizeof(Vertice *) * n_vertices);

    // Cria uma lista de ponteiros para elementos de classe Lista (tamanho n_vertices))
    // Com isso conseguimos gaurdar listas encadeadas para vizinhos de cada vértice
    adjacencias = (Lista **)malloc(sizeof(Lista *) * n_vertices);

    // Declaração das coordenadas que serão lidas do arquivo
    float x,y;

    // Para cada n_vertice, inicializa-se uma classe Vertice e uma linha da matriz de tamanho n_vertice
    for (int i = 0; i < n_vertices; i++)
    {
        fscanf(pontos, "%f %f", &x, &y);
        // Criando novo vértice e retornando seu ponteiro à lista de ponteiros para Vertices
        vertices[i] = new Vertice(x,y);
    }

    float dist;
    // Define os pesos de todas as arestas
    for (int i = 0; i < n_vertices; i++)
    {
        // Criando nova listae retornando seu ponteiro à lista de ponteiros para Listas de Adjacências 
        adjacencias[i] = new Lista();
        for (int j = 0; j < n_vertices; j++)
        {
            // Calcula a distância entre i e j
            x = (vertices[i]->getPosX()-vertices[j]->getPosX());
            y = (vertices[i]->getPosY()-vertices[j]->getPosY());
            x *= x;
            y *= y;
            dist = sqrt(x+y);

            // Define o peso da aresta como essa distância
            setAdjacencia(i+1,j+1,dist);
        }
    
    }
}

// Constrói uma lista de adjacência a partir da descrição de um grafo dentro de um arquivo
ListaAdjacencias::ListaAdjacencias(FILE *input, bool p)
{
    // Lê a primeira linha do programa e guarda o inteiro como o número de vértices total
    fscanf(input, "%d", &n_vertices);

    // Inicializa o número de arestas como 0
    n_arestas = 0;

    // Inicializa a flag de pesos com o argumento passado
    peso = p;

    // Inicializa a flag de pesos negativos como false
    pesos_negativos = false;

    // Cria uma lista de ponteiros para elementos de classe Vertice (tamanho n_vertices)
    // Com isso conseguimos guardar características de cada vértice
    vertices = (Vertice **)malloc(sizeof(Vertice *) * n_vertices);

    // Cria uma lista de ponteiros para elementos de classe Lista (tamanho n_vertices))
    // Com isso conseguimos gaurdar listas encadeadas para vizinhos de cada vértice
    adjacencias = (Lista **)malloc(sizeof(Lista *) * n_vertices);
    
    // Para cada n_vertice, inicializa-se uma classe Vertice e uma Lista para guardar seus vizinhos
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
    float w = 1;
    int leitura = 1;

    // Loop de leitura de linhas do arquivo que termina quando recebe EOF (End Of File)
    while (true)
    {
        if(p) leitura = fscanf(input, "%d %d %f", &v1, &v2, &w);
        
        else leitura = fscanf(input, "%d %d", &v1, &v2);

        printf("%d %d %f\n", v1, v2, w);
        printf("leitura: %d\n", leitura);

        if(leitura == EOF) break;
        // Se o índice de qualquer um dos vértices na linha lida for maior que o n_vertice, descarta-se a informação
        // e segue a próxima iteração do loop (pŕoxima linha)
        if(v1 > n_vertices || v2 > n_vertices) continue;

        // Caso a condição acima não seja satisfeita, define-se adjacência simétrica entre os dois vértices
        setAdjacencia(v1, v2, w);
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
void ListaAdjacencias::setAdjacencia(int v1, int v2, float w)
{
    //Se o peso da nova aresta for negativa, muda a flag de pesos negativos para refletir isso
    if(w<0) pesos_negativos = true;

    // Adiciona o vértice v2 como vizinho de v1
    adjacencias[v1 - 1]->push(v2 - 1, w);

    // Adiciona v1 como vizinho de v2
    adjacencias[v2 - 1]->push(v1 - 1, w);

    // Considerando que agora v1 possui um vizinho a mais, incrementa-se seu grau
    vertices[v1 - 1]->incrementaGrau();

    // Considerando que agora v2 possui um vizinho a mais, incrementa-se seu grau
    vertices[v2 - 1]->incrementaGrau();

    n_arestas++;
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
            verticeVizinho = pListaAdjacencias->elemento.elem1;

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

    // Retorna maiornivel para cálculo do diâmetro
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
    Tupla<int, int> **listaTupla = (Tupla<int, int> **)malloc(sizeof(Tupla<int, int> *) * n_vertices);

    // Criando stack de ponteiros para tuplas
    stack<Tupla<int, int> *> S;

    // Criando variável iterável do DFS
    Tupla<int, int> *tupla;

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
        listaTupla[i] = (Tupla<int, int> *) malloc(sizeof(Tupla<int, int>));

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
                verticeVizinho = pListaAdjacencias->elemento.elem1;

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

    // Loop para liberar todas as tuplas apontadas pelos ponteiros de listaTupla
    for (i = 0; i < n_vertices; i++)
    {
        free(listaTupla[i]);
    }

    // Libera memória da listaTupla
    free(listaTupla);
}

// Algoritmo de caminho mínimo entre origem e destino em grafos com pesos
// Retorna um vetor de distâncias em que o último elemento guarda todas as distâncias acumuladas
// Se o destino for -1, calcula a menor distância a partir da origem para todo o grafo
// Obs.: É preciso dar free no array de retorno dentro da main, após seu uso
float* ListaAdjacencias::Dijkstra(int origem, int destino){

    // Se há pesos negativos
    if(pesos_negativos){
        // Informa o usuário e termina a função
        printf("Não é possível utilizar o algoritmo de Dijkstra com pesos negativos.\n");
        return NULL; 
    }

    // Aloca memória para vetor de distâncias
    float* dist = (float*) malloc(sizeof(float)*(n_vertices+1));

    // Define acumulador de distâncias
    float dist_acum = 0;

    // Aloca memória para vetor de pais temporários
    int* pai = (int*) malloc(sizeof(int)*n_vertices);

    // Varíavel para nível inicial
    int nivel = 0;

    // Define min heap
    Heap h(n_vertices, false);

    // Tupla temporária
    Tupla<int, float>* t, vizinho;

    // Declara ponteiro para percorrer vizinhos dos vértices
    ListNode* pListaAdjacencias;


    // Para todos os vértices
    for(int i=0;i<n_vertices;i++){

        // Aloca memória para tupla
        t = (Tupla<int,float>*) malloc(sizeof(Tupla<int,float>));

        // Tupla recebe o índice do vértice
        t->elem1 = i;
        
        // E a distância inicial infinita
        t->elem2 = INFINITY;
        
        // Tupla adicionada no vector
        h.insert(t);
        
        // Distancia inicial infinita
        dist[i] = INFINITY;
        
        // Inicialmente nenhum vértice tem pai
        pai[i] = -2;
    }

    // Define distância da origem como 0 no vetor e na base da heap
    dist[origem] = 0;
    Tupla<int,float> t_origem(origem, 0);

    int index_origem = h.getIndex(&t_origem);
    h.change(index_origem, 0);
    
    // Define pai temporário da origem na árvore geradora
    pai[origem] = -1;

    // Enquanto há vértices a serem explorados
    while(!h.empty()){

        // t é o vértice restante com menor distância até a origem no momento
        t = h.extract();

        // Adiciona distância do vértice selecionado ao acumulador de distâncias
        dist_acum += dist[t->elem1]!=INFINITY?dist[t->elem1]:0;

        // Define pai e nível do vértice selecionado na árvore geradora
        vertices[t->elem1]->setPai(pai[t->elem1]);
        if(pai[t->elem1]>0) nivel = vertices[pai[t->elem1]]->getNivel()+1;                
        vertices[t->elem1]->setNivel(nivel);

        // Se o destino foi atingido, interrompe o loop
        if(t->elem1 == destino) break;

        // Acessa lista de adjacências do vértice
        pListaAdjacencias = adjacencias[t->elem1]->getInicio();
        
        // Até o final da lista
        while(pListaAdjacencias != NULL){

            // Acessa a tupla referente ao índice do vizinho e peso da aresta
            vizinho = pListaAdjacencias->elemento;

            // Se a distância do vizinho a origem for maior que a distância do vértice mais o peso da aresta
            if(dist[vizinho.elem1] > dist[t->elem1] + vizinho.elem2){

                // Define indice do vizinho na heap
                int i = h.getIndex(&vizinho);

                // Se o vizinho ainda está na heap
                if (i != -1){
                    // Atualiza menor distância
                    dist[vizinho.elem1] = dist[t->elem1] + vizinho.elem2;
                    // Define pai temporário
                    pai[vizinho.elem1] = t->elem1;
                    //Atualiza valor na heap
                    h.change(i, dist[vizinho.elem1]);
                }
            }

            // Acessa o próximo elemento da lista
            pListaAdjacencias = pListaAdjacencias->prox;
        }
    }

    // Adiona soma das distâncias ao final do vetor de distâncias
    dist[n_vertices] = dist_acum;

    // Libera memória usada pelo vetor de pais
    free(pai);

    for (int i = 0; i<n_vertices;i++) free(h.buffer[i]);

    // Retorna o vetor de distâncias
    return dist;
}

// Algoritmo de árvore geradora mínima a partir da origem
// Obs.: É preciso dar free no array de custo na main, após seu uso
float* ListaAdjacencias::Prim(int origem){

    // Variável iteradora de for
    int i;

    // Aloca memória para vetor de custos
    float* custo = (float*) malloc(sizeof(float)*n_vertices);

    // Aloca memória para vetor de pais temporários
    int* pai = (int*) malloc(sizeof(int)*n_vertices);
    
    // Varíavel para nível inicial
    int nivel = 0;

    Heap h(n_vertices, false);

    // Tupla temporária
    Tupla<int, float>* t, vizinho;

    // Declara ponteiro para percorrer vizinhos dos vértices
    ListNode* pListaAdjacencias;

    // Para todos os vértices
    for(i=0;i<n_vertices;i++){

        // Aloca memória para Tupla
        t = (Tupla<int,float>*) malloc(sizeof(Tupla<int,float>));

        // Tupla recebe o índice do vértice
        t->elem1 = i;
        
        // E a distância inicial infinita
        t->elem2 = INFINITY;
        
        // Tupla adicionada no vector
        h.insert(t);
        
        // Distancia inicial infinita
        custo[i] = INFINITY;
        
        // Inicialmente nenhum vértice tem pai
        pai[i] = -2;
    }

    // Define custo da origem como 0 no vetor e na base da heap
    custo[origem] = 0;
    Tupla<int,float> t_origem(origem, 0);

    int index_origem = h.getIndex(&t_origem);
    h.change(index_origem, 0);
    
    // Define pai temporário da origem
    pai[origem] = -1;

    // Enquanto há vértices a serem explorados
    while(!h.empty()){

        // t é o vértice restante com menor custo para ser adicionado a árvore
        t = h.extract();

        // Define pai e nível do vértice selecionado na árvore geradora
        vertices[t->elem1]->setPai(pai[t->elem1]);
        if(pai[t->elem1]>0) nivel = vertices[pai[t->elem1]]->getNivel()+1;                
        vertices[t->elem1]->setNivel(nivel);


        // Acessa lista de adjacências do vértice
        pListaAdjacencias = adjacencias[t->elem1]->getInicio();
        
        // Até o final da lista
        while(pListaAdjacencias != NULL){

            // Acessa a tupla referente ao índice do vizinho e peso da aresta
            vizinho = pListaAdjacencias->elemento;

            // Se o custo do vizinho for maior que o peso da aresta
            if(custo[vizinho.elem1] > vizinho.elem2){
                // Define um contador para achar o vizinho na heap
                int i = 0;

                i = h.getIndex(&vizinho);

                if (i != -1){
                    custo[vizinho.elem1] = vizinho.elem2;
                    pai[vizinho.elem1] = t->elem1;
                    h.change(i, custo[vizinho.elem1]);
                }            
            }

            // Acessa o próximo elemento da lista
            pListaAdjacencias = pListaAdjacencias->prox;
        }
    }

    // Libera o vetor de pais
    free(pai);

    // Retorna o vetor de distâncias
    return custo;
}

// Retorna o caminho mínimo e a distânica da origem ao destino
// Se origem e destino estão em componentes conexas diferentes
// Distância é infinita e caminho é apenas o destino
// Obs.: É preciso dar free dentro da main, após o uso da função
Tupla<int*, float> ListaAdjacencias::CaminhoMinimo(int origem, int destino){

    // Vetor de índices referente ao caminho da origem ao destino
    int* caminho;

    // Disância da origem ao destino
    float distancia;
    
    // Declara variável de retorno
    Tupla<int*, float> ret;

    // Número de vértices que o caminho contém
    int tamanho_caminho;

    // Variável temporária para iterar pelo caminho pai pai
    int pai;

    // Se o grafo possuí pesos nas arestas
    if(peso){
        // A distância está na posição destino do vetor de distâncias encontrado por Dijkstra
        distancia = Dijkstra(origem, destino)[destino];
    } 
    // Se o grafo não possui pesos nas arestas
    else{
        // É rodada uma BFS a partir da origem
        BFS(origem);
        // E a distância é o nível do vértice destino na árvore geradora
        // Se o nível for -1, a origem e o destino estão em componentes conexas diferentes
        // E a distância deve ser infinita
        distancia = vertices[destino]->getNivel()!=-1?vertices[destino]->getNivel():INFINITY;
    }

    // Caminho começa com tamnho 0
    tamanho_caminho = 0;

    // Pai começa como o destino
    pai = destino;

    // Enquanto o pai não for -1
    // Raiz tem pai -1
    while(pai>=0){
        // Redefine o pai
        pai = vertices[pai]->getPai();
        // Incrementa o caminho
        tamanho_caminho++;
    }

    // Aloca memória para caminho
    caminho = (int*) malloc(sizeof(int)*(tamanho_caminho+1));

    // Pai começa como o destino
    pai = destino;

    // A partir do destino, percorrendo pai a pai
    for(int i=tamanho_caminho;i>0;i--){
        
        // Coloca o pai no caminho
        caminho[i] = pai;
        
        // Redefine o pai
        pai = vertices[pai]->getPai();
    }
    caminho[0] = tamanho_caminho;

    // Define a varíavel de retorno com o caminho e a distância
    ret.elem1 = caminho;
    ret.elem2 = distancia;

    //free(caminho);

    // Retorna
    return ret;
}

// Escreve a árvore geradora mínima em um arquivo
// Se o grafo não for conexo, escreve a floresta geradora mínima e a soma dos custos de todas as MSTs
void ListaAdjacencias::ArvoreGeradoraMinima(FILE* output){

    // Vetor de custos
    float* custo = Prim(0);

    // Variável temporária para pai do vértice
    int pai;

    // Custo total da MST
    float custo_total;

    // Imprime tamnho da MST, que é o número de vértices do grafo
    fprintf(output, "%d\n", n_vertices);

    // Custo inicia como 0
    custo_total = 0;

    // Para todos os vértices do grafo
    for(int i=0;i<n_vertices;i++){

        // Pai do vértice i
        pai = vertices[i]->getPai();

        // Se o vértice está na MST
        if(custo[i] != INFINITY && pai>=0){
            // Imprime a aresta para o arquivo
            fprintf(output, "%d %d %.2f\n", pai+1, i+1, custo[i]);
            // Incrementa custo total
            custo_total+=custo[i];
        }
    }
    
    // Imprime o custo total
    fprintf(output, "Custo total: %.2f\n", custo_total);

    // Libera memória usada pelo custo
    free(custo);
}

//Calcula a maior distância no grafo. Retorna -1 se o grafo não or conexo
int ListaAdjacencias::diametro()
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Declaração de variáveis

    // Declaração de variável a ser comparada
    int diametro = 0;
    
    // Declarando variável acumuladora
    int tmp;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // BFS

    // Checa se há mais de uma componente conexa
    // Caso tenha, o diâmetro é infinito
    if(componentesConexos().size()>1) return -1;

    // Roda n_vertices BFS e guarda o valor do maior nível alcançado (diâmetro do grafo)
    for(int i=0;i<n_vertices;i++)
    {
        // Executa BFS em i e guarda seu maior nível
        tmp = BFS(i);

        // Compara tmp com o maior diâmetro encontrado até o momento
        diametro = tmp > diametro ? tmp : diametro;
    }

    // Retorna diâmetro do grafo
    return diametro;
}

// Retorna a maior distância entre o vértice e qualquer outro vértice do grafo
float ListaAdjacencias::excentricidade(int vertice){

    // Vetor de distâncias 
    float* dist;

    // Maior distância a partir do vértice
    float dist_max;

    // Se o grafo possui pesos nas arestas
    if(peso){
        // Vetor de distâncias encontrado por Dijkstra
        dist = Dijkstra(vertice);

        // Distância máxima começada como 0
        dist_max = 0;

        // Para todos os vértices do grafo
        for(int i=0;i<n_vertices;i++){
            
            // Se a distância de i ao vértice for maior que a distância máxima, redefine a distância máxima
            if(dist[i]!=INFINITY) dist_max = dist[i]>dist_max?dist[i]:dist_max; 
        }

        free(dist);
    }

    // Se o grafo não possui pesos nas arestas
    else{
        // Distâcia máxima equivale ao maior nível da árvore geradora da BFS a partir do vértice
        dist_max = BFS(vertice);
    }

    // Retorna a maior distância
    return dist_max;
}

// Retorna a média das distâncias de todos os pares de vértices do grafo
float ListaAdjacencias::DistanciaMedia(){

    // Acumulador de distâncias
    float dist_acum = 0;

    // Nivel do vertice na arvore BFS
    int nivel;

    float* dist;

    for(int i=0;i<n_vertices;i++){
        
        // Se o grafo tem pesos nas arestas, adiciona as distâncias a partir de i ao acumulador
        if(peso){
            dist = Dijkstra(i);
            dist_acum += dist[n_vertices];
            free(dist);
        }

        // Se o grafo não possui peso nas arestas
        else{ 

            // Roda uma BFS a partir de i
            BFS(i);

            // Para todo vértice do grafo
            for(int j=0;j<n_vertices;j++){
                
                // Pega o nivel de j na árvore BFS a partir de i
                nivel = vertices[j]->getNivel();

                // Se j e i estão na mesma componente conexa, adiciona esse nivel ao acumulador
                dist_acum += nivel>=0?nivel:0;
            }
        }
    }

    // Retorna média das distâncias
    return dist_acum/(2*n_vertices*(n_vertices-1)/2);
}

// Função que percorre todas componentes conexas do grafo, as ordena dentro de um vetor e retorna a quantidade de CCs
vector<Tupla<int, int> > ListaAdjacencias::componentesConexos()
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Declaração de variáveis

    // Criando lista de desmarcados
    // A classe Lista implementa uma lista duplamente encadeada (ListNode)    
    Lista desmarcados;


    // Declaração de tupla auxiliar
    // Cada tupla armazena os identificadores da componente conexa e seus respectivos tamanhos
    Tupla<int, int> t;

    // Vetor de tuplas
    vector<Tupla<int, int> > tamanhos;
    
    // Variável auxiliar para definir tamanho da componente conexa
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
                verticeVizinho = pListaAdjacencias->elemento.elem1;

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
        origem = no->elemento.elem1;

        // Incrementando o identificador da componente conexa (pois achamos outra componente)
        marcador++;
    }

    // Liberando memória do ponteiro índice (ponteiro para lista de Listas)
    free(indices);

    // Retorna vetor de Tuplas com todas as componentes conexas e seus tamanhos
    return tamanhos;
}

//Função para analisar as componentes conexas com relação a tamanho e elementos que as formam
Lista** ListaAdjacencias::analiseComponentesConexos()
{
    //Declara a tupla que será retirada da heap
    Tupla<int, int> t;

    //Acha todas as componentes conexas
    vector<Tupla<int, int> > ccs = componentesConexos();
   
    //Declara o vetor de listas que guardará as componentes ordenadas
    Lista** componentesConexas = (Lista**) malloc(sizeof(Lista*) * ccs.size()) ;
   
    //Inicia o contador de componentes
    int c = 0;

    //Função padrão para transformar o vector em heapmax 
    make_heap(ccs.begin(),ccs.end());

    //Enquanto a heap não estiver vazia
    while(!ccs.empty()){
  
        //Pega primeira tupla da heap (componente de maior tamanho dentre as restantes)
        pop_heap(ccs.begin(),ccs.end());
        t = ccs.back();
    
        //Remove essa tupla da heap
        ccs.pop_back();
  
        //Inicia a lista para a componente conexa c
        componentesConexas[c] = new Lista();
       
        //Define o primeiro elemento da lista como o identificador da componente
        componentesConexas[c]->push(t.elem1);

        //Para todos os vértices marcados com o identificador da componente
        for(int i=0;i<n_vertices;i++)
        {
            if(vertices[i]->getMarcacao()==t.elem1){
                //Insere o identificador do vértice na lista
                componentesConexas[c]->push(i);
            }
        }
        //Incrementa o contador de componentes
        c++;
    }
   
    //Retorna o vetor de listas de componentes em ordem decrescente
    return componentesConexas;
}

// Se leu até aqui você é um fã de verdade!
// Não se esqueça de curtir o repositório e seguir o canal no GitHub