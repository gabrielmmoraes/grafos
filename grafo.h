#ifndef GRAFO_H
#define GRAFO_H

class Vertice{
    public:
        Vertice(int i);
        
        int getIndice();
        int getGrau();
        int getPai();
        int getNivel();
        int getMarcacao();

        void incrementaGrau();
        void setPai(int v);
        void setNivel(int n);
        void desmarca();
        void marca(int i=1);
    protected:
    private:
        int indice;
        int grau;
        int marcacao;
        int pai;
        int nivel;
        
};

class Aresta{
    public:
        Aresta(int v1, int v2);
        Vertice* getVertice(int v);
    protected:
    private:
        Vertice *v[2];
};

class MatrizAdjacencias{
    public:
        MatrizAdjacencias(int n);
        MatrizAdjacencias(FILE *input);

        void setAdjacencia(int v1, int v2);

        void BFS(int origem);
        void DFS(int origem);

        void componentesConexos();

    protected:
    private:
        int n_vertices;
        int n_arestas;
        Vertice **vertices;
        int **adjacencias;
};

class ListaAdjacencias{
    public:
        ListaAdjacencias(int n);
        ListaAdjacencias(FILE *input);

        void setAdjacencia(int v1, int v2);

        void BFS(int origem);
        void DFS(int origem);

        void componentesConexos();
    protected:
    private:
        int n_vertices;
        int n_arestas;
        Vertice **vertices;
        list<int> **adjacencias;
};

#endif //GRAFO_H