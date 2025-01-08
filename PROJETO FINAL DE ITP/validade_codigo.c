#include <string.h>
#include <locale.h>
#include "validade_codigo.h"

int quant_tipo_elementos(char codigoStr[]){

    setlocale(LC_ALL,"");
    int validacao;
    char verificacao[] = "0123456789";

    //verifica a validade do código informado pelo o usuário
    if(!(strlen(codigoStr) == 8)){
        printf("Identificador não possui 8 dígitos!\n");
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
                printf("Identificador contém valores não numéricos!\n");
                break;

            }else{
                validacao = 1;
            }
        }
        return validacao;
    }

}

//converte o código tipo string para tipo inteiro
int convertInter(char x){
    char verificador[] = "0123456789";

    for(int i = 0; i < 10; ++i){
        if(x == verificador[i]){
            return i;
            break;
        }
    }
}

//varifica a validade do dígito verificador
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
        printf("O dígito verificador do identificador é inválido (não corresponde aos valores anteriores)!\n");
        return 0;
    }
}
