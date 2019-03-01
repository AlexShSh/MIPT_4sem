CFLAGS += -Wall -g
PROG1 = wf1
PROG2 = wf2
OBJ1 = reader.o dict.o word.o 
OBJ2 = reader.o tree.o word.o
HDR1 = reader.h dict.h word.h
HDR2 = reader.h word.h tree.h

all: $(PROG1) $(PROG2)

$(PROG1): $(OBJ1) wf1.o
	$(CC) $(OBJ1) wf.o -o $@

wf1.o: wf.c
	$(CC) $^ -c $(CFLAGS) -D DICT=dict

$(OBJ1): $(HDR1)

$(PROG2): $(OBJ2) wf2.o
	$(CC) $(OBJ2) wf.o -o $@

wf2.o: wf.c
	$(CC) $^ -c $(CFLAGS) -D DICT=tree_dict

$(OBJ2): $(HDR2)

clean:
	$(RM) *.o $(PROG1) $(PROG2)
    
