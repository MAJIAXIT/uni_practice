CC = g++-13 
SDL2 = /opt/homebrew/Cellar/sdl2/2.26.5/include
SDL2_IMAGE = /opt/homebrew/Cellar/sdl2_image/2.6.3_1/include
LIB_SDL2 = /opt/homebrew/Cellar/sdl2/2.26.5/lib
LIB_SDL2_IMAGE = /opt/homebrew/Cellar/sdl2_image/2.6.3_1/lib

CFLAGS = -g -I$(SDL2) -L$(LIB_SDL2) -I$(SDL2_IMAGE) -L$(LIB_SDL2_IMAGE) -lsdl2 -lsdl2_image
TARGET = football

$(TARGET) : main.o
	$(CC) main.o -o $(TARGET) $(CFLAGS)

main.o:
	$(CC) -c main.cpp -o main.o $(CFLAGS) 
	
clean:
	rm *.o $(TARGET)