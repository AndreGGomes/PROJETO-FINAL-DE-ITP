#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz_final.h"
#include "validade_codigo.h"
#include "codigo_bin.h"

//recebe o arquivo como parâmetro:

int main(int argc, char *argv[]) {


    //caso o parâmetro do arquivo não for digitado:

    if (argc != 2) { 
        printf("\nNenhum arquivo foi escolhido!");
        return 1;
    }

    //abre o arquivo:

    FILE *arquivo = fopen(argv[1], "r");

    //caso o parâmetro colocado não for um arquivo:

    if (arquivo == NULL) {
        printf("\nO arquivo com o nome informado nao existe!"); 
        return 1;
    }

    //Verificando a primeira linha do arquivo(P1):

    if (!verificar_primeira_linha(arquivo)) {
        printf("Arquivo invalido!\n");
        fclose(arquivo);
        return 1;
    }

    //Verificando a segunda linha (dimensões):

    if (!verificar_segunda_linha(arquivo)) {
        printf("Arquivo invalido!\n");
        fclose(arquivo);
        return 1;
    }

    //Voltando para o começo do arquivo:

    fseek(arquivo, 0, SEEK_SET);

    //identificando o espaçamento lateral do código de barras:

    int espacamento = checar_espacamento(arquivo, largura);

    //Voltando para o começo do arquivo:

    fseek(arquivo, 0, SEEK_SET);

    //identificando o tamanho da área:

    int area = calcular_area(largura, espacamento, arquivo);

    //Voltando para o começo do arquivo:

    fseek(arquivo, 0, SEEK_SET);

    //criando uma matriz, em que cada linha é um digito em binario do código de barras:

    char **matriz_binaria = criar_vetores(largura, area, espacamento, arquivo); //cria uma matriz de vetores, em que cada vetor é um digito do cb, em binario.

    //convertendo cada linha da matriz_binaria para seu respectivo número base10:

    int *numeroscb = converter_binario_base10(matriz_binaria);


    //verificando a validade do código de barras:

    if(!verificar_codigo_de_barras(matriz_binaria, numeroscb, espacamento)){
        free(matriz_binaria);
        free(numeroscb);
        fclose(arquivo);
        return 0;
    }

    if(validacao_identificador(numeroscb)){
        printf("O codigo de barras lido e valido.\n");
    }

    //printando o resultado final:
    printf("Codigo de barras lido:\n");

    for(int i = 0;i<8;i++){
        printf("%d", numeroscb[i]);
    }

    free(matriz_binaria);
    free(numeroscb);
    fclose(arquivo);

    return 0;
}
