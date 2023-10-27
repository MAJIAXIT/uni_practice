CC = g++-13 
SDL_H = /opt/homebrew/Cellar/sdl2/2.26.5/include/SDL2
SDL2 = /opt/homebrew/Cellar/sdl2/2.26.5/include
SDL2_LIB = /opt/homebrew/Cellar/sdl2/2.26.5/lib
SDL2_TTF = /opt/homebrew/Cellar/sdl2_ttf/2.20.2/include
SDL2_TTF_LIB = /opt/homebrew/Cellar/sdl2_ttf/2.20.2/lib

CFLAGS = -g -I$(SDL_H) -I$(SDL2) -L$(SDL2_LIB) -I$(SDL2_TTF) -L$(SDL2_TTF_LIB) -lsdl2 -lsdl2_ttf
TARGET = funcdrawer

$(TARGET) : main.o
	$(CC) main.o -o $(TARGET) $(CFLAGS)

main.o:
	$(CC) -c main.cpp -o main.o $(CFLAGS) 
	
clean:
	rm *.o $(TARGET)

run : $(TARGET)
	./$(TARGET)