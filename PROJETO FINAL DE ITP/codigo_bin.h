#ifndef CODIGO_BIN_H_INCLUDED
#define CODIGO_BIN_H_INCLUDED
#define INICIO_L 3
#define INICIO_R 36

extern int cont_L;
extern int cont_R;

void bits_padrao(int* vetor);

void conversor_R_code(int* codigo, int num);

void conversor_L_code(int* codigo, int num);

int* converter_binario_base10(char** matriz_recebida);

#endif // CODIGO_BIN_H_INCLUDED
