g++-13 -c arrRND.c -fPIC -o obj/arrRND.o
g++-13 -c matrixRND.c -fPIC -o obj/matrixRND.o
g++-13 -c matrixMain.c -fPIC -o obj/matrixMain.o
g++-13 -c arrMain.c -fPIC -o obj/arrMain.o

g++-13 -shared obj/arrRND.o obj/arrMain.o -o obj/libarr.so
g++-13 -shared obj/matrixRND.o obj/matrixMain.o -o obj/libmatrix.so

g++-13 -c load.c -fPIC -o obj/load.o
g++-13 -shared obj/load.o -o obj/libload.so

g++-13 -c loadmain.c -fPIC -o obj/loadmain.o
g++-13 obj/loadmain.o -ldl -L./obj/ -lload -o main

./main
