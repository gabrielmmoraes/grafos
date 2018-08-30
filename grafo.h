#ifndef GRAFO_H
#define GRAFO_H

class Vertice{
    public:
        Vertice(unsigned long i);
        
        unsigned long getIndice();
        unsigned long getGrau();
        unsigned long getPai();
        unsigned long getNivel();
        uint8_t getMarcacao();

        void incrementaGrau();
        void setPai(int v);
        void setNivel(int n);
        void desmarca();
        void marca(int i=1);
    protected:
    private:
        unsigned long indice;
        unsigned long grau;
        uint8_t marcacao;
        unsigned long pai;
        unsigned long nivel;
        
};

class Aresta{
    public:
        Aresta(unsigned long v1, unsigned long v2);
        Vertice* getVertice(unsigned long v);
    protected:
    private:
        Vertice *v[2];
};

class MatrizAdjacencias{
    public:
        MatrizAdjacencias(unsigned long n);
        MatrizAdjacencias(FILE *input);

        void setAdjacencia(unsigned long v1, unsigned long v2);

        void BFS(unsigned long origem);
        void DFS(unsigned long origem);

        void componentesConexos();

    protected:
    private:
        unsigned long n_vertices;
        unsigned long n_arestas;
        Vertice **vertices;
        unsigned long **adjacencias;
};

class ListaAdjacencias{
    public:
        ListaAdjacencias(unsigned long n);
        ListaAdjacencias(FILE *input);

        void setAdjacencia(unsigned long v1, unsigned long v2);

        void BFS(unsigned long origem);
        void DFS(unsigned long origem);

        void componentesConexos();
    protected:
    private:
        unsigned long n_vertices;
        unsigned long n_arestas;
        Vertice **vertices;
        list<unsigned long> **adjacencias;
};

#endif //GRAFO_H