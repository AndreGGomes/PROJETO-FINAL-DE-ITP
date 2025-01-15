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
        printf("Identificador nao possui 8 digitos!\n");
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
                printf("Identificador contem valores nao numericos!\n");
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
        printf("O digito verificador do identificador e invalido (nao corresponde aos valores anteriores)!\n");
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
    } else {return 0;}
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

int verificar_codigo_de_barras(char** matriz_binaria, int* numeroscb, int espacamento){

    if(espacamento == -1){ //checando flag de erro
        printf("O codigo de barras nao foi encontrado.");
        return 0;
    } else if(espacamento == -2){ //checando flag de erro
        printf("Codigo de barras invalido: Caracteres invalidos presentes no arquivo.");
        return 0;
    }

    if(matriz_binaria[0][0] == '2'){ //checando flag de erro
        printf("Codigo de barras invalido: Caracteres invalidos presentes no arquivo.");
        return 0;
    }

    if(numeroscb[0]== -1){ //checando flag de erro
        printf("Codigo de barras invalido: Digitos do codigo de barras sao invalidos");
        return 0;
    }

    return 1; //caso nenhum problema for encontrado
}