#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include "validade_codigo.h"

int largura, altura;

int quant_tipo_elementos(char codigoStr[]){

    setlocale(LC_ALL,"");
    int validacao;
    char verificacao[] = "0123456789";

    //verifica a validade do c�digo informado pelo o usu�rio
    if(!(strlen(codigoStr) == 8)){
        printf("Identificador n�o possui 8 d�gitos!\n");
        return 0;

    }else{

        for(int i = 0; i < strlen(codigoStr); ++i){

            int testeElemento = 0;

            for(int j = 0; j < 10; ++j){
                if(codigoStr[i] == verificacao[j]){
                    testeElemento = 1;
                }
            }
            if(testeElemento == 0){
                validacao = 0;
                printf("Identificador cont�m valores n�o num�ricos!\n");
                break;

            }else{
                validacao = 1;
            }
        }
        return validacao;
    }

}

//converte o c�digo tipo string para tipo inteiro
int convertInter(char x){
    char verificador[] = "0123456789";

    for(int i = 0; i < 10; ++i){
        if(x == verificador[i]){
            return i;
            break;
        }
    }
}

//varifica a validade do d�gito verificador
int validacao_identificador(int vetor[]){

    setlocale(LC_ALL,"");
    int soma_ponderada = 0;

    for(int i = 0; i < 7; ++i){

        if(((i+1)%2) != 0){
            soma_ponderada = soma_ponderada + (vetor[i]*3);

        }else{
            soma_ponderada = soma_ponderada + vetor[i];

        }
    }

    int cont = 1;
    int mult_dez = 10*cont;

    while(soma_ponderada > mult_dez){
        cont = cont +1;
        mult_dez = cont*10;
    }

    int digito_verificador = mult_dez - soma_ponderada;

    if(digito_verificador == vetor[7]){

        return 1;

    }else{
        printf("O d�gito verificador do identificador � inv�lido (n�o corresponde aos valores anteriores)!\n");
        return 0;
    }
}

//funções para checar a validade do arquivo pbm:

// Função para verificar a primeira linha (cabeçalho "P1")
int verificar_primeira_linha(FILE *arquivo) { //DEU CERTO
    char linha[100];  // Tamanho da linha a ser lida

    if (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remove qualquer caractere de nova linha ao final
        linha[strcspn(linha, "\n")] = '\0';

        // Verifica se a linha contém exatamente "P1"
        if (strcmp(linha, "P1") == 0) {
            return 1;  // Retorna 1 se a primeira linha for "P1"
        } else {return 0;}
    }
}


//verificando segunda linha em busca da altura e largura do codigo de barras
int verificar_segunda_linha(FILE *arquivo) { ///DEU CERTO
    char linha[100];

     // Lê a segunda linha do arquivo
    if (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remove qualquer caractere de nova linha ao final
        linha[strcspn(linha, "\n")] = '\0';

        // Usa sscanf para tentar ler dois inteiros da linha
        if (sscanf(linha, "%d %d", &largura, &altura) == 2) {
            return 1;  // Retorna 1 se a linha contiver exatamente dois inteiros
        }
    }
    return 0;  // Retorna 0 caso contrário
}



int checar_espacamento(FILE *arquivo, int largura, int altura) {
    // Calculando a linha no meio do arquivo
    int linha_meio = altura / 2;
    
    // Posiciona o ponteiro de leitura no início da linha desejada
    fseek(arquivo, linha_meio * largura * sizeof(char), SEEK_SET);
    
    // Variáveis para contar os zeros consecutivos
    int espacamento = 0;
    char c;
    
    for (int i = 0; i < largura; i++) {
        c = fgetc(arquivo);
        
        if (c == '0') {
            espacamento++;
        }
        // Se encontrar um '1', interrompe a contagem
        else if (c == '1') {
            break;
        }
    }
    
    // Retorna a quantidade de zeros consecutivos
    return espacamento;
}


// Função única para verificar o espaçamento superior
//essa função checa se a primeira e ultima linha da matriz são formadas apenas por 0s
//caso ambas sejam formadas apenas por 0s e respeitarem a largura definida, é adicionado +1 ao contador de espaçamento
/*
int checar_espacamento_superior(FILE *arquivo, int largura, int num_linhas) {
    char linha[largura + 1];  // +1 para incluir o terminador nulo '\0'
    int espacamento_superior = 0;
    char **linhas = malloc(num_linhas * sizeof(char *));
    int total_linhas = 0;

    // Pular as duas primeiras linhas do arquivo (cabeçalho)
    fgets(linha, sizeof(linha), arquivo);  // Cabeçalho "P1"
    fgets(linha, sizeof(linha), arquivo);  // Largura e altura

    // Ler as linhas do arquivo até o número total de linhas
    while (fgets(linha, sizeof(linha), arquivo) != NULL && total_linhas < num_linhas) {
        linha[strcspn(linha, "\n")] = '\0';  // Remove o caractere de nova linha
        linhas[total_linhas++] = strdup(linha);
    }

    // Verificar a primeira e a última linha
    if (strlen(linhas[0]) == largura && strlen(linhas[total_linhas - 1]) == largura) {
        int valida = 1;
        for (int i = 0; i < largura; i++) {
            if (linhas[0][i] != '0' || linhas[total_linhas - 1][i] != '0') {
                valida = 0;  // Se encontrar qualquer coisa que não seja '0', marca como inválido
                break;
            }
        }
        if (valida) {
            espacamento_superior++;  // Se ambas as linhas forem válidas, conta
        }
    }

    // Verificar as linhas intermediárias (de cima para baixo e de baixo para cima)
    for (int i = 1, j = total_linhas - 2; i < j; i++, j--) {
        if (strlen(linhas[i]) == largura && strlen(linhas[j]) == largura) {
            int valida_superior = 1, valida_inferior = 1;

            // Verifica se ambas as linhas são formadas apenas por '0's
            for (int k = 0; k < largura; k++) {
                if (linhas[i][k] != '0') {
                    valida_superior = 0;
                    break;
                }
                if (linhas[j][k] != '0') {
                    valida_inferior = 0;
                    break;
                }
            }

            // Se ambas as linhas forem formadas apenas por '0's, conta
            if (valida_superior && valida_inferior) {
                espacamento_superior++;
            }
        }
    }

    // Libera a memória alocada
    for (int i = 0; i < total_linhas; i++) {
        free(linhas[i]);
    }
    free(linhas);

    return espacamento_superior;  // Retorna o número de linhas válidas encontradas
}
*/