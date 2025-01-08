#include <string.h>
#include <locale.h>
#include <stdio.h>
#include "validade_codigo.h"

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

//fun��o para checar a validade do arquivo pbm:

