CFLAGS =-c -Wall -g
CC = gcc 
TARGET = wf

all: $(TARGET)

$(TARGET): wf.o reader.o dict.o
	$(CC) $^ -o $@

wf.o: wf.c
	$(CC) $(CFLAGS) $^

reader.o: reader.c
	$(CC) $(CFLAGS) $^

dict.o: dict.c
	$(CC) $(CFLAGS) $^

clean:
	rm -f *.o wf
