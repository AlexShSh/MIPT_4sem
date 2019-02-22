CFLAGS += -Wall -g
PROG = wf
OBJ = wf.o reader.o dict.o word.o
HDR = reader.h dict.h word.h

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) $^ -o $@

$(OBJ): $(HDR)

clean:
	$(RM) *.o $(PROG)
    
