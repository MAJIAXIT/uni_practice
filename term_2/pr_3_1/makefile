CC = gcc-13
PREF_OBJS = ./objs/
TARGET = $(PREF_OBJS)main
SRC = $(wildcard *.c)
OBJS = $(patsubst %.c, $(PREF_OBJS)%.o, $(SRC))

$(TARGET) : $(OBJS)
	$(CC) -g $(OBJS) -o $(TARGET)

$(PREF_OBJS)%.o : %.c
	${CC} -g -c $< -o $@

clean : 
	rm $(TARGET) $(PREF_OBJS)*.o

run : $(TARGET)
	$(TARGET)

bubble : $(TARGET)
	$(TARGET) 0

bubbleFixed : $(TARGET)
	$(TARGET) 1

shaker : $(TARGET)
	$(TARGET) 2

qsort : $(TARGET)
	$(TARGET) 3

debug : $(TARGET)
	lldb $(TARGET)