#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "matriz_final.h"
#include "validade_codigo.h"
#include "codigo_bin.h"
#include "entradas.h"

int main(int argc, char **argv){

    if(argc < 2){
        printf("Informe as entradas corretamente.\n");
        condicoes_entradas();
        return 1;
    }else{
        if(strcmp(argv[1], "-c") != 0){
            printf("O código EAN-8 deve ser obrigatoriamente informado. Caso o código tenha sido inserido, certifique-se de que foi o primeiro parâmetro informado.\n");
            condicoes_entradas();
            return 1;
        }
    }
    //declaração das variaveis utilizadas para a configuração das entradas.

    char *c;
    char *e = ESPACAMENTO_LATERAL_PADRAO;
    char *a = ALTURA_CODIGO_PADRAO;
    char *l = LARGURA_AREA_PADRAO;
    char *n = NOME_IMAGEM_PADRAO;
    int index;
    int x;
    int elemento;
    opterr = 0;

    //declaração das variaveis utilizadas para a construção do c�digo de barras.
    int** img;
    char codigo_string[100];
    int codigo_int[8];
    int* codigo_ean = calloc(67, sizeof(int));
    int espaco_lateral, altura_cod, largura_area;
    char nome_img[100];
    int linhas_img, colunas_img;


    while ((x = getopt (argc, argv, "c:e:a:l:n:")) != -1){

        switch (x){
            case 'c':
                c = optarg;
                break;
            case 'e':
                e = optarg;
                break;
            case 'a':
                a = optarg;
                break;
            case 'l':
                l = optarg;
                break;
            case 'n':
                n = optarg;
                break;
            case '?':
                if (optopt == 'c')
                  fprintf (stderr, "A opcao -c requer um argumento.\n", optopt);
                else if (optopt == 'e')
                  fprintf (stderr, "A opcao -e requer um argumento.\n", optopt);
                else if (optopt == 'a')
                  fprintf (stderr, "A opcao -a requer um argumento.\n", optopt);
                else if (optopt == 'l')
                  fprintf (stderr, "A opcao -l requer um argumento.\n", optopt);
                else if (optopt == 'n')
                  fprintf (stderr, "A opcao -n requer um argumento.\n", optopt);
                else
                  fprintf (stderr,"Alguma opções podem estar inválidas. Verifique suas entradas e tente novamente.\n", optopt);

                condicoes_entradas();

                return 1;

            default:
                return 1;
                abort ();
        }
    }

    for (index = optind; index < argc; index++){
        elemento = index;
        break;
    }

    if(elemento){
        printf("Sua entrada apresenta algum/s caracter/es inválido/s. Certifique-se de que tudo foi digitado corretamente.\n");
        condicoes_entradas();
        return 1;
    }

    strcpy(codigo_string, c);
    espaco_lateral = atoi(e);
    altura_cod = atoi(a);
    largura_area = atoi(l);
    strcpy(nome_img, n);
    strcat(nome_img, ".pbm");

    //verifica se o códido informado possui exatamente 8 dígitos e se todos eles são numéricos

    if(quant_tipo_elementos(codigo_string)){

        for(int i = 0; i < 8; ++i){

            //converte o codigo informado em um vetor de inteiros
            codigo_int[i] = convertInter(codigo_string[i]);
        }

        //verifica se o dígito verificador corresponde ao código informado
        if(validacao_identificador(codigo_int)){

            //dimensões da matriz final que definirá a imagem com o código de barras
            linhas_img = (altura_cod + 2*espaco_lateral);
            colunas_img = (67*largura_area + 2*espaco_lateral);

            //aloca os bits padrões no vetor que contém o código R-code e L-code
            bits_padrao(codigo_ean);

            //preenche o vetor que contém o código R-code e L-code com os demais dígitos
            for(int i = 0; i < 8; ++i){
                if(i < 4){
                    conversor_L_code(codigo_ean, codigo_int[i]);

                }else{
                    conversor_R_code(codigo_ean, codigo_int[i]);
                }
            }

            //cria a matriz que conterá a informaçãao da imagem
            img = dimensionar(linhas_img, colunas_img);

            //aloca cada elenmento na matriz final baseando-se nos parametros fornecidos pelo o usuário
            montarMatriz(img, codigo_ean, espaco_lateral, largura_area, linhas_img, colunas_img);

            //cria o arquivo com a imagem
            print(img, linhas_img, colunas_img, nome_img);

        }

    }

    return 0;

}
