#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "matriz_final.h"
#include "validade_codigo.h"
#include "codigo_bin.h"
#define ESPACAMENTO_LATERAL_PADRAO 4
#define LARGURA_AREA_PADRAO 3
#define ALTURA_CODIGO_PADRAO 50
#define NOME_IMAGEM_PADRAO "codigo_de_barras_ean8.pbm"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL,"");
    if (argc != 2) {
        printf("\nNenhum arquivo foi escolhido!");
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r");

    if (arquivo == NULL) {
        printf("\nO arquivo com o nome informado não existe!");
        return 1;
    }

    // Verificar a primeira linha do arquivo
    if (!verificar_primeira_linha(arquivo)) {
        printf("Arquivo inválido.\n");
        fclose(arquivo);
        return 1;
    }

    // Verificar a segunda linha (dimensões)
    if (!verificar_segunda_linha(arquivo)) {
        printf("Arquivo inválido.\n");
        fclose(arquivo);
        return 1;
    }

    // Reabrir o arquivo para checar o espaçamento superior
    fseek(arquivo, 0, SEEK_SET);  // Voltar para o início do arquivo

    // Passando as variáveis globais 'largura' e 'altura' para a função checar_espacamento_superior
    int espacamento = checar_espacamento(arquivo, largura);

    // Reabrir o arquivo para checar o espaçamento superior
    fseek(arquivo, 0, SEEK_SET);  // Voltar para o início do arquivo

    int area = calcular_area(largura, espacamento, arquivo);

    fseek(arquivo, 0, SEEK_SET);  // Voltar para o início do arquivo

    char **matriz_binaria = criar_vetores(largura, area, espacamento, arquivo); //cria uma matriz de vetores, em que cada vetor é um digito do cb, em binario.

    int *numeroscb = converter_binario_base10(matriz_binaria);

    for(int i = 0;i<8;i++){
        printf("%d", numeroscb[i]);
    }

    free(matriz_binaria);
    free(numeroscb);
    fclose(arquivo);

    return 0;
}
