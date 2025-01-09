#include <stdlib.h>
#include <stdio.h>
#include "codigo_bin.h"

int cont_L = INICIO_L;
int cont_R = INICIO_R;

void bits_padrao(int* vetor){

    vetor[0] = 1;
    vetor[1] = 0;
    vetor[2] = 1;
    vetor[31] = 0;
    vetor[32] = 1;
    vetor[33] = 0;
    vetor[34] = 1;
    vetor[35] = 0;
    vetor[64] = 1;
    vetor[65] = 0;
    vetor[66] = 1;

}
void conversor_L_code(int* codigo, int num){

    if(num == 0){
        int vetor[] = {0,0,0,1,1,0,1};

        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 1){
        int vetor[] = {0,0,1,1,0,0,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 2){
        int vetor[] = {0,0,1,0,0,1,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 3){
        int vetor[] = {0,1,1,1,1,0,0};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 4){
        int vetor[] = {0,1,0,0,0,1,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 5){
        int vetor[] = {0,1,1,0,0,0,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 6){
        int vetor[] = {0,1,0,1,1,1,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 7){
        int vetor[] = {0,1,1,1,0,1,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 8){
        int vetor[] = {0,1,1,0,1,1,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 9){
        int vetor[] = {0,0,0,1,0,1,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }

}

void conversor_R_code(int* codigo, int num){

    if(num == 0){
        int vetor[] = {1,1,1,0,0,1,0};

        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 1){
        int vetor[] = {1,1,0,0,1,1,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 2){
        int vetor[] = {1,1,0,1,1,0,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 3){
        int vetor[] = {1,0,0,0,0,1,1};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 4){
        int vetor[] = {1,0,1,1,1,0,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 5){
        int vetor[] = {1,0,0,1,1,1,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 6){
        int vetor[] = {1,0,1,0,0,0,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 7){
        int vetor[] = {1,0,0,0,1,0,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 8){
        int vetor[] = {1,0,0,1,0,0,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 9){
        int vetor[] = {1,1,1,0,1,0,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }

}

