FLAGS = -w -pedantic

COMMON_OBJ = codigo_bin.o matriz_final.o validade_codigo.o entradas.o

all: createCB readCB

createCB: createCB.o $(COMMON_OBJ)
	gcc createCB.o $(COMMON_OBJ) -o createCB $(FLAGS)

readCB: readCB.o $(COMMON_OBJ)
	gcc readCB.o $(COMMON_OBJ) -o readCB $(FLAGS)

createCB.o: createCB.c
	gcc -c createCB.c $(FLAGS)

entradas.o: entradas.c
	gcc -c entradas.c $(FLAGS)

readCB.o: readCB.c
	gcc -c readCB.c $(FLAGS)

codigo_bin.o: codigo_bin.c
	gcc -c codigo_bin.c $(FLAGS)

matriz_final.o: matriz_final.c
	gcc -c matriz_final.c $(FLAGS)

validade_codigo.o: validade_codigo.c
	gcc -c validade_codigo.c $(FLAGS)

clean:
	del /Q *.o
	del /Q createCB.exe readCB.exe
