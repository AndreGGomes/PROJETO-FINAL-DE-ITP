#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "matriz_final.h"
#include "validade_codigo.h"

//alocação dinâmica para criação da matriz final
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

    while(i < (colunas - borda)){ //ajustar a primeira linh da matriz, depois do espaçamento lateral, de acordo com a largura da área fornecida

        int cont = 0;
        while(cont < largura_area){
            matriz[borda][i] = vetor[x];
            cont = cont + 1;
            i = i + 1;
        }
        x = x + 1;
    }
    for(int ln = 0; ln < linhas; ++ln){ //replica a linha preenchida anteriormente nas demais linhas da matriz
        if(ln > borda && ln < linhas-borda){
            matriz[ln] = matriz[borda];
        }
    }

    free(vetor);
}

//funçãoo que printa a matriz final no arquivo pbm
void print(int** matriz, int linhas, int colunas, char nome_imagem[]){

    setlocale(LC_ALL,"");
    char confirmacao;
    FILE * fp;
    fp = fopen(nome_imagem, "r");

    if(fp == NULL){ //se o arquivo não exixtir, irá criar um novo
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
        printf("O arquivo a ser criado ja existe. Deseja sobrescreve-lo (s/n)?\n");
        scanf(" %c", &confirmacao);
    }
    if(confirmacao == 's'){ //se existir, sobrescreve o arquivo se o usuário desejar sobrescrever
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
        printf("arquivo resultante ja existe!\n");
        free(matriz);
    }

}

//transformar codigo de barras em matriz

int checar_espacamento(FILE *arquivo, int largura) {
    char linha[largura*2];  // Cria o buffer com o tamanho exato da linha (considerando o terminador '\0')
    int espacamento = 0;
    int linha_lida = -1;

    fgets(linha, sizeof(linha), arquivo);
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha_lida++;
        // Remover a nova linha (\n) que fgets pode adicionar, se houver
        linha[strcspn(linha, "\n")] = '\0';

        // Verificar se a linha contém '1'
        if (strchr(linha, '1') != NULL) {
            break;  // Parar a contagem ao encontrar o primeiro '1'
        }

        // Verificar se a linha é composta apenas por '0's
        int i = 0;
        while (linha[i] != '\0') {
            if (linha[i] != '0') {
                if(linha[i]!= '1'){ //caso o caractere não-zero também não seja 1, é pq tem algum caractere invalido!
                    return -2;
                }
                break;
            }
            i++;
        }

        // Se a linha é composta apenas de '0's
        if (linha[i] == '\0') {
            espacamento++;
        }
    }

    if(linha_lida<0){ //caso nenhuma linha tenha sido lida
        return -1;
    }

    return espacamento;
}

int calcular_area(int largura, int espacamento, FILE *arquivo){

    int area = 0;
    char linha[largura*2];

    fgets(linha, sizeof(linha), arquivo); //P1

    fgets(linha, sizeof(linha), arquivo); //largura e altura

    //pulando para a linha após o espacamento
    for(int i=0;i<espacamento;i++){
        fgets(linha, sizeof(linha), arquivo);
    }


    fgets(linha, sizeof(linha), arquivo); //lê uma linha do código de

    for (int i = espacamento; i < largura; i++) { //conta quantos 1s seguidos tem, para descobrir a area
            if (linha[i] == '1') {
                area++;
            } else if (linha[i] == '0'){
                break;
            }
    }

    return area;
}

char** criar_vetores(int largura, int area, int espacamento, FILE *arquivo){

    char linha[largura*2];
    char **vetores = (char **)malloc(8 * sizeof(char *)); //matriz de strings, 8 linhas de 7 caracteres
    for (int i = 0; i < 8; i++) {
        vetores[i] = (char *)malloc(8 * sizeof(char)); //7 caracteres + 1 para \0
    }
    //pulando para a linha após o espacamento
    for(int i = -2; i<espacamento;i++){ //i=-2 para pular as duas primeiras linhas de cabeçalho
        fgets(linha, sizeof(linha), arquivo);
    }
    char c;
    int contador = 0;
    int comecoL = espacamento+(area*3); //após o espaçamento lateral e o '101' que começa o cb
    int comecoR = espacamento+(area*3)+(area*4*7)+(area*5); //após o marcador central do cb
    int fimR = espacamento+(area*3)+(area*4*7)+(area*5)+(area*4*8); //marcador central
    int fimL = espacamento+(area*8*4); //marcador final

    for(int i = 0;i<4;i++){ //parteL do codigo
        int j=0;
        for(contador; contador<fimL && j<7;contador++){ //recebe os caracteres de depois do marcador inical até o marcador central
            c = fgetc(arquivo);
            if(c != '1'&& c != '0'){ //caso o char lido não seja 1 ou 0, um caractere invalido foi lido
                vetores[0][0] = '2'; //'2' sera a flag do erro
                return vetores; //o programa para a leitura
            }
            if(contador>comecoL && (contador-comecoL-1)%area == 0){
            vetores[i][j] = c;
            j++;
            }
        }
        vetores[i][7] = '\0';
    }

    for(int i = 4;i<8;i++){ //parteR do codigo
        int j=0;
        for(contador; contador<fimR && j<7;contador++){ //recebe os caracteres de depois do marcador central até o marcador final
            c = fgetc(arquivo);
            if(contador>comecoR && (contador-comecoR-1)%area == 0){
            vetores[i][j] = c;
            j++;
            }
        }
        vetores[i][7] = '\0';
    }

    return vetores;
}

