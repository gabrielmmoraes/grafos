
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include "grafo.h"
#include "tupla.h"

using namespace std;

/*     Tupla<int, float> t1(1,2);
    Tupla<int, float> t2(2,3);
    Tupla<int, float> t3(3,4);
    Tupla<int, float> t4(4,5);
    Tupla<int, float> t5(5,6);
    Tupla<int, float> t6(6,7);
    Tupla<int, float> t7(7,8);
    Tupla<int, float> t8(8,9);

    Tupla<int, float>* t10;

    Tupla<int, float>* ary[] = { &t1, &t2, &t3, &t4, &t5, &t6, &t7, &t8 };

    Heap h(ary, 8, 8, true);

    int k =8;

    //for(int j=0; j<8; j++, k--){
        for (int i = 0; i < k; i++){
            printf("(%d, %.1f), ", h.buffer[i]->elem1, h.buffer[i]->elem2);
        }
        printf("\n");

        Tupla<int, float> t(3,13);

        k = h.getIndex(&t);

        printf("%d index\n", k);

        //t10 = h.extract();
     //   printf("raiz extraida: (%d, %.1f)\n", t10->elem1, t10->elem2);
    //} */

int main(){

    FILE* pFileIn;

    pFileIn = fopen("grafo_teste.txt", "r");

    MatrizAdjacencias G(pFileIn, true);

    float* dist = G.Dijkstra(0);

    for(int i=0;i<16;i++){
        printf("Custo de %d: %f\n", i+1, dist[i]);
        printf("Pai de %d: %d\n", i+1, G.getVertices()[i]->getPai()+1);
    }
}