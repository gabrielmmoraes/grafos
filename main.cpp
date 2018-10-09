
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include "grafo.h"
#include "tupla.h"
#include <sys/time.h>

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

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main(){

    FILE* pFileIn;
    FILE* pFileOut;

    long inicio, fim;

    double duracao;

    pFileIn = fopen("grafo_teste.txt", "r");

    ListaAdjacencias G(pFileIn, true);

    inicio = getMicrotime();

    for (int i = 0; i<15; i++) {
        float oi = G.excentricidade(i);
    
        //for(int j = 0; j<15;j++){
            printf("Dist de med %d é %.1f\n", i+1, oi);
        //}
    
        printf("\n\n");

//        free(oi);
    }

    fim = getMicrotime();

    duracao = (fim-inicio) / 1000;

    printf("%lf\n", duracao);

/*     for (int j = 9; j <= 49; j+=10){

        Tupla<int*,float> gosto = G.CaminhoMinimo(0,j);

        printf("Distância até 10: %f\n", gosto.elem2);

        printf("Caminho: ");
        for(int i = 1; i<=gosto.elem1[0];i++){
            printf("(%d) ",gosto.elem1[i]+1);
        }
        printf("\n");

        printf("Excentricidade de %d: %f\n\n", j+1, G.excentricidade(j));

    }
 */
}