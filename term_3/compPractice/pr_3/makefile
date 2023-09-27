CC = clang-17

P_OBJ = ./obj/
P_SRC = ./src/

SRC = $(wildcard $(P_SRC)*.c)
OBJS = $(patsubst $(P_SRC)%.c, $(P_OBJ)%.o, $(SRC))

TARGET = $(P_OBJ)main

TARGET : $(OBJS)
	$(CC) -shared $(P_OBJ)arrRND.o $(P_OBJ)arrMain.o -o $(P_OBJ)libarr.so
	$(CC) -shared $(P_OBJ)matrixRND.o $(P_OBJ)matrixMain.o -o $(P_OBJ)libmatrix.so
	$(CC) -shared $(P_OBJ)load.o -o $(P_OBJ)libload.so
	$(CC) $(P_OBJ)loadmain.o -ldl -L$(P_OBJ) -lload -o $(P_OBJ)main

$(P_OBJ)%.o : $(P_SRC)%.c
	$(CC) -c $< -fPIC -o $@ 

clean :
	rm -r $(P_OBJ)*