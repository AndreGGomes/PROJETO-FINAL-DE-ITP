#ifndef MATRIZ_FINAL_H_INCLUDED
#define MATRIZ_FINAL_H_INCLUDED

int** dimensionar(int linhas, int colunas);

void montarMatriz(int** matriz, int* vetor, int borda, int largura_area, int linhas, int colunas);

void print(int** matriz, int linhas, int colunas, char nome_imagem[]);

int calcular_area(int largura, int espacamento, FILE *arquivo);

void criar_vetores(int largura, int area, int espacamento, FILE *arquivo);

#endif // MATRIZ_FINAL_H_INCLUDED
