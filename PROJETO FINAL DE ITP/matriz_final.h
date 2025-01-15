#ifndef MATRIZ_FINAL_H_INCLUDED
#define MATRIZ_FINAL_H_INCLUDED

int** dimensionar(int linhas, int colunas);

void montarMatriz(int** matriz, int* vetor, int borda, int largura_area, int linhas, int colunas);

void print(int** matriz, int linhas, int colunas, char nome_imagem[]);

int checar_espacamento(FILE *arquivo, int largura);

int calcular_area(int largura, int espacamento, FILE *arquivo);

char** criar_vetores(int largura, int area, int espacamento, FILE *arquivo);

extern char **vetores;

#endif // MATRIZ_FINAL_H_INCLUDED
