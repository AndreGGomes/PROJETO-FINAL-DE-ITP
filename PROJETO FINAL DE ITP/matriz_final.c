#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "matriz_final.h"

int** dimensionar(int linhas, int colunas){
    int**m;
    m = calloc(linhas, sizeof(int*));

    for(int i = 0; i < linhas; ++i){
        m[i] = calloc(colunas, sizeof(int));
    }

    return m;
}

//função para montar a matriz ajustada de acordo com a largura de cada área e baseada no vetor_ean
void montarMatriz(int** matriz, int* vetor, int borda, int largura_area, int linhas, int colunas){

    int i = borda;
    int x = 0;

    while(i < (colunas - borda)){

        int cont = 0;
        while(cont < largura_area){
            matriz[borda][i] = vetor[x];
            cont = cont + 1;
            i = i + 1;
        }
        x = x + 1;
    }
    for(int ln = 0; ln < linhas; ++ln){
        if(ln > borda && ln < linhas-borda){
            matriz[ln] = matriz[borda];
        }
    }

    free(vetor);
}

//função que printa a matriz final no arquivo pbm
void print(int** matriz, int linhas, int colunas, char nome_imagem[]){

    setlocale(LC_ALL,"");
    char confirmacao;
    FILE * fp;
    fp = fopen(nome_imagem, "r");

    if(fp == NULL){
        fp = fopen(nome_imagem, "w+");
        fprintf(fp, "P1\n");
        fprintf(fp, "%d %d\n", colunas, linhas);

        for(int i = 0; i < linhas; ++i){
            for(int j = 0; j < colunas; ++j){
                fprintf(fp, "%d", matriz[i][j]);
            }
            fprintf(fp, "\n");
        }
        fclose(fp);

        free(matriz);

    }else{
        printf("O arquivo a ser criado já existe. Deseja sobrescrevê-lo (s/n)?\n");
        scanf(" %c", &confirmacao);
    }
    if(confirmacao == 's'){
        fp = fopen(nome_imagem, "r+");
        fprintf(fp, "P1\n");
        fprintf(fp, "%d %d\n", colunas, linhas);

        for(int i = 0; i < linhas; ++i){
            for(int j = 0; j < colunas; ++j){
                fprintf(fp, "%d", matriz[i][j]);
            }
            fprintf(fp, "\n");
        }
        fclose(fp);

        free(matriz);

    }else if(confirmacao == 'n'){
        printf("arquivo resultante já existe!\n");
    }

}
