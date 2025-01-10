#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "matriz_final.h"
#include "validade_codigo.h"

int** dimensionar(int linhas, int colunas){
    int**m;
    m = calloc(linhas, sizeof(int*));

    for(int i = 0; i < linhas; ++i){
        m[i] = calloc(colunas, sizeof(int));
    }

    return m;
}

//fun��o para montar a matriz ajustada de acordo com a largura de cada �rea e baseada no vetor_ean
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

//fun��o que printa a matriz final no arquivo pbm
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
        printf("O arquivo a ser criado j� existe. Deseja sobrescrev�-lo (s/n)?\n");
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
        printf("arquivo resultante j� existe!\n");
    }

}

//transformar codigo de barras em matriz

//TODO: criar um vetor com a linha espacamento_superior+1, a partir da coluna espacamento_superior+1 até a coluna espacamento_superior-1
//a partir da coluna espacamento_superior+1 checar quantos 1 seguidos, para saber a area.

int calcular_area(int largura, int espacamento, FILE *arquivo){

    int area = 0;
    char linha[largura+1];  
    int linha_meio = (altura / 2)+2;

    fseek(arquivo, linha_meio * largura * sizeof(char), SEEK_SET);

    //pulando para a linha após o espacamento
    for(int i = 0; i<espacamento+1;i++){ 
        fgets(linha, sizeof(linha), arquivo);
    }

    fgets(linha, sizeof(linha), arquivo); //lê uma linha do código de 

    for (int i = 0; i < largura; i++) { //testando para ver se a linha sendo observada é a certa
        printf("%c", linha[i]);
    }
    printf("\n");  // Nova linha após a impressão de todos os elementos

    
    for (int i = espacamento; i < largura; i++) { //conta quantos 1s seguidos tem, para descobrir a area
            if (linha[i] == '1') {
                area++;  
            } else if (linha[i] == '0'){
                break;
            }
    }
    
    return area;
}

