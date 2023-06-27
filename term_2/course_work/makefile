CC = clang++
# SFML includes and library
SFMLI = /opt/homebrew/Cellar/sfml/2.5.1_2/include
SFMLL = /opt/homebrew/Cellar/sfml/2.5.1_2/lib
LIBS = -lsfml-system -lsfml-window -lsfml-graphics
# Target folders prefixes
PREF_OBJS = ./objs/
PREF_SRC = ./src/
# Sourse code
SRC = $(wildcard $(PREF_SRC)*.cpp)
OBJS = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJS)%.o, $(SRC))

TARGET = text_editor

CFLAGS = -L$(SFMLL) $(LIBS) 

$(TARGET) : $(OBJS)
	$(CC) -g $(OBJS) -o $(TARGET) $(CFLAGS)

$(PREF_OBJS)%.o : $(PREF_SRC)%.cpp
	$(CC) -g -c $< -o $@ -I$(SFMLI)

clean :
	rm $(PREF_OBJS)*.o $(TARGET)

run : $(TARGET)
	./$(TARGET)

debug : $(TARGET)
	lldb $(TARGET)
